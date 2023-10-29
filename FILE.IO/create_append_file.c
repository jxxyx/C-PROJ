#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file; // Declare a file pointer

    int choice;
    char input[100]; // Variable to store user input

    printf("Choose an option:\n");
    printf("1. Create a new file and write data\n");
    printf("2. Append data to an existing file\n");
    printf("Enter your choice (1 or 2): ");
    
    fgets(input, sizeof(input), stdin); // Get user's choice as text
    choice = atoi(input); // Convert the text input to an integer

    if (choice == 1) {
        // User wants to create a new file and write data
        file = fopen("database.txt", "w");
        if (file == NULL) {
            printf("Could not create the file.\n");
            return 1;
        }
    } else if (choice == 2) {
        // User wants to append data to an existing file
        file = fopen("database.txt", "a");
        if (file == NULL) {
            printf("Could not open the file for appending.\n");
            return 1;
        }
    } else {
        printf("Invalid choice. Please enter 1 or 2.\n");
        return 1;
    }

    // User inputs what they want to write into the file
    printf("Please input data (press Enter to start a new line, Ctrl+D or Ctrl+Z to finish):\n");
    char data[1000]; // Declare the variable to store the data

    while (fgets(data, sizeof(data), stdin) != NULL) {
        // Append or write the user's data to the file
        fprintf(file, "%s", data);
    }

    // Close the file
    fclose(file);

    return 0;
}
