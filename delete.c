#include "delete.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Database.h"

// Function to delete a row from the hash map-based database
void deleteRow(BaggageTable *table, const char* RFIDValue) { // Removed Location parameter to meet Brief
    int hash = calculateHash(RFIDValue, table->size); // Calculate the index based on the ID
    Baggage *current = table->table[hash];
    Baggage *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->RFIDValue, RFIDValue) == 0) {
            // Remove the row if the ID matches
            if (previous == NULL) {
                // If the first node matches, update the bucket pointer
                table->table[hash] = current->next;
            } else {
                previous->next = current->next;
            }

            // Free memory associated with the node and the airport code
            free(current->RFIDValue);
            free(current);

            printf("\n\t\t-----------------------------\n");
            printf("\t\tRecord RFID %s deleted successfully!\n", RFIDValue); // Deletion successful
            printf("\t\t-----------------------------\n");
            return; // Exit the function after deletion
        }
        previous = current;
        current = current->next;
    }
    printf("\t\t\n-----------------------------\n");
    printf("\t\tRecord RFID %s not found!\n", RFIDValue); // Deletion unsuccessful
    printf("\t\t-----------------------------\n");
}
