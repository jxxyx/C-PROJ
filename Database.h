// This is a guard to prevent header file form being use too many times in the same compilation unit
#ifndef DATABASE_H
#define DATABASE_H


// Defining structure to store key and value(s)
typedef struct Baggage {
    char *RFIDValue; // This sets the RFID value as key
    char *Location; // This sets Location as the value
    struct Baggage *next; // Pointer to the next entry in the hash table
} Baggage;


// This is the hashmap function
typedef struct {
    int size; // Represents the max size of the DB
    Baggage **table; //  This is a pointer to an array of Baggage pointers
} BaggageTable;


// Create a function to create and start a hashmap
BaggageTable *createBaggageTable(int size);

// Create a function to save the Database
void saveBaggageTable(BaggageTable *table, const char *filename);

// Create a function to free the memeory allocation of the Database to limit its use else where
void freeBaggageTable(BaggageTable *table);

// Create a function to retrieve a value from the hashmap based on a key, which is the RFIDValue
const char *retrieveBaggageTable(BaggageTable *table, const char *RFIDValue);

// Function to insert a key-value pair into the hashmap
void insertRecord(BaggageTable *table, const char *RFIDValue, const char *Location);

// This statement is to close the guard, to ensure that the content within the guard is only runned once
#endif