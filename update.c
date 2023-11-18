#include <stdio.h>
#include <stddef.h>
#include "Database.h"
#include "update.h"

// Function to update a row in the hash map-based database
void updateRow(BaggageTable *table, const char* RFIDValue, const char* Location) {
    int hash = calculateHash(RFIDValue, table->size);
    Baggage *current = table->table[hash];

    while (current != NULL) {
        printf("Checking row with ID %s\n", current->RFIDValue);  // Print the ID of the row being checked
        if (strcmp(current->RFIDValue, RFIDValue) == 0) {
            // Update the airport code if the ID matches
            strncpy(current->Location, Location, 4);
            printf("\n-----------------------------\n");
            printf("RFID %s updated with new Airport Code %s\n", RFIDValue, Location);
            printf("-----------------------------\n");
            return;  // Exit the function after updating
        }
        current = current-> next;
    }

    printf("\n-----------------------------\n");
    printf("Record RFID %s not found!\n", RFIDValue);
    printf("-----------------------------\n");
}
