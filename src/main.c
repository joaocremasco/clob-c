#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "queue.h"
#include "orderbook.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso incorreto!\nSintaxe: %s <arquivo_de_ordens.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo de ordens");
        return EXIT_FAILURE;
    }

    ORDER_BOOK *book = orderbook_init();
    if (book == NULL) {
        fclose(fp);
        return EXIT_FAILURE;
    }

    char type;
    int id, qty;
    double price;
    
    while(fscanf(fp, " %c %d %lf %d", &type, &id, &price, &qty) == 4){
      TRANSACTION_TYPE t_type = (type == 'C' || type == 'c') ? PURCHASE : SALE;

      ITEM *item = item_create(id, t_type, price, qty);
      orderbook_insert(book, item);
  }
    

    fclose(fp);
    orderbook_delete(&book);
    return EXIT_SUCCESS;
}
