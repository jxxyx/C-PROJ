#ifndef DATABASE_H
#define DATABASE_H

// This is to include in the 

// Defining structure to store key and value(s)
typedef struct Baggage {
    char *newID; // This sets the RFID value as key
    char *newAirportCode; // This sets Location as the value
    struct Baggage *next; // Pointer to the next entry in the hash table
} Baggage;


// This is the hashmap function
typedef struct {
    int size; // Represents the max size of the DB
    Baggage **table; // This is a pointer to an array of Baggage pointers
} BaggageTable;


// Create a function to create and start a hashmap
BaggageTable *createBaggageTable(int size);

// Create a function to save the Database
void saveBaggageTable(BaggageTable *table, const char *filename);

// Create a function to free the memeory allocation of the Database to limit its use else where
void freeBaggageTable(BaggageTable *table);

// Create a function to retrieve a value from the hashmap based on a key, which is the RFIDValue
const char *retrieveBaggageTable(BaggageTable *table, const char *newID);

// Function to insert a key-value pair into the hashmap
void insertRecord(BaggageTable *table, const char *newID, const char *newAirportCode);

// This statement is to close the guard, to ensure that the content within the guard is only runned once
#endif