#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include "Database.h"
#include "open.h"


// // Create a function to read DB txt file 

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
    
    } else {
        FILE *file = fopen("BaggageInfoEzDB.txt", "w");
        if (file == NULL) {
            printf("Could not create file\n");
            return;
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

