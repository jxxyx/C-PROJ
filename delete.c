#include "delete.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Database.h"

// Function to delete a row from the hash map-based database
void deleteRow(BaggageTable *table, const char* RFIDValue, const char* Location) {
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
            free(current->Location);
            free(current);

            printf("The record of Key= %s is successfully deleted\n", RFIDValue); // Deletion successful
            return; // Exit the function after deletion
        }
        previous = current;
        current = current->next;
    }

    printf("There is no record with Key= %s found in the database\n", RFIDValue); // Deletion unsuccessful
}

// Create a function to test the deleteRow function, remove this function when submitting the code
void testDelete() {
    // Create a new hash map-based database
    BaggageTable *table = createBaggageTable(10);

    // Add some Baggage instances to the table
    insertRecord(table, "020", "SIN");  // Assuming you have a function to add a row
    insertRecord(table, "021", "ICN");

    // Delete the row from the database
    deleteRow(table, "020", "SIN");

    // Try to find the deleted record
    const char *record = retrieveBaggageTable(table, "020");

    // Check if the row was successfully deleted
    if (record == NULL) {
        printf("Test successful: Row has been deleted.\n");
    } else {
        printf("Test failed: Row was not deleted.\n");
    }
}

int main() {
    testDelete();
    return 0;
}
