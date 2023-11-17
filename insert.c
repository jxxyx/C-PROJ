#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "insert.h"
#include "Database.h"
#include "fileio.h"

void insertRecord(BaggageTable *table, const char *RFIDValue, const char *Location) 
{
    int hash = calculateHash(RFIDValue, table->size);

    // Check if a record with the same RFID value already exists in the table
    Baggage *current = table->table[hash];
    while (current != NULL) {
        if (strcmp(current->RFIDValue, RFIDValue) == 0) {
            printf("The record with RFID %s already exists in the database.\n", RFIDValue);
            return;
        }
        current = current->next;
    }

    // If no existing record is found, insert the new record
    Baggage *newRecord = (Baggage *)malloc(sizeof(Baggage));
    newRecord->RFIDValue = strdup(RFIDValue);
    newRecord->Location = strdup(Location);
    newRecord->next = table->table[hash];
    table->table[hash] = newRecord;

    printf("A new record of ID %s and new Airport Code %s are successfully inserted.\n", RFIDValue, Location);
    writeTableToFile(table, "BaggageInfoEzDB.txt");
    
    if (strcmp(RFIDValue, "RFIDValue") == 0) {
        printf("The record with RFID already exists in the database.\n");
    }
}

