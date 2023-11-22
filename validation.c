#include "error_codes.h"
#include "validation.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "libs/cJSON/cJSON.h"
#include <stdlib.h>

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

int validate_iata_code(const char *user_input) {
    // Load the JSON file
    FILE *file = fopen("IATAairports.json", "rb");
    if (!file) {
        fprintf(stderr, "\t\tCould not open file\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(length + 1);
    fread(data, 1, length, file);
    fclose(file);

    // Parse the JSON data
    cJSON *json = cJSON_Parse(data);
    if (!json) {
        fprintf(stderr, "\t\tCould not parse JSON\n");
        free(data);
        return 1;
    }

    // Check if the user's input matches any of the IATA codes
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, json) {
        cJSON *iata = cJSON_GetObjectItemCaseSensitive(item, "iata");
        if (cJSON_IsString(iata) && strcmp(user_input, iata->valuestring) == 0) {
            // The user's input is a valid IATA code
            cJSON_Delete(json);
            free(data);
            return 0;
        }
    }

    // The user's input is not a valid IATA code
    fprintf(stderr, "\t\tInvalid IATA code: %s\n", user_input);
    cJSON_Delete(json);
    free(data);
    return 10;
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

    // Check if string contains verified IATA airport code
    if (validate_iata_code(Location) != 0) {
        return 10;
    }

    return VALID_INPUT;
}

void handleError(int errorCode) {
    switch (errorCode) {
        case VALID_INPUT:
            printf("\t\tInput is valid.\n");
            break;
        case NULL_INPUT:
            printf("\t\tInput is null.\n");
            break;
        case CONTAINS_SPECIAL_CHAR:
            printf("\t\tInput contains special characters.\n");
            break;
        case CONTAINS_LETTER:
            printf("\t\tInput contains letters.\n");
            break;
        case EMPTY_STRING:
            printf("\t\tInput is an empty string.\n");
            break;
        case WHITESPACE_ONLY:
            printf("\t\tInput contains only whitespace.\n");
            break;
        case INVALID_AIRPORT_NAME_LENGTH:
            printf("\t\tAirport name is of invalid length.\n");
            break;
        case NON_ALPHABETIC_AIRPORT_NAME:
            printf("\t\tAirport name contains non-alphabetic characters.\n");
            break;
        case DUPLICATE_KEY:
            printf("\t\tDuplicate key found.\n");
            break;
        case INVALID_AIRLINE_CODE:
            printf("\t\tInvalid airline code.\n");
            break;
        default:
            printf("\t\tAn unknown error occurred.\n");
            break;
    }
}
