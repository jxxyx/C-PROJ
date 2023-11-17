#include <stdio.h>
#include <stddef.h>
#include "Database.h"
#include "update.h"
#include "fileio.h"

// Function to update a row in the hash map-based database
void updateRow(BaggageTable *table, const char* RFIDValue, const char* Location) {
    int hash = calculateHash(RFIDValue, table->size);
    Baggage *current = table->table[hash];

    while (current != NULL) {
        printf("Checking row with ID %s\n", current->RFIDValue);  // Print the ID of the row being checked
        if (strcmp(current->RFIDValue, RFIDValue) == 0) {
            // Update the airport code if the ID matches
            strncpy(current->Location, Location, 4);
            printf("Row with ID %s updated with new airport code %s\n", RFIDValue, Location);
            writeTableToFile(table, "BaggageInfoEZDB.txt");
            return;  // Exit the function after updating
        }
        current = current-> next;
    }

    printf("Row with ID %s not found in the database\n", RFIDValue);
}  

