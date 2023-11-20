#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "Database.h"
#include "open.h"
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

//copied fileio.c's openFile here
void openFile(BaggageTable *myDatabase, FILE *file) {
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

// int main() {
//     openFile();
//     return 0;
// }