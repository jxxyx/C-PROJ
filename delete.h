#ifndef DELETE_H
#define DELETE_H

#include "Database.h" // Include the appropriate header for your HashMap data structure
#include <string.h>

// Function prototype to delete a row from the hash map-based database
void deleteRow(BaggageTable *table, const char* RFIDValue, const char* Location);

#endif // DELETE_H