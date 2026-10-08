/**
   dbounce button problem :

   A hardware button generates multiple electrical transitions when pressed or released
   because of contact bounce.
   Implement logic that reports one valid press only when the button state has remained
   stable for a specified debounce interval.

   Tue Oct  6 22:16:12 PDT 2026
**/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define DEBOUNCE_MS 20

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define DEBOUNCE_MS 20

typedef struct {
    int raw_state;          // Latest GPIO value
    int stable_state;       // Debounced GPIO value
    uint64_t last_change;   // Time raw signal last changed
} Button;


/* Initialize button */
void button_init(Button *b, int initial_state, uint64_t now)
{
    b->raw_state = initial_state;
    b->stable_state = initial_state;
    b->last_change = now;
}


/* Return true when a valid button press is detected */
bool button_update(Button *b, int input, uint64_t now)
{
    /*
     * Raw GPIO change : Raw signal changed -- bouncing may be happening
     * Could be a real transition or contact bounce.
     */
    if (input != b->raw_state) {
        b->raw_state = input;
        b->last_change = now;

        printf("  Raw change -> %d at %llu ms\n",
               input,
               (unsigned long long)now);
    }

    /*
     * Has the raw state remained unchanged
     * for at least DEBOUNCE_MS?
     */
	 /*
     * Raw signal has remained unchanged for DEBOUNCE_MS.
     * Accept it as the real button state.
     */
    if ((now - b->last_change) >= DEBOUNCE_MS &&
        b->stable_state != b->raw_state) {

        b->stable_state = b->raw_state;

        printf("  Stable state -> %d at %llu ms\n",
               b->stable_state,
               (unsigned long long)now);

        /* Detect press: 0 -> 1 */
        if (b->stable_state == 1)
            return true;
    }

    return false;
}


int main(void)
{
    Button button;

    /*
     * Simulated GPIO input.
     *
     * Button starts at 0.
     *
     * Around 10-18 ms it bounces:
     *
     * 0 -> 1 -> 0 -> 1 -> 0 -> 1
     *
     * After 18 ms it remains HIGH.
     */

    uint64_t times[] = {
        0,
        10,
        12,
        14,
        16,
        18,
        20,
        25,
        30,
        35,
        38,
        40,
        50
    };

    int gpio[] = {
        0,      // 0 ms
        1,      // 10 ms  bounce
        0,      // 12 ms  bounce
        1,      // 14 ms  bounce
        0,      // 16 ms  bounce
        1,      // 18 ms  final transition
        1,
        1,
        1,
        1,
        1,      // 38 ms -> stable for 20 ms
        1,
        1
    };

    int count = sizeof(times) / sizeof(times[0]);

    button_init(&button, 0, 0);

    printf("Starting button debounce test\n\n");

    for (int i = 0; i < count; i++) {

        printf("time=%llu ms gpio=%d\n",
               (unsigned long long)times[i],
               gpio[i]);

        if (button_update(&button, gpio[i], times[i])) {
            printf("  *** BUTTON PRESS DETECTED ***\n");
        }
    }

    return 0;
}

/**
	Starting button debounce test

	time=0 ms gpio=0
	time=10 ms gpio=1
	  Raw change -> 1 at 10 ms
	time=12 ms gpio=0
	  Raw change -> 0 at 12 ms
	time=14 ms gpio=1
	  Raw change -> 1 at 14 ms
	time=16 ms gpio=0
	  Raw change -> 0 at 16 ms
	time=18 ms gpio=1
	  Raw change -> 1 at 18 ms
	time=20 ms gpio=1
	time=25 ms gpio=1
	time=30 ms gpio=1
	time=35 ms gpio=1
	time=38 ms gpio=1
	  Stable state -> 1 at 38 ms
	  *** BUTTON PRESS DETECTED ***
	time=40 ms gpio=1
	time=50 ms gpio=1
**/

/**
   Time (ms):  0   1   2   3   4   5   6 ........ 25
Signal:     0   1   0   1   0   1   1 ........ 1
                ^ bouncing ^

Actual interpretation:
            -----------| PRESSED
                       ^
             stable long enough

	The important idea is that you don't delay for 20 ms and block the CPU.
	Instead, whenever the raw GPIO changes, restart the debounce timer.

	timestamp     GPIO
	---------     ----
	0 ms           0

	10 ms          1  <-- possible press
	12 ms          0  <-- bounce
	14 ms          1  <-- bounce
	16 ms          0  <-- bounce
	18 ms          1  <-- last transition

	20 ms          1
	25 ms          1
	30 ms          1
	38 ms          1  <-- stable for 20 ms

	At 10 ms we do not immediately report a button press.
	Every bounce restarts the timer. The final transition happens at 18 ms, so:
	18 + 20 = 38 ms

	At 38 ms:

	raw_state    = 1
	stable_state = 0

	38 - 18 >= 20
	Therefore we accept:
	
	stable_state: 0 -> 1
	BUTTON PRESSED
**/
