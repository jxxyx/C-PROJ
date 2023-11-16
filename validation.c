#include "error_codes.h"
#include "validation.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int containsSpecialCharacter(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!(isalnum(str[i]) || str[i] == ' ')) {
            return 4; // Special character found
        }
    }
    return 0; // No special characters found
}

int containsLetter(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            return 5; // Character found
        }
    }
    return 0; // No Character found
}

void convertToUppercase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (islower(str[i])) {
            str[i] = toupper(str[i]); // Convert to uppercase
        }
    }
}

void removeWhitespace(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (!isspace(str[i])) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0'; // Null-terminate the new string
}

int validateRFID(char* RFIDValue) {
    // Null check
    if (RFIDValue == NULL) {
        return 3;
    }

    // Remove possible whitespace
    removeWhitespace(RFIDValue);

    // Check for special characters
    if (containsSpecialCharacter(RFIDValue)) {
        return 4;
    }
    // Check for letters
    if (containsLetter(RFIDValue)) {
        return 5;
    }

    // Check if string is empty
    if (RFIDValue[0] == '\0') {
        return 6;
    }

    return VALID_INPUT;
}

int validateAirportName(char* Location) {
    // Null check
    if (Location == NULL) {
        return 3;
    }

    // Remove possible whitespace
    removeWhitespace(Location);

    // Convert to uppercase
    convertToUppercase(Location);

    // Check airport name length
    if (strlen(Location) != 3) {
        return 8;
    }

    // Check for non-alphabetic characters
    for (int i = 0; i < 3; i++) {
        if (!isalpha(Location[i])) {
            return 9;
        }
    }

    // Check if string is empty
    if (Location[0] == '\0') {
        return 6;
    }

    return VALID_INPUT;
}

void handleError(int errorCode) {
    switch (errorCode) {
        case VALID_INPUT:
            printf("Input is valid.\n");
            break;
        case NULL_INPUT:
            printf("Input is null.\n");
            break;
        case CONTAINS_SPECIAL_CHAR:
            printf("Input contains special characters.\n");
            break;
        case CONTAINS_LETTER:
            printf("Input contains letters.\n");
            break;
        case EMPTY_STRING:
            printf("Input is an empty string.\n");
            break;
        case WHITESPACE_ONLY:
            printf("Input contains only whitespace.\n");
            break;
        case INVALID_AIRPORT_NAME_LENGTH:
            printf("Airport name is of invalid length.\n");
            break;
        case NON_ALPHABETIC_AIRPORT_NAME:
            printf("Airport name contains non-alphabetic characters.\n");
            break;
        case DUPLICATE_KEY:
            printf("Duplicate key found.\n");
            break;
        default:
            printf("An unknown error occurred.\n");
            break;
    }
}
