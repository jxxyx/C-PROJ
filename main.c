// main header file, which consists of many functions
#include <stdio.h>
// This is console io, where it can be used for input output function
#include <conio.h>
#include <string.h>
#include <stdlib.h>

// Creating a structure called baggage using typedef
// For testing purposes, I will be only having 1 key value and 1 value only. Once fully tested we will implment more values under key
typedef struct {
    // creating variable called RFID_Value that has int property
    // This is the Key
    char RFID_Value[100];
    // char property for the location value
    char location[100];
} Baggage;

// Limiting the amount of entry for testing phase
Baggage baggage_info[200];
int baggage_info_size = 0;


// Creating a function to insert record
// using void to ensure that the code does not return a value
void insertRecord(Baggage baggage) {
    // "a" means append, "w" means write
    // This line means that this will append the record into the BaggageInfoEzDB.txt
    FILE *file = fopen("BaggageInfoEzDB.txt", "a");
    // If file is present or empty it will print the following value into the DB
    if (file != NULL) {
        // In file, print key and value
        fprintf(file, "%s,%s\n", baggage.RFID_Value, baggage.location);
        fclose(file);
    }

}

// Perhaps i wanna do query here?
// Baggage* find_RFID_Value(int* RFID_Value) {
    // For all of the int i, if it is less than the size of the DB, append count by 1
    // for (int i = 0; i < baggage_info_size; i++){
        // if (strcmp(baggage_info[i].RFID_Value, RFID_Value) == 0) {
            // return &baggage_info[i];
        // }
    // }

    //return NULL;
//}

// This is the temporary show all function
void print_baggage_info() {
    for (int i = 0; i < baggage_info_size; i++) {
        printf("RFIDValue: %s, Location: %s", 
            baggage_info[i].RFID_Value, baggage_info[i].location);
    }
}

// Putting int main(void) to ensure that program is compatible with all c compilers
int main(void) {
    Baggage baggage1 = {"1", "Singapore"};
    Baggage baggage2 = {"2", "Malaysia"};
    Baggage baggage3 = {"3", "Russia"};

    insertRecord(baggage1);
    insertRecord(baggage2);
    insertRecord(baggage3);

    // Finding the baggage by RFID value
    
    // Printing the baggage info
    

    // Printing the the entire DB
    print_baggage_info();

    return 0;
}