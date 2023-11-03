#include "error_codes.h"
#include "validation.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Placeholder for a function to check if an RFID is already in the database
int isRFIDAlreadyInDatabase(const char* rfid) {
    // Simulated check for duplicate RFID (you should implement this according to your database)
    if (strcmp(rfid, "AB1234CD") == 0) {
        return 1; // RFID exists in the database
    }
    return 0; // RFID is not in the database
}

// Placeholder for a function to check if an airport name is already in the database
int isAirportNameAlreadyInDatabase(const char* airportName) {
    // Simulated check for duplicate airport name (you should implement this according to your database)
    if (strcmp(airportName, "JFK") == 0) {
        return 1; // Airport name exists in the database
    }
    return 0; // Airport name is not in the database
}

int containsSpecialCharacter(const char* str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (!(isalnum(str[i]) || str[i] == ' ')) {
            return 1; // Special character found
        }
    }
    return 0; // No special characters found
}

int containsDigits(const char* str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (isdigit(str[i])) {
            return 1; // Digit found
        }
    }
    return 0; // No digits found
}

int containslowercase(const char* str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (islower(str[i])) {
            return 1; // lowercase found
        }
    }
    return 0; // No lowercase found
}

int validateRFID(const char* rfid) {
    // Check RFID length and format
    if (strlen(rfid) != 8) {
        return INVALID_INPUT;
    }

    // Check for special characters
    if (containsSpecialCharacter(rfid)) {
        return INVALID_INPUT;
    }

    // Check if RFID is unique (simulated)
    if (isRFIDAlreadyInDatabase(rfid)) {
        return DUPLICATE_KEY;
    }

    return VALID_INPUT;
}

int validateAirportName(const char* airportName) {
    // Check airport name length
    if (strlen(airportName) < 3 || strlen(airportName) > 3) {
        return INVALID_INPUT;
    }

    // Check for special characters
    if (containsSpecialCharacter(airportName)) {
        return INVALID_INPUT;
    }

    // Check for digits
    if (containsDigits(airportName)) {
        return INVALID_INPUT;
    }

    // Check for lowercase
    if (containslowercase(airportName)) {
        return INVALID_INPUT;
    }

    // Check if airport name is unique (simulated)
    if (isAirportNameAlreadyInDatabase(airportName)) {
        return DUPLICATE_KEY;
    }

    return VALID_INPUT;
}

void handleError(int errorCode) {
    switch (errorCode) {
        case INVALID_INPUT:
            printf("Invalid input.\n");
            break;
        case DUPLICATE_KEY:
            printf("Duplicate key found.\n");
            break;
        default:
            printf("An error occurred.\n");
            break;
    }
}
