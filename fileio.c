#include "fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a function to read DB txt file 

void readBaggageTable() {
    FILE *file = fopen("BaggageInfoEzDB.txt", "r");
    if (file == NULL) {
        printf("Could not open file to read\n");
        return;
    }

    char ch;
    while((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}

