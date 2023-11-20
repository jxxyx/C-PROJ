#ifndef VALIDATION_H
#define VALIDATION_H

int validateRFID(char* rfid);
int validateAirportName(char* airportName);
void handleError(int errorCode);
int validate_iata_code(const char *user_input); // to test this function, see Tests/test_validate_iata_code.c

#endif
