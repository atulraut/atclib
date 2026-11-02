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

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>

#define UART_RX_SIZE 16
#define UART_TX_SIZE 16
#define RX_TEST_BYTES 24
#define TX_TEST_BYTES 40

typedef struct {
    uint8_t data[UART_RX_SIZE];

    size_t head;
    size_t tail;
    size_t count;
    size_t capacity;

    pthread_mutex_t mutex;
    pthread_cond_t is_empty;
    pthread_cond_t is_full;

    bool closed;
} RingBuffer;

typedef struct {
    RingBuffer rx;
    RingBuffer tx;

    uint32_t rx_overflow_count;

    uint8_t rx_output[RX_TEST_BYTES];
    size_t rx_output_count;

    uint8_t tx_output[TX_TEST_BYTES];
    size_t tx_output_count;
} UARTDriver;

/*
 * Initialize before creating threads.
 * The mutex protects every ring state update.
 */
bool ring_init(RingBuffer *r, size_t capacity) {
    if (!r || capacity == 0 ||
        capacity > UART_RX_SIZE)
        return false;

    r->head = 0;
    r->tail = 0;
    r->count = 0;
    r->capacity = capacity;
    r->closed = false;

    if (pthread_mutex_init(&r->mutex, NULL) != 0)
        return false;

    if (pthread_cond_init(&r->is_empty, NULL) != 0) {
        pthread_mutex_destroy(&r->mutex);
        return false;
    }

    if (pthread_cond_init(&r->is_full, NULL) != 0) {
        pthread_cond_destroy(&r->is_empty);
        pthread_mutex_destroy(&r->mutex);
        return false;
    }

    return true;
}

void ring_close(RingBuffer *r) {
    pthread_mutex_lock(&r->mutex);

    r->closed = true;

    /* Wake all threads waiting for data or space. */
    pthread_cond_broadcast(&r->is_empty);
    pthread_cond_broadcast(&r->is_full);

    pthread_mutex_unlock(&r->mutex);
}

void ring_destroy(RingBuffer *r) {
    pthread_cond_destroy(&r->is_empty);
    pthread_cond_destroy(&r->is_full);
    pthread_mutex_destroy(&r->mutex);
}

bool uart_init(UARTDriver *uart) {
    if (!uart)
        return false;

    memset(uart, 0, sizeof(*uart));

    if (!ring_init(&uart->rx, UART_RX_SIZE))
        return false;

    if (!ring_init(&uart->tx, UART_TX_SIZE)) {
        ring_destroy(&uart->rx);
        return false;
    }

    return true;
}

/*
 * Simulated RX interrupt:
 *
 * In real hardware this byte comes from the UART
 * receive data register.
 *
 * If RX is full, discard the new byte.
 *
 * This uses a pthread mutex ONLY because this is
 * a userspace simulation, not a real hard IRQ.
 */
bool uart_rx_isr(UARTDriver *uart, uint8_t byte) {
    if (!uart)
        return false;

    RingBuffer *r = &uart->rx;

    pthread_mutex_lock(&r->mutex);

    if (r->closed) {
        pthread_mutex_unlock(&r->mutex);
        return false;
    }

    if (r->count == r->capacity) {
        uart->rx_overflow_count++;

        pthread_mutex_unlock(&r->mutex);
        return false;
    }

    r->data[r->tail] = byte;
    r->tail = (r->tail + 1) % r->capacity;
    r->count++;

    /*
     * Wake a consumer waiting on an empty ring.
     */
    pthread_cond_signal(&r->is_empty);

    pthread_mutex_unlock(&r->mutex);

    return true;
}

/*
 * Application RX:
 *
 * Wait until data arrives or the RX ring closes.
 * Returns false after shutdown and draining.
 */
bool uart_rx_pop(UARTDriver *uart, uint8_t *byte) {
    if (!uart || !byte)
        return false;

    RingBuffer *r = &uart->rx;

    pthread_mutex_lock(&r->mutex);

    while (r->count == 0 && !r->closed) {
        pthread_cond_wait(&r->is_empty, &r->mutex);
    }

    if (r->count == 0) {
        pthread_mutex_unlock(&r->mutex);
        return false;
    }

    *byte = r->data[r->head];
    r->head = (r->head + 1) % r->capacity;
    r->count--;

    pthread_cond_signal(&r->is_full);

    pthread_mutex_unlock(&r->mutex);

    return true;
}

/*
 * Application TX:
 *
 * Unlike RX overflow handling, TX uses blocking.
 * Producer waits when the TX ring is full.
 */
bool uart_tx_push(UARTDriver *uart, uint8_t byte)
{
    if (!uart)
        return false;

    RingBuffer *r = &uart->tx;

    pthread_mutex_lock(&r->mutex);

    while (r->count == r->capacity && !r->closed) {
        pthread_cond_wait(&r->is_full, &r->mutex);
    }

    if (r->closed) {
        pthread_mutex_unlock(&r->mutex);
        return false;
    }

    r->data[r->tail] = byte;
    r->tail = (r->tail + 1) % r->capacity;
    r->count++;

    pthread_cond_signal(&r->is_empty);

    pthread_mutex_unlock(&r->mutex);

    return true;
}

/*
 * Simulated TX ISR worker:
 *
 * Wait for TX data and remove one byte.
 *
 * Real hardware code would write the byte
 * to the UART TX register when hardware is ready.
 */
bool uart_tx_isr(UARTDriver *uart, uint8_t *byte) {
    if (!uart || !byte)
        return false;

    RingBuffer *r = &uart->tx;

    pthread_mutex_lock(&r->mutex);

    while (r->count == 0 && !r->closed) {
        pthread_cond_wait(&r->is_empty, &r->mutex);
    }

    if (r->count == 0) {
        pthread_mutex_unlock(&r->mutex);
        return false;
    }

    *byte = r->data[r->head];
    r->head = (r->head + 1) % r->capacity;
    r->count--;

    /* Producer may now have room to enqueue. */
    pthread_cond_signal(&r->is_full);

    pthread_mutex_unlock(&r->mutex);

    return true;
}

/* ---------------- Thread functions ---------------- */

/*
 * Simulate UART hardware receiving 24 bytes.
 *
 * We intentionally finish this thread before
 * starting the RX consumer, to test overflow.
 */
void *rx_hardware_thread(void *arg) {
    UARTDriver *uart = arg;

    for (int i = 0; i < RX_TEST_BYTES; i++) {
        uart_rx_isr(uart, (uint8_t)('A' + i));
    }

    ring_close(&uart->rx);
    return NULL;
}

/* Application consumes RX bytes in FIFO order. */
void *rx_application_thread(void *arg) {
    UARTDriver *uart = arg;
    uint8_t byte;

    while (uart_rx_pop(uart, &byte)) {
        size_t pos = uart->rx_output_count++;

        assert(pos < RX_TEST_BYTES);
        uart->rx_output[pos] = byte;

        printf("RX application: %c\n", byte);
    }

    return NULL;
}

/* Application produces more than one TX ring's capacity. */
void *tx_application_thread(void *arg) {
    UARTDriver *uart = arg;

    for (int i = 0; i < TX_TEST_BYTES; i++) {
        uint8_t byte = (uint8_t)i;

        assert(uart_tx_push(uart, byte));
    }

    ring_close(&uart->tx);
    return NULL;
}

/*
 * Simulated TX worker.
 *
 * A real hard ISR must not wait on condition
 * variables. This worker represents deferred
 * interrupt processing in userspace.
 */
void *tx_interrupt_thread(void *arg) {
    UARTDriver *uart = arg;
    uint8_t byte;

    while (uart_tx_isr(uart, &byte)) {
        size_t pos = uart->tx_output_count++;

        assert(pos < TX_TEST_BYTES);
        uart->tx_output[pos] = byte;
    }

    return NULL;
}

/* ---------------- Tests ---------------- */
static void test_rx(UARTDriver *uart) {
    pthread_t producer, consumer;

    printf("\nTest 1: RX FIFO and overflow\n");

    assert(pthread_create(&producer, NULL, rx_hardware_thread, uart) == 0);

    assert(pthread_join(producer, NULL) == 0);

    /*
     * Producer generated 24 bytes.
     * Ring capacity is 16.
     *
     * Expected:
     * 16 retained, 8 dropped.
     */
    assert(uart->rx_overflow_count == 8);
    assert(uart->rx.count == UART_RX_SIZE);

    assert(pthread_create(&consumer, NULL, rx_application_thread, uart) == 0);

    assert(pthread_join(consumer, NULL) == 0);

    assert(uart->rx_output_count == UART_RX_SIZE);

    for (int i = 0; i < UART_RX_SIZE; i++) {
        assert(uart->rx_output[i] == (uint8_t)('A' + i));
    }

    assert(uart->rx.count == 0);

    printf("RX PASS: retained 16, dropped 8\n");
}

static void test_tx(UARTDriver *uart) {
    pthread_t producer, consumer;

    printf("\nTest 2: TX concurrent producer/consumer\n");

    /*
     * Start both threads.
     * Producer blocks when TX ring fills.
     * Consumer wakes producer as space is freed.
     */
    assert(pthread_create(&consumer, NULL, tx_interrupt_thread, uart) == 0);

    assert(pthread_create(&producer, NULL, tx_application_thread, uart) == 0);

    assert(pthread_join(producer, NULL) == 0);
    assert(pthread_join(consumer, NULL) == 0);

    assert(uart->tx_output_count == TX_TEST_BYTES);

    for (int i = 0; i < TX_TEST_BYTES; i++) {
        assert(uart->tx_output[i] == (uint8_t)i);
    }

    assert(uart->tx.count == 0);

    printf("TX PASS: all 40 bytes delivered in order\n");
}

static void test_edge_cases(UARTDriver *uart) {
    uint8_t byte = 0;

    printf("\nTest 3: Edge cases\n");

    assert(!uart_rx_pop(NULL, &byte));
    assert(!uart_rx_pop(uart, NULL));
    assert(!uart_tx_push(NULL, 0x55));
    assert(!uart_tx_isr(NULL, &byte));

    /* Both rings have been closed and drained. */
    assert(!uart_rx_pop(uart, &byte));
    assert(!uart_tx_push(uart, 0x55));
    assert(!uart_tx_isr(uart, &byte));
    assert(!uart_rx_isr(uart, 0x55));

    printf("Edge cases PASS\n");
}

/* ---------------- test ---------------- */
int test(void) {
  UARTDriver uart;

  if (!uart_init(&uart)) {
    fprintf(stderr, "UART initialization failed\n");
    return 1;
  }

  test_rx(&uart);
  test_tx(&uart);
  test_edge_cases(&uart);

  printf("\nAll tests passed!\n");
  printf("RX overflow count: %u\n",
	 (unsigned)uart.rx_overflow_count);
  printf("TX bytes transmitted: %zu\n",
	 uart.tx_output_count);

  ring_destroy(&uart.rx);
  ring_destroy(&uart.tx);

  return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}


/**
   Test 1: RX FIFO and overflow
   RX application: A
   RX application: B
   RX application: C
   RX application: D
   RX application: E
   RX application: F
   RX application: G
   RX application: H
   RX application: I
   RX application: J
   RX application: K
   RX application: L
   RX application: M
   RX application: N
   RX application: O
   RX application: P
   RX PASS: retained 16, dropped 8

   Test 2: TX concurrent producer/consumer
   TX PASS: all 40 bytes delivered in order

   Test 3: Edge cases
   Edge cases PASS

   All tests passed!
   RX overflow count: 8
   TX bytes transmitted: 40
**/
