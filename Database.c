#include "Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// For all of the codes here, I will need more time to understand it, as well as finetune it to match the descriptions of the functions in the project brief

// Specifying the size for the initial data array, setting a limit to the initial load of the DB
#define MAX_DATABASE_SIZE 0

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

void initializeDatabase(BaggageTable *table) {
}

int main() {
    BaggageTable *myDatabase = createBaggageTable(MAX_DATABASE_SIZE);
    initializeDatabase(myDatabase);

    // Save the database to a file
     saveBaggageTable(myDatabase, "BaggageInfoEzDB.txt");

    // Free the memory when you're done
    freeBaggageTable(myDatabase);

     return 0;
}