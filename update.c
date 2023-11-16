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
            printf("Row with ID %s updated with new airport code %s\n", RFIDValue, Location);
            return;  // Exit the function after updating
        }
        current = current-> next;
    }

    printf("Row with ID %s not found in the database\n", RFIDValue);
}  

// Comment out the testUpdateRow function and main below if you do not want a test run
// Function to test update feature, updating a row in the hash map-based database
void testUpdateRow() {
    // Create a BaggageTable instance
    BaggageTable *table = createBaggageTable(10);  // Assuming you have a function to create a BaggageTable

    // Add some Baggage instances to the table
    insertRecord(table, "020", "SIN");  // Assuming you have a function to add a row
    insertRecord(table, "021", "ICN");

    // Call updateRow to update a row in the table
    updateRow(table, "021", "BKK");

    // Verify that the row was updated correctly
    int hash = calculateHash("021", table->size);
    Baggage *current = table->table[hash];

    while (current != NULL) {
        printf("Checking row with ID %s for verification\n", current->RFIDValue);  // Print the ID of the row being checked
        if (strcmp(current->RFIDValue, "021") == 0) {
            if (strcmp(current->Location, "BKK") == 0) {
                printf("Test passed: Row was updated correctly.\n");
            } else {
                printf("Test failed: Row was not updated correctly.\n");
            }
            break;
        }
        current = current->next;
    }

    // free the memory
    freeBaggageTable(table);  // Assuming you have a function to free the memory
}

int main() {
    testUpdateRow();
    return 0;
}