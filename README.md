# Limit Order Book in C

A simplified limit order book implemented in C99. The program reads buy and sell orders from a text file and attempts to match each incoming order against orders on the opposite side.

This personal project is part of my studies in Computer Science at the University of São Paulo (ICMC-USP). I use it to practice data structures, algorithms, memory management, and software design in C.

## Implementation

Orders contain an ID, side, price, and quantity. The order book keeps buy and sell orders in separate dynamically allocated singly linked FIFO queues. When an order arrives, the program compares it with orders at the front of the opposite queue and reduces quantities for any matches. Fully filled orders are removed; any remaining quantity is added to the queue for its side.

The queue is not sorted by price. Matching considers the front order first, even if a later order has a better price. The program currently does not print the book or report executed trades. Memory is managed with `malloc()` and `free()`, and the public interfaces use opaque structures for items, queues, and the order book.

For an incoming order that matches against `k` queued orders, the matching loop takes O(k). Enqueue and dequeue are O(1). The implementation does not provide arbitrary order lookup or removal.

## Project files

```text
include/       Public headers for items, queues, and the order book
src/main.c     Command-line entry point and file input
src/item.c     Order representation and accessors
src/queue.c    Dynamic linked FIFO queue
src/orderbook.c Order book and matching logic
```

## Build and run

Compile with GCC and C99:

```sh
gcc -std=c99 -Wall -Wextra -Iinclude src/main.c src/item.c src/queue.c src/orderbook.c -o orderbook
```

Run the program with an order file:

```sh
./orderbook orders.txt
```

## Input format

Each line contains a side character, order ID, price, and quantity, separated by whitespace. `C` or `c` means buy; any other character is treated as sell.

```text
C 101 10.50 20
V 202 10.25 8
C 303 10.00 5
```

## Possible next steps

These are ideas for further study and are not implemented yet:

- Add a hash table to find orders by ID in O(1) average time. Cancellation would still need an efficient way to remove an order from its queue; a lookup table alone does not make arbitrary removal O(1).
- Study heaps for price-based prioritization. Preserving FIFO order among equal prices and supporting arbitrary cancellation would require additional mechanisms.
- Organize orders into price levels, with a queue at each price.
- Compare alternative implementations and analyze their time complexity under defined workloads.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for the full text.
