#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>

typedef enum { PURCHASE, SALE } TRANSACTION_TYPE;
typedef struct item ITEM; // Opaque type

ITEM *item_create(int id, TRANSACTION_TYPE type, double price, int quantity);
void item_delete(ITEM **item_ptr);

// Controlled Getters and Setters
int item_get_id(const ITEM *item);
double item_get_price(const ITEM *item);
int item_get_quantity(const ITEM *item);
TRANSACTION_TYPE item_get_type(const ITEM *item);
void item_set_quantity(ITEM *item, int new_quantity);

#endif
