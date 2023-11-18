#include "Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a function to read DB txt file

const char *showAll(BaggageTable *table) {
    int count = 0;
    printf("\nRFIDValue : Location\n");
    for (int i = 0; i < table->size; i++) {
        Baggage *baggage = table->table[i];
        while (baggage != NULL) {
            printf("RFID %4s : %s\n", baggage->RFIDValue, baggage->Location);
            baggage = baggage->next;
            count++;
            }
        }
    printf("\n-----------------------------\n");
    printf("Total Record(s) Found: %d\n", count);
    printf("-----------------------------\n");
}
