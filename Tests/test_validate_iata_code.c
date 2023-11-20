#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libs/cJSON/cJSON.h"
#include "../validation.h"  // Adjust this path to the header file that declares validate_iata_code

void test_validate_iata_code() {
    // Test with a valid IATA code
    int result = validate_iata_code("SFO");
    assert(result == 0);  // The function should return 0 for a valid IATA code

    // Test with an invalid IATA code
    result = validate_iata_code("XYZ");
    assert(result == 10);  // The function should return 1 for an invalid IATA code

    printf("validate_iata_code test passed!\n");
}

int main() {
    test_validate_iata_code();
    return 0;
}