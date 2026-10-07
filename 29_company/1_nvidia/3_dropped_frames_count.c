/**
    You work on an NVIDIA video streaming system where camera frames arrive as packets over the network.
    The system processes frames in real time but has limited capacity to handle bursts of frames.
    If too many frames arrive too close together, some frames get dropped due to capacity limits.

        1. Frames arrive at integer seconds (packet arrival timestamps).
        2. The system processes frames in fixed 1 second batches.
        3. Each second can handle up to capacity frames.
        4. Extra frames arriving in the same second beyond capacity are dropped.

Task:
    1. Given a sorted list arrivalTimes (integers) and an integer capacity, return the total number of dropped frames.

Example:

    Input:
        arrivalTimes = [1, 1, 1, 2, 2, 3]
        capacity = 2

    Output: 1

    Explanation:
        Second 1: 3 frames arrive, process 2, drop 1
        Second 2: 2 frames arrive, process all
        Second 3: 1 frame arrives, process all

        Total dropped = 1

// Follow-up for question 1:

// Background:

//     Now the system supports flexible, continuous processing similar to NVIDIA’s streaming pipelines:
//     Frames arrive with timestamps as floating-point numbers (seconds).
//     The system can process up to capacity frames in any sliding window of windowSize seconds.
//     If the number of frames processed in the last windowSize seconds equals capacity, new frames arriving within that window are dropped.


// Task:
//     Given a sorted list arrivalTimes (floats), an integer capacity, and a float windowSize, return the total number of dropped frames.

   Tue Oct  6 21:55:36 PDT 2026
**/

#include <stdio.h>
#include <stdlib.h>

int dropped_frames(int arrivalTimes[], int n, int capacity) {
    if (n <= 0 || capacity <= 0)
        return (capacity <= 0) ? n : 0;

    int dropped = 0;
    int count = 1;

    for (int i = 1; i < n; i++) {

        if (arrivalTimes[i] == arrivalTimes[i - 1]) {
            count++;
        } else {
            // Previous second is complete
            if (count > capacity)
                dropped += count - capacity;

            count = 1;
        }
    }

    // Handle last group
    if (count > capacity)
        dropped += count - capacity;

    return dropped;
}

int test_1 (void) {
    int arrivalTimes[] = {1, 1, 1, 2, 2, 3};
    int n = sizeof(arrivalTimes) / sizeof(arrivalTimes[0]);
    int capacity = 2;

    printf("Dropped frames = %d\n",
           dropped_frames(arrivalTimes, n, capacity));

    return 0;
}

// follow up part :
/**
  // Example:
//     Input:
//         arrivalTimes = [0.1, 1.3, 1.6, 2.0, 2.1, 2.2]
//         capacity = 3
//         windowSize = 2

//     Output: 2

//     Explanation:
//         Frames at 0.1, 1.3, 1.6 → processed (3 frames in last windowSize=2 seconds)
//         Frame at 2.0 → dropped (capacity reached in window [0, 2])
//         Frame at 2.1 → dropped (capacity reached in window [0.1, 2.1])
//         Frame at 2.2 → processed (only 3 frames in window [0.2, 2.2])

**/
int dropped_frames_sliding(const double arrivalTimes[],
                           int n,
                           int capacity,
                           double windowSize)
{
    if (n <= 0)
        return 0;

    if (capacity <= 0)
        return n;

    if (windowSize <= 0.0)
        return 0;

    /*
     * Queue stores ACCEPTED frame timestamps only.
     *
     * Maximum possible size = n.
     */
    double *queue = malloc(n * sizeof(double));

    if (queue == NULL)
        return -1;

    int head = 0;
    int tail = 0;
    int dropped = 0;

    for (int i = 0; i < n; i++) {

        double current = arrivalTimes[i];

        /*
         * Remove frames outside the sliding window.
         *
         * Window:
         *     (current - windowSize, current]
         */
        while (head < tail &&
               current - queue[head] >= windowSize) {
            head++;
        }

        /*
         * Number of accepted frames currently
         * inside the window.
         */
        int frames_in_window = tail - head;

        if (frames_in_window < capacity) {

            /* Accept/process this frame */
            queue[tail++] = current;

        } else {

            /* Capacity reached */
            dropped++;
        }
    }

    free(queue);

    return dropped;
}

int test_2 (void)
{
    double arrivalTimes[] = {
        1.0,
        1.1,
        1.2,
        2.0,
        2.1
    };

    int n = sizeof(arrivalTimes) / sizeof(arrivalTimes[0]);

    int capacity = 2;
    double windowSize = 1.0;

    int dropped =
        dropped_frames_sliding(arrivalTimes,
                               n,
                               capacity,
                               windowSize);

    printf("Dropped frames = %d\n", dropped);

    return 0;
}

int main () {
  test_1();
  test_2();
}
