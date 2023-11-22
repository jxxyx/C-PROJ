#include "fileio.h"
#include <stdio.h>
#include <string.h>
#include "Database.h"

const char *queryTag(BaggageTable *table, const char *RFIDValue) {
    int hash = calculateHash(RFIDValue, table->size);
    Baggage *current = table->table[hash];

    while (current != NULL) { // while the current node is not null

        if (strcmp(current->RFIDValue, RFIDValue) == 0) { // if the RFIDValue is found
            printf("\n\t\t-----------------------------\n");
            printf("\t\tRecord found...\n");
            printf("\t\t%s : %s\n", RFIDValue ,current->Location);
            printf("\t\t-----------------------------\n");
            return current->Location; // return the location
        }

        current = current->next; // move to the next node
    }
    if (current == NULL){ // if the current node is null
        printf("\n\t\t-----------------------------\n");
        printf("\t\tRecord for %s not found...\n", RFIDValue);
        printf("\t\t-----------------------------\n");
    }

    return NULL;

}
