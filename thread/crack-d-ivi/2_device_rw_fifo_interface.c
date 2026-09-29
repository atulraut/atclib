/**

    Program: Write a simple device FIFO read/write interface
    Ref: https://chatgpt.com/c/6ab1cbb9-de70-83e8-82cb-5dfbf2da260d

	0xA0001000   DATA register
	0xA0001004   STATUS register

	STATUS:
	bit 0 = FIFO FULL
	bit 1 = FIFO EMPTY

        CPU                        DEVICE
         |                            |
         | read STATUS               |
         |--------------------------->|
         |                            |
         |      FULL / EMPTY          |
         |<---------------------------|
         |                            |
         | read/write DATA            |
         |--------------------------->|
         |                            |
         |                       +----------+
         |                       | HW FIFO  |
         |                       +----------+

		You would map the MMIO resource and use Linux MMIO accessors such as:
		readl(base + FIFO_STATUS_OFFSET);
		writel(data, base + FIFO_DATA_OFFSET);

	Mon Sep 28 20:13:30 PDT 2026
	Folsom, CA
**/

#include <stdint.h>
#include <stddef.h>

#define FIFO_DATA_REG    (*(volatile uint32_t *)0xA0001000)
#define FIFO_STATUS_REG  (*(volatile uint32_t *)0xA0001004)

#define FIFO_FULL        (1U << 0)
#define FIFO_EMPTY       (1U << 1)

/*
 * Write one word to device FIFO.
 *
 * Return:
 *   0  success
 *  -1  FIFO full
 */
int fifo_write(uint32_t data) {
    /* Check whether device can accept data */
    if (FIFO_STATUS_REG & FIFO_FULL)
        return -1;

    /* Write data into hardware FIFO */
    FIFO_DATA_REG = data;

    return 0;
}

/*
 * Read one word from device FIFO.
 *
 * Return:
 *   0  success
 *  -1  FIFO empty
 */
int fifo_read(uint32_t *data) {
    if (data == NULL)
        return -1;

    /* Check whether device has data */
    if (FIFO_STATUS_REG & FIFO_EMPTY)
        return -1;

    /* Read data from hardware FIFO */
    *data = FIFO_DATA_REG;

    return 0;
}

/**
	What if I want write() to wait until FIFO
	space becomes available?

**/
#define FIFO_TIMEOUT 1000000U

int fifo_write_wait(uint32_t data) {
    uint32_t timeout = FIFO_TIMEOUT;

    while (FIFO_STATUS_REG & FIFO_FULL) {

        if (--timeout == 0)
            return -1;
    }

    FIFO_DATA_REG = data;

    return 0;
}

/**
          +---------------+
          | FIFO empty ?  |
          +---------------+
            |          |
           yes         no
            |          |
            v          v
          retry     read DATA
            |
            v
       timeout?
        |     |
       yes    no
        |      |
        v      +-----> retry
      error
**/
int fifo_read_wait(uint32_t *data) {
    uint32_t timeout = FIFO_TIMEOUT;

    if (data == NULL)
        return -1;

    while (FIFO_STATUS_REG & FIFO_EMPTY) {

        if (--timeout == 0)
            return -1;
    }

    *data = FIFO_DATA_REG;

    return 0;
}

/**
	  Application
		 |
		 | fifo_write_buf()
		 v
	+-------------+
	| FIFO Driver |
	+-------------+
		 |
		 | check STATUS
		 | write DATA
		 v
	+-------------+
	| HW FIFO     |
	|             |
	| [10]        |
	| [20]        |
	| [30]        |
	+-------------+
**/
int fifo_write_buf(const uint32_t *buf, size_t count) {
    if (buf == NULL)
        return -1;

    for (size_t i = 0; i < count; i++) {

        if (fifo_write_wait(buf[i]) != 0)
            return -1;
    }

    return 0;
}

int fifo_read_buf(uint32_t *buf, size_t count) {
    if (buf == NULL)
        return -1;

    for (size_t i = 0; i < count; i++) {

        if (fifo_read_wait(&buf[i]) != 0)
            return -1;
    }

    return 0;
}

/**
	Instead of busy polling can use Interrupts :
	I would use device interrupts. When RX data arrives, the device generates an RX interrupt.
	When TX FIFO space becomes available, it generates a TX interrupt.
	The interrupt handler acknowledges the interrupt and wakes the thread
	waiting for the corresponding condition.

	Application
		 |
		 | read()
		 v
	Driver
		 |
		 | RX FIFO empty
		 v
	 sleep / wait queue
		 .
		 .
		 .
	Device receives data
		 |
		 v
	RX interrupt
		 |
		 v
	ISR
		 |
		 v
	wake reader
		 |
		 v
	read DATA register

	This is better because :
	Polling:

	CPU -> STATUS -> STATUS -> STATUS -> STATUS -> STATUS
		   busy      busy      busy      busy

	Interrupt:

	CPU -> sleep
			.
			.
			.
	Device -> IRQ -> CPU wakes
**/
#define FIFO_DATA_OFFSET    0x00
#define FIFO_STATUS_OFFSET  0x04

#define FIFO_FULL           BIT(0)
#define FIFO_EMPTY          BIT(1)

struct fifo_dev {
    void __iomem *base;
};

// Below code is NOT thread safe, need spinlock APIs to protect
static int hw_fifo_write(struct fifo_dev *dev, uint32_t data) {
    uint32_t status;

    status = readl(dev->base + FIFO_STATUS_OFFSET);

    if (status & FIFO_FULL)
        return -EAGAIN;

    writel(data, dev->base + FIFO_DATA_OFFSET);

    return 0;
}

static int hw_fifo_read(struct fifo_dev *dev, uint32_t *data) {
    uint32_t status;

    if (!data)
        return -EINVAL;

    status = readl(dev->base + FIFO_STATUS_OFFSET);

    if (status & FIFO_EMPTY)
        return -EAGAIN;

    *data = readl(dev->base + FIFO_DATA_OFFSET);

    return 0;
}
