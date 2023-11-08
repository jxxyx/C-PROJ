#include "query.h"
#include <stdio.h>
#include <string.h>


const char *retrieveBaggageTable(BaggageTable *table, const char *RFIDValue) {

    int hash = calculateHash(RFIDValue, table->size);
    Baggage *current = table->table[hash];

    while (current != NULL) {

        if (strcmp(current->RFIDValue, RFIDValue) == 0) {
            printf("Record found...\n");
            printf("%s : %s\n", RFIDValue ,current->Location);
            return current->Location;
        }

        current = current->next;
    }
    if (current == NULL){
        printf("Record for %s not found...\n", RFIDValue);
    }

    return NULL;

}
