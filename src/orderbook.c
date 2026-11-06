#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "item.h"
#include "queue.h"
#include "orderbook.h"

struct orderbook{
  QUEUE *bids;
  QUEUE *asks;
};

ORDER_BOOK *orderbook_init(void){
  ORDER_BOOK *book = malloc(sizeof(*book));
  if(book == NULL)
    return NULL;

  book->bids = queue_create();
  book->asks = queue_create();

  if(book->bids == NULL || book->asks == NULL){
    queue_delete(&(book->bids));
    queue_delete(&(book->asks));
    free(book);
    return NULL;
  }
  return book;
}

void orderbook_delete(ORDER_BOOK **book_ptr){
  if(book_ptr == NULL || *book_ptr == NULL)
    return;

  queue_delete(&((*book_ptr)->asks));
  queue_delete(&((*book_ptr)->bids));

  free(*book_ptr);
  *book_ptr = NULL;
}

bool orderbook_insert(ORDER_BOOK *book, ITEM *item) {
if (book == NULL || item == NULL)
  return false;

switch (item_get_type(item)) {

  case PURCHASE: {
    while (!queue_is_empty(book->asks) &&
      item_get_quantity(item) > 0) {

      ITEM *top_ask = queue_front(book->asks);

      if (item_get_price(top_ask) > item_get_price(item))
        break;

      int qty_incoming = item_get_quantity(item);
      int qty_ask = item_get_quantity(top_ask);

      int traded = (qty_incoming < qty_ask)
        ? qty_incoming : qty_ask;

      item_set_quantity(item, qty_incoming - traded);
      item_set_quantity(top_ask, qty_ask - traded);

      if (item_get_quantity(top_ask) == 0) {
        ITEM *removed = queue_dequeue(book->asks);
        item_delete(&removed);
      }
    }

    if (item_get_quantity(item) > 0)
      queue_enqueue(book->bids, item);
    else
      item_delete(&item);

    break;
  }

  case SALE: {
    while (!queue_is_empty(book->bids) &&
      item_get_quantity(item) > 0) {
      
      ITEM *top_bid = queue_front(book->bids);

      if(item_get_price(top_bid) < item_get_price(item))
        break;


      int qty_incoming = item_get_quantity(item);
      int qty_bid = item_get_quantity(top_bid);

      int traded = (qty_incoming < qty_bid)
        ? qty_incoming : qty_bid;

      item_set_quantity(item, qty_incoming - traded);
      item_set_quantity(top_bid, qty_bid - traded);

      if (item_get_quantity(top_bid) == 0) {
        ITEM *removed = queue_dequeue(book->bids);
        item_delete(&removed);
      }
    }
      if (item_get_quantity(item) > 0)
        queue_enqueue(book->asks, item);
      else
        item_delete(&item);

      break;
    }

    default:
      return false;
  }

    return true;
}

ITEM *orderbook_get_best_bid(const ORDER_BOOK *book) {
    return (book == NULL || queue_is_empty(book->bids))
           ? NULL : queue_front(book->bids);
}

ITEM *orderbook_get_best_ask(const ORDER_BOOK *book) {
    return (book == NULL || queue_is_empty(book->asks))
           ? NULL : queue_front(book->asks);
}

bool orderbook_is_empty(const ORDER_BOOK *book) {
    return (book == NULL)
           ? true
           : queue_is_empty(book->bids) &&
             queue_is_empty(book->asks);
}

size_t orderbook_bids_count(const ORDER_BOOK *book) {
    return (book != NULL) ? queue_size(book->bids) : 0;
}

size_t orderbook_asks_count(const ORDER_BOOK *book) {
    return (book != NULL) ? queue_size(book->asks) : 0;
}

size_t orderbook_total_orders(const ORDER_BOOK *book) {
    return (book != NULL)
           ? queue_size(book->bids) + queue_size(book->asks)
           : 0;
}

