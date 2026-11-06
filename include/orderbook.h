
#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <stdbool.h>
#include <stddef.h>
#include "item.h"

typedef struct orderbook ORDER_BOOK;

ORDER_BOOK *orderbook_init(void);
void orderbook_delete(ORDER_BOOK **book_ptr);

bool orderbook_insert(ORDER_BOOK *book, ITEM *item);
void orderbook_process(ORDER_BOOK *book);

size_t orderbook_total_orders(const ORDER_BOOK *book);
bool orderbook_is_empty(const ORDER_BOOK *book);
void orderbook_print(const ORDER_BOOK *book);

ITEM *orderbook_get_best_bid(const ORDER_BOOK *book);
ITEM *orderbook_get_best_ask(const ORDER_BOOK *book);

size_t orderbook_bids_count(const ORDER_BOOK *book);
size_t orderbook_asks_count(const ORDER_BOOK *book);

#endif
