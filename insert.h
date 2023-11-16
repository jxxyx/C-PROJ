#ifndef INSERT_H
#define INSERT_H

#include "Database.h"
#include <string.h>

void insertRecord(BaggageTable *table, const char *RFIDValue, const char *Location);

#endif // INSERT_H