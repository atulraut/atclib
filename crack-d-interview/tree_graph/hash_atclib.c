#include <stdio.h>
#include <stdlib.h>
#define HASH_MAP_SIZE 10
typedef struct node {
        int data;
        struct node *next;
}node;

node *hash_map[HASH_MAP_SIZE];
#define is_valid_key(key) \
        if (key >= HASH_MAP_SIZE) { \
                printf("wrong key value\n"); \
                        return; \
        }

#define is_valid_key_value(key) \
        if (key >= HASH_MAP_SIZE) { \
                printf("wrong key value pair\n"); \
                return -1; \
        }

node *create_node(int val) {
        node *temp = malloc(sizeof(*temp));
        temp->data = val;
        temp->next = NULL;
        return temp;
}

void put(int key, int value) {
        is_valid_key(key);
        if (!hash_map[key]) {
                hash_map[key] = create_node(value);
                return;
        } else {
                node *head = hash_map[key];
                node *new_node = create_node(value);
                new_node->next = head;
                hash_map[key] = new_node;
        }
}

void print_all(int key) {
        is_valid_key(key);
        node *temp = hash_map[key];
        if (!temp)
                return;
        while (temp) {
                printf("[print_all] key->[%d] value->[%d] Addr->[%p]\n",key, temp->data, temp);
                temp = temp->next;
        }
}
int get(int key) {
        is_valid_key_value(key);
        node *temp = hash_map[key];
        if (!temp)
                return -1;
        return temp->data;
}

int remove_value(int key) {
        int data;
        node *prev;
        is_valid_key_value(key);
        node *head = hash_map[key];
        node *temp = head;
        if (!temp)
                return -1;
        if (head) {
                head = head->next;
        }
        hash_map[key] = head;
        data = temp->data;
        free(temp);
        return data;
}

int main() {
        int count = 0, i=0, j=0;
        int key, value;
        while(count != 10) {
                int key = i++;//rand()%10;
                int value = ++j;//rand();
                if (key == 35)
                        printf("++++++++++++++key %d value %d\n", key, value);
                printf("[main] key %d value %d \n", key, value);
                put(key, value);
                count++;
        }
        count = 0;
        printf("what the hell\n");
        print_all(9);
        while(count != 10) {
                printf("%d\n", remove_value(count));
                count++;
        }
}
