#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Database.h"
#include "../delete.h"
#include "../insert.h"
#include "../query.h"

void benchmarkDatabase() {
    int num_rows = 1;  // Adjust this value based on your needs
    char RFID[20];
    char location[20];

    // Create a new database
    BaggageTable* myDatabase = createBaggageTable(10);

    // Prepare the data
    sprintf(RFID, "%d", 1);
    strcpy(location, "JFK");

    // Measure the time taken to add a single row
    clock_t start = clock();
    insertRecord(myDatabase, RFID, location);
    clock_t end = clock();
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time taken to add a single row: %f seconds\n", time_taken);

    // Reset the timer and measure the time taken to query a single row
    start = clock();
    queryTag(myDatabase, RFID);
    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time taken to query a single row: %f seconds\n", time_taken);

    // Reset the timer and measure the time taken to delete a single row
    start = clock();
    deleteRow(myDatabase, RFID);
    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time taken to delete a single row: %f seconds\n", time_taken);
    printf("\n\n\n\n");
    free(myDatabase);
}

int main() {
    // Run the benchmark
    benchmarkDatabase();

    return 0;
}