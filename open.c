#include <stdio.h>
#include <stddef.h>
#include "Database.h"
#include "open.h"
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

        // Reopen the file in append mode
        file = fopen("BaggageInfoEzDB.txt", "a");
        if (file == NULL) {
            printf("Could not open file\n");
            return;
        }
        // You can append to the file here using fprintf or fputc
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