#include "Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char file
char line[1000]

// Open the new main file (BaggageInfoEzDB.txt) and check its contents
file = fopen("BaggageInfoEzDB.txt", "r");

if (file == NULL) {
    printf("Could not read the file main file.\n");
    return 1;
    
    
    // Display the contents of the new main file
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    
    // Close the new main file
    fclose(file);
}

