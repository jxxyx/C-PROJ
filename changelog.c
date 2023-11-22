#include <string.h>
#include <stdio.h>
#include <time.h>
#include "changelog.h"

#define MAX_CHANGES 100
#define MAX_DESCRIPTION_LENGTH 256

char changeBuffer[MAX_CHANGES][MAX_DESCRIPTION_LENGTH];
int changeCount = 0;

char* getCurrentTime() {
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    static char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

    return buffer;
}

void logChange(const char* changeDescription) {
    if(changeCount < MAX_CHANGES) {
        strncpy(changeBuffer[changeCount], changeDescription, MAX_DESCRIPTION_LENGTH);
        changeCount++;
    }
}

void saveChanges(const char* dataFileName) {
    char logFileName[256];
    snprintf(logFileName, sizeof(logFileName), "%s_change_log.txt", dataFileName);

    FILE *logfile = fopen(logFileName, "a");
    if(logfile != NULL){
        for(int i = 0; i < changeCount; i++) {
            fprintf(logfile, "Change made at %s: %s\n", getCurrentTime(), changeBuffer[i]);
        }
        fclose(logfile);
    }

    changeCount = 0;
}