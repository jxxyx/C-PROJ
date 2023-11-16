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

void testInsertRecord(){
    BaggageTable *table = createBaggageTable(10);

    insertRecord(table, "020","SIN");
    insertRecord(table, "021","ICN");

    int hash = calculateHash("021", table->size);
    Baggage *current = table->table[hash];

    while (current != NULL) {
        if (strcmp(current->RFIDValue, "021") == 0) {
            printf("The record with RFID 021 is found in the database.\n");
            break;
        }
        else{
            printf("The record with RFID 021 is not found in the database.\n");
            break;
        }
        current = current->next;
    }
}

int main()
{
    testInsertRecord();
    return 0;
}