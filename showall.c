#include "Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showBaggageTable(BaggageTable *table) {
    for (int i = 0; i < table->size; i++) {
        Baggage *baggage = table->table[i];
        while (baggage != NULL) {
            printf("RFIDValue: %s, Location: %s\n", baggage->RFIDValue, baggage->Location);
            baggage = baggage->next;
        }
    }
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