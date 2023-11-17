#include <stdio.h>
#include <assert.h>
#include "../Database.h"
#include "../fileio.h"
#include "../query.h"
#include "../insert.h"

void test_retrieveBaggageTable() {
    // Create a BaggageTable object
    BaggageTable *table = createBaggageTable(10);

    // Read the file and populate the BaggageTable
    readTableFromFile(table, "BaggageInfoEzDB.txt");

    // Provide an RFID value to search for
    const char *RFIDValue = "001";

    // Call the retrieveBaggageTable function
    const char *location = retrieveBaggageTable(table, RFIDValue);

    // Check if the location is correct
    const char *expectedLocation = "ABC";
    assert(strcmp(location, expectedLocation) == 0);

    printf("retrieveBaggageTable test passed!\n");
}

int main() {
    test_retrieveBaggageTable();
    return 0;
}
