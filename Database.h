// This are the headers that are required for the database.h
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

// This is a guard to prevent header file form being use too many times in the same compilation unit
#ifndef DATABASE_H
#define DATABASE_H


// Defining structure to store key and value(s)
typedef struct {
    char *RFIDValue; // This sets the RFID value as key
    char *Location; // This sets Location as the value
} Baggage;

typedef struct {
    int size; // Represents the max size of the DB
    int count; // Show count of current entries present in the database
    Baggage *records; // This is a pointer to Baggage
} BaggageTable;

// Declares the function to open the database stored in the txt file.
// Takes the file name as parameter and returns pointer to Baggage Table
BaggageTable *open_database(const char *filename);
// using a void function to save database in to the datatable in a file
void save_record(BaggageTable *table, const char *filename);
// using a void function to insert records into the DB
void insert_record(BaggageTable *table, const char *RFIDVale, const char *Location);
// function to get all record in the database
const char *retrieve_record(BaggageTable *table, const char *RFIDValue); // This code makes use of the key value to retrieve records in the database

// This statement is to close the guard, to ensure that the content within the guard is only runned once
#endif