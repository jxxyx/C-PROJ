#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "insert.h"
#include "Database.h"

void insertRecord(BaggageTable *table, const char *RFIDValue, const char *Location) 
{
    int hash = calculateHash(RFIDValue, table->size);

    Baggage *newRecord = (Baggage *)malloc(sizeof(Baggage));
    newRecord->RFIDValue = strdup(RFIDValue);
    newRecord->Location = strdup(Location);
    newRecord->next = table->table[hash];
    table->table[hash] = newRecord;

    printf("A new record of ID %s and new Airport Code %s are successfully inserted.\n", RFIDValue, Location);

    if (strcmp(RFIDValue, "RFIDValue") == 0) {
        printf("The record with RFID already exists in the database.\n");
    }
}

