 #ifndef UPDATE_H
#define UPDATE_H

#include "Database.h" // Include the appropriate header for your HashMap data structure
#include <string.h>

// Function prototype to update a row in the hash map-based database
void updateRow(BaggageTable *table, const char* RFIDValue, const char* Location);


#endif // UPDATE_H
