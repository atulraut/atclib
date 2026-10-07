**
 You have a number of items ranging from 0, N-1 (N is a very big number)

 Your task is to be able to do the following functions in O(1) time at best:
 1. set_item_price : Set the price of item
 2. get_item_price : Get the price of the item
 3. set_all : Set the prices of all items at once

 Tue Oct  6 22:16:27 PDT 2026
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int price;
    uint64_t version;
} Item;

typedef struct {
    Item *items;
    size_t n;

    int all_price;
    uint64_t all_version;

    uint64_t version;
} PriceDB;

PriceDB *create_db(size_t n, int initial_price) {
    PriceDB *db = malloc(sizeof(*db));
    if (!db)
        return NULL;

    db->items = calloc(n, sizeof(*db->items));
    if (!db->items) {
        free(db);
        return NULL;
    }

    db->n = n;
    db->all_price = initial_price;
    db->version = 1;
    db->all_version = 1;

    return db;
}

/* O(1) */
void set_item_price(PriceDB *db, size_t item, int price) {
    if (!db || item >= db->n)
        return;

    db->version++;

    db->items[item].price = price;
    db->items[item].version = db->version;
}

/* O(1) */
int get_item_price(PriceDB *db, size_t item) {
    if (!db || item >= db->n)
        return -1;

    /*
     * Was this item individually updated
     * AFTER the latest set_all()?
     */
    if (db->items[item].version > db->all_version)
        return db->items[item].price;

    return db->all_price;
}

/* O(1) */
void set_all(PriceDB *db, int price) {
    if (!db)
        return;

    db->version++;

    db->all_price = price;
    db->all_version = db->version;
}

void destroy_db(PriceDB *db) {
    if (!db)
        return;

    free(db->items);
    free(db);
}

int main(void) {
    PriceDB *db = create_db(1000000, 0); // O(N) if array is big, better to go with hash map

    if (!db)
        return 1;

    set_item_price(db, 10, 100);
    set_item_price(db, 20, 200);

    printf("item 10 = %d\n", get_item_price(db, 10));
    printf("item 20 = %d\n", get_item_price(db, 20));

    printf("\nset_all(50)\n");
    set_all(db, 50);

    printf("item 10 = %d\n", get_item_price(db, 10));
    printf("item 20 = %d\n", get_item_price(db, 20));
    printf("item 30 = %d\n", get_item_price(db, 30));

    printf("\nset_item_price(20, 300)\n");
    set_item_price(db, 20, 300);

    printf("item 10 = %d\n", get_item_price(db, 10));
    printf("item 20 = %d\n", get_item_price(db, 20));
    printf("item 30 = %d\n", get_item_price(db, 30));

    destroy_db(db);
    return 0;
}

/**
	item 10 = 100
	item 20 = 200

	set_all(50)
	item 10 = 50
	item 20 = 50
	item 30 = 50

	set_item_price(20, 300)
	item 10 = 50
	item 20 = 300
	item 30 = 50
**/
