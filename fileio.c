#include <stdio.h>
#include <stddef.h>
#include "Database.h"
#include "fileio.h"
#include "insert.h"
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif


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
    }
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

void writeTableToFile(BaggageTable *table, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    for (int i = 0; i < table->size; i++) {
        Baggage *current = table->table[i];
        while (current != NULL) {
            if (current->RFIDValue == NULL) {
                printf("RFIDValue is null\n");
                return;
            }
            if (current->Location == NULL) {
                printf("Location is null\n");
                return;
            }
            fprintf(file, "%s\t%s\n", current->RFIDValue, current->Location);
            current = current->next;
        }
    }
    fclose(file);
}

// Create a function to read the Database from a txt file
void readTableFromFile(BaggageTable *table, const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        char RFIDValue[100];
        char Location[100];
        sscanf(line, "%s %s", RFIDValue, Location);
        insertRecord(table, RFIDValue, Location);
    }

    fclose(file);
}
