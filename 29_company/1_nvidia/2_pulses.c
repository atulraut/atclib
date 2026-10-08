/**
   A digital signal is fed into the system. A pulse is one rising edge (0→1) followed by one falling edge (1→0).
   The system calls a callback on every edge (every change in the signal) and passes in information about that edge.
   Define and implement two user-facing APIs:
   - reset_count(): start counting pulses from this moment.
   - get_count(): return the number of full pulses since the last reset.
   A full pulse means both edges, 0→1 and then 1→0, happened after the reset.
   Also implement the edge callback that the system calls on each edge.

   gcc -std=c11 -Wall -Wextra -Werror pulse.c -o pulse
   Tue Oct  6 20:54:02 PDT 2026
**/

#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>

typedef enum {
    EDGE_RISING,
    EDGE_FALLING
} edge_t;

/* Number of complete pulses since reset */
static atomic_uint pulse_count = 0;

/*
 * true  = rising edge has occurred; waiting for falling edge
 * false = waiting for rising edge
 */
static atomic_bool rise_seen = false;


/*
 * Reset pulse counter.
 *
 * Important:
 * rise_seen is also cleared because a rising edge that happened
 * before reset must NOT be used to form a pulse after reset.
 */
void reset_count(void)
{
    atomic_store(&pulse_count, 0);
    atomic_store(&rise_seen, false);
}


/*
 * Return number of complete pulses since last reset.
 */
uint32_t get_count(void)
{
    return atomic_load(&pulse_count);
}


/*
 * System calls this function whenever an edge occurs.
 */
void edge_callback(edge_t edge)
{
    if (edge == EDGE_RISING) {

        printf("Rising edge\n");

        /* We have seen the first half of a pulse */
        atomic_store(&rise_seen, true);
    }
    else if (edge == EDGE_FALLING) {

        printf("Falling edge\n");

        /*
         * atomic_exchange:
         *
         * 1. Get old value of rise_seen
         * 2. Set rise_seen = false
         *
         * If old value was true, we have:
         *
         *      rising -> falling
         *
         * which is one complete pulse.
         */
        if (atomic_exchange(&rise_seen, false)) {
            atomic_fetch_add(&pulse_count, 1);
            printf("Complete pulse detected!\n");
        }
        else {
            printf("Ignoring falling edge: no rising edge after reset\n");
        }
    }
}


int main(void)
{
    printf("Reset counter\n");
    reset_count();

    printf("\n--- Pulse 1 ---\n");

    edge_callback(EDGE_RISING);
    edge_callback(EDGE_FALLING);

    printf("Count = %u\n", get_count());


    printf("\n--- Pulse 2 ---\n");

    edge_callback(EDGE_RISING);
    edge_callback(EDGE_FALLING);

    printf("Count = %u\n", get_count());


    printf("\n--- Start Pulse 3 ---\n");

    edge_callback(EDGE_RISING);

    /*
     * Reset happens in the middle of the pulse.
     *
     * Because the rising edge occurred BEFORE reset,
     * its falling edge must NOT count.
     */
    printf("\n*** RESET in middle of pulse ***\n");
    reset_count();

    edge_callback(EDGE_FALLING);

    printf("Count after reset = %u\n", get_count());


    printf("\n--- New full pulse after reset ---\n");

    edge_callback(EDGE_RISING);
    edge_callback(EDGE_FALLING);

    printf("Final count = %u\n", get_count());

    return 0;
}

/**
Suppose the signal does:
	             reset
               |
Signal:  0 ----1---------0------1------0----
              rise      fall   rise   fall
               |         |      |      |
               |         X      +------+
               |       don't      count
               |       count

If the rising edge happened before reset_count():
0 → 1
    |
  reset_count()
    |
    1 → 0
the falling edge after reset must not count as a pulse. reset_count() therefore clears:
rise_seen = false;

So that falling edge is ignored.
Now consider:

reset_count()

0 → 1       // EDGE_RISING
    rise_seen = true

1 → 0       // EDGE_FALLING
    rise_seen was true
    pulse_count++
    rise_seen = false

Now get_count() returns 1.
After another pair:

0 → 1
1 → 0

it returns 2.
Important concurrency issue
The above is good for explaining the state machine, but there is one deeper interview issue: reset_count() and edge_callback() must be synchronized as one logical state.
Separate atomic variables prevent data races, but they don't make this entire operation atomic:
	reset:
    count = 0;
    rise_seen = false;

	For example, an edge callback could run between those two operations.
	In production code, if reset_count() can race with the callback,
	I'd protect the complete state with a lock/critical section
	(or use a generation/epoch scheme if the callback is interrupt-context and cannot take a normal mutex).
    The core state machine is:

                     RISING
        +----------------------+
        |                      v
   WAIT_FOR_RISE          WAIT_FOR_FALL
        ^                      |
        |                      |
        +----------------------+
                 FALLING
              count++

	reset_count() always moves the machine to WAIT_FOR_RISE and sets the count to zero.
	For an embedded/kernel interview, this last concurrency point is likely the most interesting follow-up: what happens if reset_count() occurs exactly while an edge callback is executing?

**/
