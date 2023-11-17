#include "Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    printf("\n-----------------------------\n");
    printf("Total Record(s) Found: %d\n", count);
    printf("-----------------------------\n");

    // Second pass to print the records
    for (int i = 0; i < table->size; i++) {
        Baggage *current = table->table[i];
        while (current != NULL) {
            printf("Record:\n");
            printf("  RFID Value: %s\n", current->RFIDValue);
            printf("  Location:   %s\n", current->Location);
            printf("-----------------------------\n");
            current = current->next;
        }
    }
    printf("You have reached the end of the record(s) :>\n");
}

// int main() {
//     // Create a new BaggageTable
//     BaggageTable *table = createBaggageTable(10); // Assuming createBaggageTable is a function that initializes a new BaggageTable

//     // Display the table
//     showBaggageTable(table);

//     // Free memory
//     freeBaggageTable(table); // Assuming freeBaggageTable is a function that frees all memory associated with the table

//     return 0;
// }