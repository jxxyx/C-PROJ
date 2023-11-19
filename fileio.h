
#include "Database.h"
//header guard
#ifndef FILEIO_H
#define FILEIO_H

//OPENFUNCTION
void saveBaggageTable(BaggageTable *table, const char *filename);

//OPENFUNCTION
void openFile(BaggageTable *myDatabase);

#endif