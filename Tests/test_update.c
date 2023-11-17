#include <stdio.h>
#include <string.h>
#include "../Database.h"
#include "../update.h"
#include "../insert.h"
#include "../fileio.h"
#include "../delete.h"

// Test function for updateRow
void test_updateRow() {
    // Create a BaggageTable object and initialize it
    BaggageTable *table = createBaggageTable(10);

    // Read the file into the BaggageTable
    readTableFromFile(table, "BaggageInfoEzDB.txt");

    // Add some sample data to the BaggageTable object
    printf("Test case 1: insert a row\n");
    insertRecord(table, "001", "ABC");
    insertRecord(table, "002", "ABC");
    insertRecord(table, "003", "ABC");
    insertRecord(table, "004", "ABC");

    // Test case 2: Update an existing row
    printf("Test case 2: Update an existing row\n");
    updateRow(table, "004", "HHH");

    // Test case 3: Delete a row
    printf("Test case 3: Delete a row\n");
    deleteRow(table, "004");


    // Write the updated BaggageTable back to the file
    writeTableToFile(table, "BaggageInfoEzDB.txt");

    // Clean up the BaggageTable object
    freeBaggageTable(table);
}

int main() {
    // Call the test function
    test_updateRow();

    return 0;
}
