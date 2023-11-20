#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "Database.h"
#include "fileio.h"
#include "insert.h"
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif


// void openFile(BaggageTable *myDatabase) {
//     char line[256];
//     if (access("BaggageInfoEzDB.txt", F_OK) != -1) {
//         FILE *file = fopen("BaggageInfoEzDB.txt", "r");
//         printf("Current File Contents Since Last Save: \n");
//         if (file == NULL) {
//             printf("Could not open file\n");
//             return;
//         }
//         // Read the contents of the file and insert into the BaggageTable
//         while (fgets(line, sizeof(line), file) != NULL) {
//             // Assuming each line has RFIDValue and Location separated by a space
//             char *token = strtok(line, " ");
//             if (token != NULL) {
//                 char *RFIDValue = token;
//                 token = strtok(NULL, " ");
//                 if (token != NULL) {
//                     char *Location = token;
//                     // Insert into the BaggageTable
//                     insertRecord(myDatabase, RFIDValue, Location);
//                 }
//             }
//         }
//         fclose(file);
//     } else {
//         FILE *file = fopen("BaggageInfoEzDB.txt", "w");
//         if (file == NULL) {
//             printf("Could not create file\n");
//             return;
//         }
//         fclose(file);
//         printf("No saved database found, creating a new .txt database\n");
//         printf("Database created successfully\n");
//     }
// }

void openFile(BaggageTable *myDatabase) {
    char line[256];
    if(access("BaggageInfoEzDB.txt", F_OK ) != -1 ) {
        FILE *file = fopen("BaggageInfoEzDB.txt", "r");
            if (file == NULL) {
            printf("Failed to open the file.\n");
        }

            // Initialize the database
        char RFIDValue[256], Location[256];
        while (fscanf(file, "%s %s", RFIDValue, Location) != EOF) {
            // Calculate the hash of the RFIDValue
            int index = calculateHash(RFIDValue, myDatabase->size);

            // Create a new Baggage node
            Baggage *newBaggage = malloc(sizeof(Baggage));
            newBaggage->RFIDValue = strdup(RFIDValue);
            newBaggage->Location = strdup(Location);

            // Insert the new node at the beginning of the linked list at the hashed index
            newBaggage->next = myDatabase->table[index];
            myDatabase->table[index] = newBaggage;
    }

    fclose(file);

    //might need to look at the code below because file is already opened in if above
    } else {
        FILE *file = fopen("BaggageInfoEzDB.txt", "w");
        if (file == NULL) {
            printf("Could not create file\n");
        }
        fclose(file);
        printf("No saved database found, creating new .txt database\n");
        printf("Database created successfully\n");
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
