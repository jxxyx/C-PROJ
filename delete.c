#include "delete.h"
#include <stdio.h>
#include <string.h>

// Function to delete a row from the hash map-based database
void deleteRow(struct HashMap* hashMap, const char* idToDelete) {
    int index = calculateIndex(idToDelete); // Calculate the index based on the ID
    struct HashMapNode* current = hashMap->table[index];
    struct HashMapNode* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->data.id, idToDelete) == 0) {
            // Remove the row if the ID matches
            if (previous == NULL) {
                // If the first node matches, update the bucket pointer
                hashMap->table[index] = current->next;
            } else {
                previous->next = current->next;
            }

            // Free memory associated with the node and the airport code
            free(current->data.id);
            free(current->data.airport);
            free(current);

            printf("Row with ID %s deleted from the database\n", idToDelete);
            return; // Exit the function after deletion
        }
        previous = current;
        current = current->next;
    }

    printf("Row with ID %s not found in the database\n", idToDelete);
}
