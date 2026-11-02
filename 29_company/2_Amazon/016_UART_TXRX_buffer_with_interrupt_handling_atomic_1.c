/***

    Implement a UART RX/TX buffer with interrupt handling :

    You are designing a UART driver with two independent circular buffers:
    - RX buffer: UART hardware receives bytes and triggers an RX interrupt.
                 The ISR reads bytes from the UART data register and stores
                 them in the RX ring buffer. Application code reads those bytes.
    - TX buffer: Application code queues bytes into the TX ring buffer.
                 The TX interrupt handler removes bytes and writes them to the
    UART transmit data register.

    Functional requirements :
    Your implementation must support:
    1. Initialize RX and TX ring buffers with fixed capacity.
    2. Receive a byte from the UART hardware through the RX ISR and store it in the RX buffer.
    3. Allow application code to read bytes from the RX buffer in FIFO order.
    4. Allow application code to queue bytes into the TX buffer.
    5. Transmit bytes through the TX ISR whenever the hardware is ready.
    6. Detect RX overflow and count dropped bytes.
    7. Detect TX buffer full and return a failure status without overwriting data.
    8. Correctly handle circular wraparound.

    Constraints :
    Property	Requirement
    Programming language	C11
    RX buffer	16 bytes
    TX buffer	16 bytes
    Memory allocation	No malloc()
    RX ISR	Must not block
    TX ISR	Must not block
    FIFO ordering	Mandatory
    Runtime	O(1) per byte
    Synchronization	Bare-metal ISR/main-loop model
    Hardware	Memory-mapped UART registers (abstracted)

    Assume a single-core MCU. The RX ISR is the only RX producer, and the application is the only RX consumer.
    The application is the only TX producer, and the TX ISR is the only TX consumer. For this first version,
    application APIs are non-reentrant and interrupts are not nested.

    You may use short interrupt-masking critical sections where necessary, but do not use
    pthread_mutex_lock() or pthread_cond_wait() inside an ISR.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun Nov  1 08:35:00 PST 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdatomic.h>
#include <string.h>
#include <assert.h>

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

#define UART_RX_SIZE 16
#define UART_TX_SIZE 16
#define HW_RX_SIZE   64
#define HW_TX_SIZE   256

/*
 * SPSC ring buffer:
 *
 * head: consumer-owned counter
 * tail: producer-owned counter
 *
 * RX:
 *   producer = RX ISR on Core 0
 *   consumer = application on Core 1
 *
 * TX:
 *   producer = application on Core 1
 *   consumer = TX ISR on Core 0
 *
 * No shared count variable.
 *
 * Invariant:
 *     0 <= tail - head <= capacity
 *
 * Counters are monotonically advancing unsigned
 * values. Array indices wrap independently.
 */
typedef struct {
  uint8_t buffer[UART_RX_SIZE];

  atomic_size_t head;
  atomic_size_t tail;
} RingBuffer;

typedef struct {
  RingBuffer rx;
  RingBuffer tx;

  atomic_uint rx_overflow_count;
} UARTDriver;

/*
 * Mock UART hardware.
 *
 * This test harness is driven sequentially from main().
 * The driver ring synchronization is suitable for
 * concurrent SPSC access, but the mock hardware itself
 * is not a general concurrent hardware simulator.
 */
typedef struct {
  uint8_t rx_fifo[HW_RX_SIZE];
  size_t rx_head;
  size_t rx_tail;
  size_t rx_count;

  uint8_t tx_log[HW_TX_SIZE];
  size_t tx_count;

  atomic_bool tx_irq_enabled;
  bool tx_ready;
} UARTMockHW;

static UARTMockHW hw;

/* ---------------- Hardware simulation ---------------- */

static void hw_init(void) {
  memset(&hw, 0, sizeof(hw));
  atomic_init(&hw.tx_irq_enabled, false);
  hw.tx_ready = true;
}

static bool hw_inject_rx(uint8_t byte) {
  if (hw.rx_count == HW_RX_SIZE)
    return false;

  hw.rx_fifo[hw.rx_tail] = byte;
  hw.rx_tail = (hw.rx_tail + 1) % HW_RX_SIZE;
  hw.rx_count++;

  return true;
}

bool uart_hw_rx_ready(void) {
  return hw.rx_count != 0;
}

uint8_t uart_hw_read_byte(void) {
  assert(hw.rx_count > 0);

  uint8_t byte = hw.rx_fifo[hw.rx_head];

  hw.rx_head = (hw.rx_head + 1) % HW_RX_SIZE;
  hw.rx_count--;

  return byte;
}

bool uart_hw_tx_ready(void) {
  return hw.tx_ready;
}

void uart_hw_write_byte(uint8_t byte) {
  assert(hw.tx_ready);
  assert(hw.tx_count < HW_TX_SIZE);

  hw.tx_log[hw.tx_count++] = byte;
}

void uart_enable_tx_interrupt(void) {
  atomic_store_explicit(&hw.tx_irq_enabled, true, memory_order_seq_cst);
}

void uart_disable_tx_interrupt(void) {
  atomic_store_explicit(&hw.tx_irq_enabled, false, memory_order_seq_cst);
}

/* ---------------- Initialization ---------------- */

static void ring_init(RingBuffer *r) {
  atomic_init(&r->head, 0);
  atomic_init(&r->tail, 0);
}

void uart_init(UARTDriver *uart) {
  if (!uart)
    return;

  /*
   * Call before enabling UART interrupts
   * or starting application threads.
   */
  ring_init(&uart->rx);
  ring_init(&uart->tx);

  atomic_init(&uart->rx_overflow_count, 0);

  uart_disable_tx_interrupt();
}

/* ---------------- RX ISR: producer ---------------- */

/*
 * Core 0: RX interrupt.
 *
 * Reads hardware and publishes received bytes.
 * Never waits for the application.
 */
void uart_rx_isr(UARTDriver *uart) {
  if (!uart)
    return;

  while (uart_hw_rx_ready()) {

    uint8_t byte = uart_hw_read_byte();

    /*
     * Only RX ISR modifies tail.
     * Therefore relaxed load is sufficient.
     */
    size_t tail = atomic_load_explicit(&uart->rx.tail, memory_order_relaxed);

    /*
     * Application owns head.
     * Acquire ensures previously consumed slots
     * may safely be reused.
     */
    size_t head = atomic_load_explicit(&uart->rx.head, memory_order_acquire);

    if (tail - head >= UART_RX_SIZE) {

      /*
       * Software RX ring full:
       * discard newest incoming byte.
       */
      atomic_fetch_add_explicit(&uart->rx_overflow_count, 1, memory_order_relaxed);

      continue;
    }

    uart->rx.buffer[tail % UART_RX_SIZE] = byte;

    /*
     * Publish byte only after writing it.
     *
     * Consumer's acquire-load of tail
     * synchronizes with this release.
     */
    atomic_store_explicit(&uart->rx.tail, tail + 1, memory_order_release);
  }
}

/* ---------------- RX application: consumer ---------------- */

/*
 * Core 1: application reads received bytes.
 *
 * Returns false if RX ring is empty.
 */
bool uart_rx_pop(UARTDriver *uart, uint8_t *byte) {
  if (!uart || !byte)
    return false;

  size_t head = atomic_load_explicit(&uart->rx.head, memory_order_relaxed);

  size_t tail = atomic_load_explicit(&uart->rx.tail, memory_order_acquire);

  if (head == tail)
    return false;

  /*
   * Acquire of tail guarantees the published
   * payload byte is visible on this CPU.
   */
  *byte = uart->rx.buffer[head % UART_RX_SIZE];

  /*
   * Release head after reading the byte.
   * Producer can now reuse this slot.
   */
  atomic_store_explicit(&uart->rx.head, head + 1, memory_order_release);

  return true;
}

/* ---------------- TX application: producer ---------------- */

/*
 * Core 1: enqueue a byte for transmission.
 *
 * Returns false if software TX ring is full.
 */
bool uart_tx_push(UARTDriver *uart, uint8_t byte) {
  if (!uart)
    return false;

  size_t tail = atomic_load_explicit(&uart->tx.tail, memory_order_relaxed);

  size_t head = atomic_load_explicit(&uart->tx.head, memory_order_acquire);

  if (tail - head >= UART_TX_SIZE)
    return false;

  uart->tx.buffer[tail % UART_TX_SIZE] = byte;

  /*
   * Publish the byte before enabling TX IRQ.
   */
  atomic_store_explicit(&uart->tx.tail, tail + 1, memory_order_release);

  /*
   * Kick TX hardware.
   *
   * The hardware-specific interrupt controller
   * must guarantee a pending/level TX-ready event
   * is serviced when this interrupt is enabled.
   */
  uart_enable_tx_interrupt();

  return true;
}

/* ---------------- TX ISR: consumer ---------------- */

/*
 * Core 0: TX interrupt.
 *
 * Sends at most one byte per invocation.
 * This matches a UART with one available TX slot.
 *
 * For a hardware FIFO, loop while TX has room.
 */
void uart_tx_isr(UARTDriver *uart) {
  if (!uart)
    return;

  if (!uart_hw_tx_ready())
    return;

  size_t head = atomic_load_explicit(&uart->tx.head, memory_order_relaxed);

  size_t tail = atomic_load_explicit(&uart->tx.tail, memory_order_acquire);

  if (head != tail) {

    uint8_t byte = uart->tx.buffer[head % UART_TX_SIZE];

    /*
     * Submit byte to hardware before freeing
     * its software ring slot.
     */
    uart_hw_write_byte(byte);

    atomic_store_explicit(&uart->tx.head, head + 1, memory_order_release);

    return;
  }

  /*
   * Empty queue: disable TX-ready interrupt
   * to avoid an interrupt storm.
   */
  uart_disable_tx_interrupt();

  /*
   * Recheck after disabling.
   *
   * Producer may have enqueued a byte while
   * the ISR was disabling the interrupt.
   *
   * If data is now present, reenable it.
   */
  head = atomic_load_explicit(&uart->tx.head, memory_order_acquire);

  tail = atomic_load_explicit(&uart->tx.tail, memory_order_acquire);

  if (head != tail)
    uart_enable_tx_interrupt();
}

/* ---------------- Test interrupt dispatcher ---------------- */

/*
 * Simulates hardware interrupt delivery.
 * In a real system the interrupt controller
 * invokes the appropriate handler.
 */
static void service_uart(UARTDriver *uart) {
  if (uart_hw_rx_ready())
    uart_rx_isr(uart);

  /*
   * One TX byte per simulated interrupt.
   */
  if (atomic_load_explicit(&hw.tx_irq_enabled, memory_order_seq_cst) && uart_hw_tx_ready()) {
    uart_tx_isr(uart);
  }
}

static void drain_tx(UARTDriver *uart) {
  /*
   * Bound the test to catch stuck TX IRQs.
   */
  for (size_t i = 0; i < 100; i++) {
    if (!atomic_load_explicit(&hw.tx_irq_enabled, memory_order_seq_cst))
      return;
    service_uart(uart);
  }
  assert(!"TX interrupt failed to quiesce");
}

/* ---------------- Tests ---------------- */

static void test_rx_fifo(UARTDriver *uart) {
  printf("Test 1: RX FIFO\n");

  assert(hw_inject_rx('A'));
  assert(hw_inject_rx('B'));
  assert(hw_inject_rx('C'));

  service_uart(uart);

  uint8_t byte;

  assert(uart_rx_pop(uart, &byte) && byte == 'A');
  assert(uart_rx_pop(uart, &byte) && byte == 'B');
  assert(uart_rx_pop(uart, &byte) && byte == 'C');

  assert(!uart_rx_pop(uart, &byte));

  printf("PASS\n");
}

static void test_rx_overflow(UARTDriver *uart) {
  printf("Test 2: RX overflow\n");

  for (int i = 0; i < 20; i++)
    assert(hw_inject_rx((uint8_t)i));

  service_uart(uart);

  assert(atomic_load(&uart->rx_overflow_count) == 4);

  for (int i = 0; i < 16; i++) {
    uint8_t byte;
    assert(uart_rx_pop(uart, &byte));
    assert(byte == (uint8_t)i);
  }

  printf("PASS: 4 bytes dropped\n");
}

static void test_rx_wraparound(UARTDriver *uart) {
  printf("Test 3: RX wraparound\n");

  for (int i = 0; i < 40; i++) {
    uint8_t byte;

    assert(hw_inject_rx((uint8_t)i));
    service_uart(uart);

    assert(uart_rx_pop(uart, &byte));
    assert(byte == (uint8_t)i);
  }

  printf("PASS\n");
}

static void test_tx_fifo(UARTDriver *uart) {
  printf("Test 4: TX FIFO\n");

  size_t start = hw.tx_count;

  assert(uart_tx_push(uart, 'H'));
  assert(uart_tx_push(uart, 'E'));
  assert(uart_tx_push(uart, 'L'));
  assert(uart_tx_push(uart, 'L'));
  assert(uart_tx_push(uart, 'O'));

  drain_tx(uart);

  assert(hw.tx_count == start + 5);
  assert(memcmp(&hw.tx_log[start], "HELLO", 5) == 0);

  printf("PASS: HELLO transmitted\n");
}

static void test_tx_full(UARTDriver *uart) {
  printf("Test 5: TX full\n");

  hw.tx_ready = false;

  for (int i = 0; i < 16; i++)
    assert(uart_tx_push(uart, (uint8_t)i));

  assert(!uart_tx_push(uart, 0xFF));

  size_t start = hw.tx_count;

  hw.tx_ready = true;
  drain_tx(uart);

  for (int i = 0; i < 16; i++)
    assert(hw.tx_log[start + i] == (uint8_t)i);

  printf("PASS: overflow prevented\n");
}

static void test_tx_wraparound(UARTDriver *uart) {
  printf("Test 6: TX wraparound\n");

  size_t start = hw.tx_count;

  for (int i = 0; i < 40; i++) {
    assert(uart_tx_push(uart, (uint8_t)(i + 50)));
    drain_tx(uart);
  }

  for (int i = 0; i < 40; i++)
    assert(hw.tx_log[start + i] == (uint8_t)(i + 50));

  printf("PASS\n");
}

static void test_edge_cases(UARTDriver *uart) {
  printf("Test 7: Invalid arguments and empty RX\n");

  uint8_t byte;

  assert(!uart_rx_pop(NULL, &byte));
  assert(!uart_rx_pop(uart, NULL));
  assert(!uart_tx_push(NULL, 0x55));
  assert(!uart_rx_pop(uart, &byte));

  uart_rx_isr(NULL);
  uart_tx_isr(NULL);
  uart_init(NULL);

  printf("PASS\n");
}

/* ---------------- test ---------------- */
int test(void) {
  UARTDriver uart;

  hw_init();
  uart_init(&uart);

  test_rx_fifo(&uart);
  test_rx_overflow(&uart);
  test_rx_wraparound(&uart);
  test_tx_fifo(&uart);
  test_tx_full(&uart);
  test_tx_wraparound(&uart);
  test_edge_cases(&uart);

  printf("\nAll tests passed!\n");

  printf("RX overflow count: %u\n", atomic_load(&uart.rx_overflow_count));

  printf("TX bytes submitted: %zu\n", hw.tx_count);

  return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   Test 1: RX FIFO
   PASS
   Test 2: RX overflow
   PASS: 4 bytes dropped
   Test 3: RX wraparound
   PASS
   Test 4: TX FIFO
   PASS: HELLO transmitted
   Test 5: TX full
   PASS: overflow prevented
   Test 6: TX wraparound
   PASS
   Test 7: Invalid arguments and empty RX
   PASS

   All tests passed!
   RX overflow count: 4
   TX bytes submitted: 61
**/
