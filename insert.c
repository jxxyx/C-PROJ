#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "insert.h"

// Function to insert a row in the hash map-based database
// Defines a function called insert row that takes three parameters a pointer to hash map 
// (1) hashmap, (2) newID, (3) newAirportCode
void insertRow(struct HashMap* hashMap, const char* RFIDValue, const char* Location){

// Hash code of the new ID is calculated using the Hash function. 
// The result is used as an index to insert the new data intom the hash map
    int index = hashFunction(RFIDValue);

// The function allocated memory for a new node "struct hashmap node* newnode" 
// and inititalise it with the new ID and airport code. 
// The new node is then inserted into the hash map at the calculated index
    struct HashMapNode* newNode = (struct HashMapNode*) malloc(sizeof(struct HashMapNode));
    if(newNode == NULL) {
        printf("Error: Unable to allocate memory for newNode.\n");
        return;
    }
    newNode->data.RFIDValue = strdup(RFIDValue);
    newNode->data.Location = strdup(Location);
    newNode->next = NULL;

// If there is an exisiting node at the calculated index, the new node inserted at the beginning
// of the existing node linked list. This ensures that the hash map always stores the most recent data
    if(HashMap_get(hashMap, RFIDValue) != NULL) {
        newNode->next = hashMap->table[index];
    }
    hashMap->table[index] = newNode;

    printf("Row with new ID %s and new Airport Code %s are inserted into the database\n", RFIDValue, Location);
}