#include <stdlib.h>
#include "item.h"

struct item {
    int id;
    TRANSACTION_TYPE type;
    double price;
    int quantity;
};

ITEM *item_create(int id, TRANSACTION_TYPE type, double price, int quantity) {
    ITEM *item = malloc(sizeof(*item));

    if (item == NULL)
        return NULL;

    item->id = id;
    item->type = type;
    item->price = price;
    item->quantity = quantity;

    return item;
}

void item_delete(ITEM **item_ptr) {
    if (item_ptr == NULL || *item_ptr == NULL)
        return;

    free(*item_ptr);
    *item_ptr = NULL;
}

// Getters

int item_get_id(const ITEM *item) {
    return item->id;
}

double item_get_price(const ITEM *item) {
    return item->price;
}

int item_get_quantity(const ITEM *item) {
    return item->quantity;
}

TRANSACTION_TYPE item_get_type(const ITEM *item) {
    return item->type;
}

// Setter

void item_set_quantity(ITEM *item, int new_quantity) {
    item->quantity = new_quantity;
}
