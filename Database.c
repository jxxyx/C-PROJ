#include "Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // This function will either open or create a txt file to store the database
    BaggageTable *table = open_database("BaggageInfoEzDB.txt");

    // This is to insert the user defined value using insert.h



    // Get the user to input open or save file
    char input[256];
    char command[32];
    char filename[256];

    while(1) {
        printf("1. Open Database\n");
        printf("2. Save Database\n");
        printf("Enter 1 or 2:\n");
        fgets(input, sizeof(input), stdin);

        if (sscanf(input, "%s %s", command, filename) == 2) {
            if (strcmp(command, "OPEN") == 0) {
                // Open an existing database file
                table = open_database(filename);
                printf("Database '%s' opened.\n", filename);
            } else if (strcmp(command, "SAVE") == 0) {
                // Save the latest records to the database file
                save_database(table, filename);
                printf("Database '%s' saved.\n", filename);
            }
        } else {
            printf("Unknown Option. Please enter a valid option.\n");
        }
    }
    // This is the save function to save the database to the file
    save_database(table, "BaggageInfoEzDB.txt");

    return 0;
}