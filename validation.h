#ifndef VALIDATION_H
#define VALIDATION_H

int validateRFID(const char* rfid);
int validateAirportName(const char* airportName);
void handleError(int errorCode);

#endif