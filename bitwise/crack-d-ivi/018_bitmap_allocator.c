/**

	Implement a bitmap allocator

	Tue Sep 29 07:09:18 PDT 2026
	Folsom, CA, USA
**/

#include <stdio.h>
#include <stdint.h>

#define NUM_BLOCKS  64
#define BITS_PER_BYTE 8
#define BITMAP_SIZE ((NUM_BLOCKS + BITS_PER_BYTE - 1) / BITS_PER_BYTE)

typedef struct {
    uint8_t bitmap[BITMAP_SIZE];
} bitmap_allocator_t;

void bitmap_init(bitmap_allocator_t *allocator) {
    for (int i = 0; i < BITMAP_SIZE; i++)
        allocator->bitmap[i] = 0;
}

static int bit_is_set(bitmap_allocator_t *allocator, int bit) {
    int byte_index = bit / 8;
    int bit_index  = bit % 8;

    return (allocator->bitmap[byte_index] & (1U << bit_index)) != 0;
}

static void set_bit(bitmap_allocator_t *allocator, int bit) {
    int byte_index = bit / 8;
    int bit_index  = bit % 8;

    allocator->bitmap[byte_index] |= (uint8_t)(1U << bit_index);
}

static void clear_bit(bitmap_allocator_t *allocator, int bit) {
    int byte_index = bit / 8;
    int bit_index  = bit % 8;

    allocator->bitmap[byte_index] &= (uint8_t)~(1U << bit_index);
}

int bitmap_alloc(bitmap_allocator_t *allocator) {
    for (int i = 0; i < NUM_BLOCKS; i++) {

        if (!bit_is_set(allocator, i)) {
            set_bit(allocator, i);
            return i;
        }
    }
    return -1;  /* no free blocks */
}

int bitmap_free(bitmap_allocator_t *allocator, int block) {
    if (block < 0 || block >= NUM_BLOCKS)
        return -1;

    if (!bit_is_set(allocator, block))
        return -1;  /* double free / already free */

    clear_bit(allocator, block);
    return 0;
}

int main(void) {
    bitmap_allocator_t allocator;

    bitmap_init(&allocator);

    int a = bitmap_alloc(&allocator);
    int b = bitmap_alloc(&allocator);
    int c = bitmap_alloc(&allocator);

    printf("Allocated: %d %d %d\n", a, b, c);
    bitmap_free(&allocator, b);
    int d = bitmap_alloc(&allocator);

    printf("Allocated again: %d\n", d);
    return 0;
}
