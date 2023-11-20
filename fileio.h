#include <stdio.h>
#include "Database.h"
//header guard
#ifndef FILEIO_H
#define FILEIO_H

//OPENFUNCTION
void saveBaggageTable(BaggageTable *table, const char *filename);

//OPENFUNCTION
void openFile(BaggageTable *myDatabase, FILE *file);

//WRITETABLETOFILE
void writeTableToFile(BaggageTable *table, const char* filename);

//READTABLEFROMFILE
void readTableFromFile(BaggageTable *table, const char* filename);

//CLOSEGUARD
#endif