

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file; // Declare file pointer for old file
    FILE *file1; // Declare file pointer for new file

    // Open the old file in read mode
    file = fopen("test.txt", "a");
    if (file == NULL) {
        printf("Could not open the file.\n");
        return 1;
    }

    // To read the contents in the file
    char line[100]; // Assuming each line has at most 100 characters
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line); // Print the line to the console
    }

    // Open the new file (temp.txt) in write mode
    file1 = fopen("temp.txt", "w");
    if (file1 == NULL) {
        fclose(file);
        printf("Could not open the new file.\n");
        return 1;
    }

    // User inputs what they want to write into the file
    printf("\n");
    printf("Please input your name: \n");
    char name[100]; // Declare the variable to store the name
    // Use scanf to read input from the user (including spaces)
    if (scanf("%99[^\n]", name) != 1) {
        printf("Invalid input. Please enter a valid name.\n");
        fclose(file);
        fclose(file1);
        return 1; // Exit the program with an error code.
    }
    
    // Append the user's name to the new file
    fprintf(file1, "%s\n", name);

    // Done reading and writing in both files, so close both files
    fclose(file);
    fclose(file1);
    
    // Rename the new file (temp.txt) to the main file (test.txt)
    if (rename("temp.txt", "test.txt") != 0) {
        printf("Failed to rename the file.\n");
        return 1;
    }
    // Remove the temporary file
    remove("temp.txt");
    
    // Open the new main file (test.txt) and check its contents
    file = fopen("test.txt", "r");
    if (file == NULL) {
        printf("Could not open the amended main file.\n");
        return 1;
    }
    
    // Display the contents of the new main file
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    
    // Close the new main file
    fclose(file);

    return 0;
}