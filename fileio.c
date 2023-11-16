#include "fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// FOR OPEN FUNCTION
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//OPEN FUNCTION



void openFile() {
    char line[256];
    if(access("BaggageInfoEzDB.txt", F_OK ) != -1 ) {
        FILE *file = fopen("BaggageInfoEzDB.txt", "r");
        printf("Current File Contents Since Last Save: \n");
        if (file == NULL) {
            printf("Could not open file\n");
            return;
        }
        // Display the contents of the file
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
        }
        fclose(file);

        // Reopen the file in append mode
        file = fopen("BaggageInfoEzDB.txt", "a");
        if (file == NULL) {
            printf("Could not open file\n");
            return;
        }
        // You can append to the file here using fprintf or fputc
        fclose(file);

    } else {
        FILE *file = fopen("BaggageInfoEzDB.txt", "w");
        if (file == NULL) {
            printf("Could not create file\n");
            return;
        }
        fclose(file);
        printf("No saved database found, creating new .txt database\n");
        printf("Database created successfully\n");
    }
}
//////////////////////////////////////////////////////////////////////////////////////////

// Function to insert a row in the hash map-based database
// Defines a function called insert row that takes three parameters a pointer to hash map 
// (1) hashmap, (2) newID, (3) newAirportCode
void insertRow(struct HashMap* hashMap, const char* RFIDValue, const char* Location){

// Hash code of the new ID is calculated using the Hash function. 
// The result is used as an index to insert the new data intom the hash map
    int index = hashFunction(RFIDValue);

// The function allocated memory for a new node "struct hashmap node* newnode" 
// and inititalise it with the new ID and airport code. 
// The new node is then inserted into the hash map at the calculated index
    struct HashMapNode* newNode = (struct HashMapNode*) malloc(sizeof(struct HashMapNode));
    if(newNode == NULL) {
        printf("Error: Unable to allocate memory for newNode.\n");
        return;
    }
    newNode->data.RFIDValue = strdup(RFIDValue);
    newNode->data.Location = strdup(Location);
    newNode->next = NULL;

// If there is an exisiting node at the calculated index, the new node inserted at the beginning
// of the existing node linked list. This ensures that the hash map always stores the most recent data
    if(HashMap_get(hashMap, RFIDValue) != NULL) {
        newNode->next = hashMap->table[index];
    }
    hashMap->table[index] = newNode;

    printf("Row with new ID %s and new Airport Code %s are inserted into the database\n", RFIDValue, Location);
}
//////////////////////////////////////////////////////////////////////////////////////////
//DATABASE FUNCTION

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

//////////////////////////////////////////////////////////////////////////////////////////
//QUERY FUNCTIONS

const char *retrieveBaggageTable(BaggageTable *table, const char *RFIDValue) {
    int hash = calculateHash(RFIDValue, table->size);
    Baggage *current = table->table[hash];

    while (current != NULL) { // while the current node is not null

        if (strcmp(current->RFIDValue, RFIDValue) == 0) { // if the RFIDValue is found
            printf("Record found...\n");
            printf("%s : %s\n", RFIDValue ,current->Location);
            return current->Location; // return the location
        }

        current = current->next; // move to the next node
    }
    if (current == NULL){ // if the current node is null
        printf("Record for %s not found...\n", RFIDValue);
    }

    return NULL;

}

//////////////////////////////////////////////////////////////////////////////////////////
// DELETE FUNCTION
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


//////////////////////////////////////////////////////////////////////////////////////////

// SHOWALL FUNCTION
void readBaggageTable() {
    FILE *file = fopen("BaggageInfoEzDB.txt", "r");
    if (file == NULL) {
        printf("Could not open file to read\n");
        return;
    }

    char ch;
    while((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}
//////////////////////////////////////////////////////////////////////////////////////////

// UPDATE FUNCTION
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