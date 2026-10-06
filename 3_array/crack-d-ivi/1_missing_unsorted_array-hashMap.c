/**

    Remove duplicates from unsorted array

    Folsom CA,
    Date : Tue Sep 29 08:42:17 PDT 2026

*/

#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 101

typedef struct HashNode {
    int key;
    struct HashNode *next;
} HashNode_t;

typedef struct {
    HashNode_t *bucket[HASH_SIZE];
} HashSet_t;


/* Handle negative integers too */
static unsigned int hash(int key) {
    unsigned int x = (unsigned int)key;
    return x % HASH_SIZE;
}


void hashSetInit(HashSet_t *set) {
    for (int i = 0; i < HASH_SIZE; i++)
        set->bucket[i] = NULL;
}


/* Return 1 if found, otherwise 0 */
int hashSetContains(HashSet_t *set, int key) {
    unsigned int index = hash(key);

    HashNode_t *node = set->bucket[index];

    while (node != NULL) {
        if (node->key == key)
            return 1;
        node = node->next;
    }
    return 0;
}


/* Return 0 on success, -1 on malloc failure */
int hashSetInsert(HashSet_t *set, int key) {
    unsigned int index = hash(key);
    HashNode_t *node = malloc(sizeof(*node));

    if (node == NULL)
        return -1;

    node->key = key;
    node->next = set->bucket[index];
    set->bucket[index] = node;

    return 0;
}


void hashSetDestroy(HashSet_t *set) {
    for (int i = 0; i < HASH_SIZE; i++) {

        HashNode_t *node = set->bucket[i];

        while (node != NULL) {
            HashNode_t *next = node->next;
            free(node);
            node = next;
        }
        set->bucket[i] = NULL;
    }
}


/*
 * Remove duplicates in-place.
 *
 * Example:
 *
 * [4, 2, 4, 1, 2, 3, 1]
 *
 * becomes:
 *
 * [4, 2, 1, 3, ...]
 *
 * Return value = 4
 */
int removeDuplicates(int *nums, int numsSize) {
    if (nums == NULL || numsSize <= 0)
        return 0;

    HashSet_t set;
    hashSetInit(&set);

    int write = 0;

    for (int read = 0; read < numsSize; read++) {
        if (!hashSetContains(&set, nums[read])) {       // if exist, dont do anything, else insert into hashMap
            if (hashSetInsert(&set, nums[read]) != 0) {
                hashSetDestroy(&set);
                return -1;
            }
            nums[write++] = nums[read];
        }
    }
    hashSetDestroy(&set);

    return write;
}


int main(void) {
    int nums[] = {4, 2, 4, 1, 2, 3, 1, 10, 10, -5, -5};

    int n = sizeof(nums) / sizeof(nums[0]);
    int newSize = removeDuplicates(nums, n);

    if (newSize < 0) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Unique elements:\n");
    for (int i = 0; i < 11; i++)
        printf("%d ", nums[i]);
    printf("\n");

    return 0;
}
