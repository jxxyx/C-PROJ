#include "Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// For all of the codes here, I will need more time to understand it, as well as finetune it to match the descriptions of the functions in the project brief

// Specifying the size for the initial data array, setting a limit to the initial load of the DB
#define MAX_DATABASE_SIZE 10

// Create a function to create and start a hashmap
BaggageTable *createBaggageTable(int size) {
    // Creates a new baggage table 
    BaggageTable *table = (BaggageTable *)malloc(sizeof(BaggageTable));
    // Size of the table will specify the number of slots it will have
    table->size = size;
    table->table = (Baggage **)malloc(sizeof(Baggage *) * size);

    for (int i = 0; i < size; i++) {
        table->table[i] = NULL;
    }

    return table;
}

// Calculate the hash for a given RFIDValue
int calculateHash(const char *RFIDValue, int size) {
    // Initiate hash value = 0
    int hash = 0;
    int length = strlen(RFIDValue);

    // This calculates the hashvalue of the given RFID value
    // Determines what slot in Baggage Table that the RFIDValue will be in
    for (int i = 0; i < length; i++) {
        hash += RFIDValue[i];
    }

    return hash % size;
}

// Create a function to save the Database into a txt file 
void saveBaggageTable(BaggageTable *table, const char *filename) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Could not open file to save\n");
        return;
    }

    for (int i = 0; i < table->size; i++) {
        Baggage *current = table->table[i];

        while (current != NULL) {
            fprintf(file, "%s %s\n", current->RFIDValue, current->Location);
            current = current-> next;
        }
    }

    fclose(file);
}

// Create a function to free the memory allocation of the Database to limit its use elsewhere
void freeBaggageTable(BaggageTable *table) {
    // Frees memory allocated to the baggage table
    for (int i = 0; i < table->size; i++) {
        Baggage *current = table->table[i];
        Baggage *next;

        while (current != NULL) {
            next = current-> next;
            free(current->RFIDValue);
            free(current->Location);
            free(current);
            current = next;
        }
    }

    free(table->table);
    free(table);
}

// Create a function to retrieve a value from the hashmap based on a key, which is the RFIDValue
const char *retrieveBaggageTable(BaggageTable *table, const char *RFIDValue) {
    // If RFIDValue not found, then return null value.
    int hash = calculateHash(RFIDValue, table->size);
    Baggage *current = table->table[hash];

    while (current != NULL) {
        if (strcmp(current->RFIDValue, RFIDValue) == 0) {
            return current->Location;
        }

        current = current->next;
    }

    return NULL;
}

// Function to insert a key-value pair into the hashmap
void insertRecord(BaggageTable *table, const char *RFIDValue, const char *Location) {
    int hash = calculateHash(RFIDValue, table->size);

    Baggage *newRecord = (Baggage *)malloc(sizeof(Baggage));
    newRecord->RFIDValue = strdup(RFIDValue);
    newRecord->Location = strdup(Location);
    newRecord->next = table->table[hash];
    table->table[hash] = newRecord;
}

// Function to initialize the database with 10 initial records
void initializeDatabase(BaggageTable *table) {
    insertRecord(table, "001", "SGP");
    insertRecord(table, "002", "CHN");
    insertRecord(table, "003", "IND");
    insertRecord(table, "004", "RUS");
    insertRecord(table, "005", "USA");
    insertRecord(table, "006", "BRN");
    insertRecord(table, "007", "AUS");
    insertRecord(table, "008", "ENG");
    insertRecord(table, "009", "KRN");
    insertRecord(table, "010", "JPN");
}

// int main() {
//     BaggageTable *myDatabase = createBaggageTable(MAX_DATABASE_SIZE);
//     initializeDatabase(myDatabase);

//     // Now, you can perform operations on the database
//     const char *location = retrieveBaggageTable(myDatabase, "001");
//     if (location != NULL) {
//         printf("Location for RFID 001: %s\n", location);
//     } else {
//         printf("RFID 001 not found in the database.\n");
//     }

//     // Save the database to a file
//     saveBaggageTable(myDatabase, "BaggageInfoEzDB.txt");

//     // Free the memory when you're done
//     freeBaggageTable(myDatabase);

//     return 0;
// }