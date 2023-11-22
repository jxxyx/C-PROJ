#include "Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a function to read DB txt file

void showBaggageTable(BaggageTable *table) {
    int count = 0;

    // First pass to count the records
    for (int i = 0; i < table->size; i++) {
        Baggage *current = table->table[i];
        while (current != NULL) {
            current = current->next;
            count++;
        }
    }

    printf("\n\t\t----------------------------------------\n");
    printf("\t\tTotal Record(s) Found: %d\n", count);
    printf("\t\t----------------------------------------\n");

    // Second pass to print the records
    for (int i = 0; i < table->size; i++) {
        Baggage *current = table->table[i];
        while (current != NULL) {
            // printf("\t\tRecord:\n");
            printf("  \t\tRFID Value: %s : %s\n", current->RFIDValue, current->Location);
            printf("\t\t----------------------------------------\n");
            current = current->next;
        }
    }
    printf("\t\tYou have reached the end of the record(s) :>\n");
}