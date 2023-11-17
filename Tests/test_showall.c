#include "../Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../fileio.h"
#include "../showall.h"
#include "../insert.h"

void testShowBaggageTable() {
    // Create a new BaggageTable
    BaggageTable *table = createBaggageTable(10);

    // Read the contents of the file and populate the BaggageTable
    readTableFromFile(table, "BaggageInfoEzDB.txt");

    // Display the table
    showBaggageTable(table);

    // Free memory
    freeBaggageTable(table);
}

int main() {
    // Call the test function
    testShowBaggageTable();

    return 0;
}
