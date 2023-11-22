#include "menu.h"
#include "open.c"
#include "validation.c"
#include "query.c"
#include "Database.c"
#include "Database.h"
#include "fileio.h"
#include "insert.c"
#include "showall.c"
#include "update.c"
#include "delete.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int menu1 (){
    printf("\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("\t\t*                                      DECLARATION                                                *\n");
    printf("\t\t*  SIT's policy on copying does not allow the students to copy source code as well as assessment  *\n");
    printf("\t\t*  solutions from another person or other places. It is the students' responsibility to guarantee *\n");
    printf("\t\t*  that their assessment solutions are their own work. Meanwhile, the students must also ensure   *\n");
    printf("\t\t*  that their work is not accessible by others. Where such plagiarism is detected, both of the    *\n");
    printf("\t\t*  assessments involved will receive ZERO mark.                                                   *\n");
    printf("\t\t*                                                                                                 *\n");
    printf("\t\t*  We hereby declare that:                                                                        *\n");
    printf("\t\t*  -  We fully understand and agree to the abovementioned plagiarism policy.                      *\n");
    printf("\t\t*  -  We did not copy any code from others or from other places.                                  *\n");
    printf("\t\t*  -  We did not share our codes with others or upload to any other places for public access.     *\n");
    printf("\t\t*  -  We agree that our project will receive Zero mark if there is any plagiarism detected.       *\n");
    printf("\t\t*                                                                                                 *\n");
    printf("\t\t*  Declared by: Group Name: (please insert your group name)                                       *\n");
    printf("\t\t*  Team members:                                                                                  *\n");
    printf("\t\t*  1)  Mock Jun Yu                                                                                *\n");
    printf("\t\t*  2)  Ng Shu Yi                                                                                  *\n");
    printf("\t\t*  3)  Julian Teo                                                                                 *\n");
    printf("\t\t*  4)  Soon Jun Hong, Samuel                                                                      *\n");
    printf("\t\t*  5)  Muhammad Yusri Bin Abdullah                                                                *\n");
    printf("\t\t*  6)  Tamo Cholo Rafael Tandoc                                                                   *\n");
    printf("\t\t*  Date: (23/11/2023 XXXXHRS).                                                                    *\n");
    printf("\t\t*                                                                                                 *\n");
    printf("\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("\n");
    printf("\n");

    //user input as a string
    char input[100];
    printf("\t\t - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("\t\t|                                         # HOME PAGE #                                            |\n");
    printf("\t\t - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("\t\t|                                 - What would you like to do?                                     |\n");
    printf("\t\t|                                 - Type 'HELP' for more information.                              |\n");
    printf("\t\t - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    BaggageTable *myDatabase = createBaggageTable(2); // Please change this!

     while (1) {
        printf("\t\t"); // Adjusted indentation for user input
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;  // Remove the newline character from fgets

        // Tokenize the input to check the command
        char *token = strtok(input, " ");

        // Convert token to uppercase
        for(int i = 0; token[i]; i++){
        token[i] = toupper(token[i]);
    }

        // If user input '?', display possible commands
        if (token != NULL && strcmp(token, "HELP") == 0) {
            //if user input '?', display possible commands
            if (strcmp(input, "HELP") == 0) {
                printf("\n");
                printf("\t\tYou have entered: %s\n", input);
                printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
                printf("\t\tPossible commands: \n");
                printf("\t\tOPEN\t - <filename>.txt\n");
                printf("\t\tEXIT\t - Exit Program\n");
                printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        }

        } else if (token != NULL && strcmp(token, "OPEN") == 0) {
            // Check if there is another token (filename) after OPEN
            token = strtok(NULL, " ");
            if (token != NULL) {
                printf("\n");
                printf("\t\tYou have entered: %s %s\n",input, token);
                // Animation to show that the file is being opened
                for (int i = 0; i < 3; i++) {
                    printf("\r\t\tInitializing Database");
                    for (int j = 0; j <= i; j++) {
                        printf(".");
                        fflush(stdout);  // Flushes the output buffer of the stream
                    }
                    sleep(1);
                }
                printf("\n");  // Move to the next line after the animation

                // Attempt to open the specified file
                FILE *file = fopen(token, "r");
                if (file != NULL) {
                    // Create a new BaggageTable and initialize it
                    myDatabase = createBaggageTable(200);  // Please change this!

                    // Open the file using openFile() function from open.c
                    openFile(myDatabase, file);

                    // Clear the console
                    system("cls");

                    printf("\r\t\tDatabase initialized successfully!\n");
                    sleep(1);

                    // Go to menu2
                    menu2(myDatabase);
                    break;
                } else {
                    printf("\t\tError: Unable to open file %s\n", token);
                }
            } else {
                printf("\t\tError: Please provide a filename after OPEN\n");
            }
        } else if (token != NULL && strcmp(token, "EXIT") == 0) {
            printf("\n");
            printf("\t\tExiting program\n");
            return 0;
            break;
        } else {
            printf("\t\tInvalid command. Please try again.\n");
        }
    }

    return 1;
}

int menu2(BaggageTable *myDatabase){
// BaggageTable *myDatabase = createBaggageTable(200); // Please change this!

// //open the file, then store the data into myDatabase
// FILE *file = fopen("BaggageInfoEzDB.txt", "r");
// if (file == NULL) {
//     printf("Failed to open the file.\n");
//     return 0;
// }

// // Initialize the database
// char RFIDValue[256], Location[256];
// while (fscanf(file, "%s %s", RFIDValue, Location) != EOF) {
//     // Calculate the hash of the RFIDValue
//     int index = calculateHash(RFIDValue, myDatabase->size);

//     // Create a new Baggage node
//     Baggage *newBaggage = malloc(sizeof(Baggage));
//     newBaggage->RFIDValue = strdup(RFIDValue);
//     newBaggage->Location = strdup(Location);

//     // Insert the new node at the beginning of the linked list at the hashed index
//     newBaggage->next = myDatabase->table[index];
//     myDatabase->table[index] = newBaggage;
// }

// fclose(file);
    printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("\t\t                         MAINPAGE                         \n");
    printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("\t\t\t  ______     ______     _____     ______               \n");
    printf("\t\t\t /\\  ___\\   /\\___  \\   /\\  __-.  /\\  -- \\       \n");
    printf("\t\t\t \\ \\  __\\   \\/_/  /__  \\ \\ \\/\\ \\ \\ \\  __<   \n");
    printf("\t\t\t  \\ \\_____\\   /\\_____\\  \\ \\____-  \\ \\_____\\ \n");
    printf("\t\t\t   \\/_____/   \\/_____/   \\/____/   \\/_____/        \n");
    printf("\t\t                                                       \n");
    printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    char quePasa[9] = {'H', 'E', 'L', 'P', '\0'};
    char ShowWord[9] = {'S', 'H', 'O', 'W','\0'};
    char InsertWord[9] = {'I', 'N', 'S', 'E', 'R', 'T','\0'};
    char QueryWord[6] = {'Q', 'U', 'E', 'R', 'Y', '\0'};
    char UpdateWord[9] = {'U', 'P', 'D', 'A', 'T', 'E','\0'};
    char DeleteWord[9] = {'D', 'E', 'L', 'E', 'T', 'E','\0'};

    char OpenWord[5] = {'O', 'P', 'E', 'N', '\0'};
    char SaveWord[5] = {'S', 'A', 'V', 'E', '\0'};
    char backWord[5] = {'B', 'A', 'C', 'K', '\0'};

    char* tempRFID;
    char* tempLocation;

    char* command;
    char* lastWord;

    // printf("What would you like to do?\n");
    // printf("Type 'HELP' for more information.\n");

    char input[100];

    do{
        printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
        printf("\t\t                 What would you like to do?               \n");
        printf("\t\t             Type 'HELP' for more information.            \n");
        printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");

        printf("\t\t");
        fgets(input, 100, stdin);
        input[strcspn(input, "\n")] = 0; //remove the newline character from fgets
        char *token = strtok(input, " ");;//Get the first token

        // Convert token to uppercase
        for(int i = 0; token[i]; i++){
        token[i] = toupper(token[i]);
    }

        if (token != NULL) {    // Check if token is NULL before using it
            // Empty Command Input
            if(token == NULL){
                printf("\t\tSyntax Error: Please enter a command!\n");
            }
            // ?
            else if(strcmp(token, quePasa) == 0){
                printf("\t\tHELP\t\t - Show all commands    \n");
                printf("\t\tSHOW ALL\t - SHOW ALL             \n");
                printf("\t\tINSERT\t\t - INSERT RFIDValue Location   \n");
                printf("\t\tQUERY\t\t - QUERY RFIDValue       \n");
                printf("\t\tUPDATE\t\t - UPDATE RFIDValue Location   \n");
                printf("\t\tDELETE\t\t - DELETE RFIDValue      \n");
                printf("\t\tSAVE\t\t - SAVE 'fileName.txt'  \n");
                printf("\t\tBACK\t\t - GO BACK TO HOMEPAGE                \n");
            }

            // INSERT
            else if(strcmp(token, InsertWord) == 0) {
                token = strtok(NULL, " ");
                tempRFID = token;
                token = strtok(NULL, " ");
                tempLocation = token;
                token = strtok(NULL, " ");
                lastWord = token;
                
                int validateResult = validateAirportName(tempLocation);

                if(validateRFID(tempRFID) == 0 && validateResult == 0 && lastWord == NULL){
                    insertRecord(myDatabase, tempRFID, tempLocation);
                }
                else if(validateRFID(tempRFID) != 0)    {
                    printf("\n\t\t-----------------------------\n");
                    printf("\t\tSyntax Error: ");
                    handleError(validateRFID(tempRFID));
                    printf("\t\t-----------------------------\n");
                }
                else if(validateResult != 0)    {
                printf("\n\t\t-----------------------------\n");
                printf("\t\tSyntax Error: ");
                handleError(validateResult);
                printf("\t\t-----------------------------\n");
                            }
                else{
                    printf("\t\t\n-----------------------------\n");
                    printf("\t\tSyntax Error: Additional Input Detected!\n");
                    printf("\t\t-----------------------------\n");
                }
            }

            // SHOW ALL
            else if(strcmp(token, ShowWord) == 0){
                token = strtok(NULL, " ");
                char* secondWord = token;

                // Convert secondWord to uppercase
                for(int i = 0; secondWord != NULL && secondWord[i]; i++){
                secondWord[i] = toupper(secondWord[i]);
                }

                token = strtok(NULL, " ");
                lastWord = token;

                if (secondWord == NULL){
                    printf("\n\t\t-----------------------------\n");
                    printf("\t\tSyntax Error: Did you mean SHOW ALL?\n");
                    printf("\t\t-----------------------------\n");
                }
                else if (strcmp(secondWord, "ALL") == 1){
                    printf("\n\t\t-----------------------------\n");
                    printf("\t\tSyntax Error: Did you mean SHOW ALL?\n");
                    printf("\t\t-----------------------------\n");
                }
                else if(strcmp(secondWord, "ALL") == 0 && lastWord == NULL){
                    showBaggageTable(myDatabase);
                }
                else{
                    printf("\n\t\t-----------------------------\n");
                    printf("\t\tSyntax Error: Additional Input Detected!\n");
                    printf("\t\t-----------------------------\n");
                }
            }

            // QUERY
            else if (strcmp(token, QueryWord) == 0){
                token = strtok(NULL, " ");
                tempRFID = token;
                token = strtok(NULL, " ");
                lastWord = token;

                if(validateRFID(tempRFID) == 0 && lastWord == NULL){
                    queryTag(myDatabase, tempRFID);
                }
                else if (validateRFID(tempRFID) != 0){
                    printf("\n\t\t-----------------------------\n");
                    printf("\t\tSyntax Error: ");
                    handleError(validateRFID(tempRFID));
                    printf("\t\t-----------------------------\n");
                }
                else{
                    printf("\n\t\t-----------------------------\n");
                    printf("\t\tSyntax Error: Additional Input Detected!\n");
                    printf("\t\t-----------------------------\n");
                }
            }

            // UPDATE
            else if(strcmp(token, UpdateWord) == 0) {
                token = strtok(NULL, " ");
                tempRFID = token;
                token = strtok(NULL, " ");
                tempLocation = token;
                token = strtok(NULL, " ");
                lastWord = token;

                if(validateRFID(tempRFID) == 0 && validateAirportName(tempLocation) == 0 && lastWord == NULL){
                    updateRow(myDatabase, tempRFID, tempLocation);
                }
                else if(validateRFID(tempRFID) != 0)    {
                    printf("\n\t\t-----------------------------\n");
                    printf("\t\tSyntax Error: ");
                    handleError(validateRFID(tempRFID));
                    printf("\t\t-----------------------------\n");
                }
                else if(validateAirportName(tempLocation) != 0)    {
                    printf("\n\t\t-----------------------------\n");
                    printf("\t\tSyntax Error: ");
                    handleError(validateAirportName(tempLocation));
                    printf("\t\t-----------------------------\n");
                }
                else{
                    printf("\n\t\t-----------------------------\n");
                    printf("\t\tSyntax Error: Additional Input Detected!\n");
                    printf("\t\t-----------------------------\n");
                }
            }

            // DELETE
            else if(strcmp(token, DeleteWord) == 0){
                token = strtok(NULL, " ");
                tempRFID = token;
                token = strtok(NULL, " ");
                lastWord = token;

                if(validateRFID(tempRFID) == 0 && lastWord == NULL){
                    char confirmation[10];
                    printf("\t\tAre you sure you want to delete the data? (YES/NO): ");
                    fgets(confirmation, 10, stdin);
                    confirmation[strcspn(confirmation, "\n")] = 0; // remove newline character

                    // Convert confirmation to uppercase
                    for(int i = 0; confirmation[i]; i++){
                        confirmation[i] = toupper(confirmation[i]);
                    }

                    if(strcmp(confirmation, "YES") == 0){
                        deleteRow(myDatabase, tempRFID);
                    }
                    else{
                        printf("Operation cancelled.\n");
                    }
                }
                else if (validateRFID(tempRFID) != 0){
                    printf("\n\t\t-----------------------------\n");
                    printf("\t\tSyntax Error: ");
                    handleError(validateRFID(tempRFID));
                    printf("\t\t-----------------------------\n");
                }
                else{
                    printf("\n\t\t-----------------------------\n");
                    printf("\t\tSyntax Error: Additional Input Detected!\n");
                    printf("\t\t-----------------------------\n");
                }
            }

            //Go back to menu1
            else if(strcmp(token, backWord) == 0){
                printf("\t\tGoing back to menu1...\n");
                freeBaggageTable(myDatabase);
                system("cls");
                menu1();
                break;
            }

            // SAVE
            else if(strcmp(token, SaveWord) == 0){
                token = strtok(NULL, " ");
                if(token != NULL){
                    printf("\n\t\t-----------------------------\n");
                    printf("\t\tSyntax Error: Additional input detected after SAVE\n");
                    printf("\t\t-----------------------------\n");
                }
                else{
                    char confirmation[10];
                    printf("\t\tAre you sure you want to save the data? (YES/NO): ");
                    fgets(confirmation, 10, stdin);
                    confirmation[strcspn(confirmation, "\n")] = 0; // remove newline character

                    // Convert confirmation to uppercase
                    for(int i = 0; confirmation[i]; i++){
                        confirmation[i] = toupper(confirmation[i]);
                    }

                    if(strcmp(confirmation, "YES") == 0){
                        saveBaggageTable(myDatabase, "BaggageInfoEzDB.txt");
                        printf("\t\tSave Successful!\n");
                    }
                    else{
                        printf("\t\tOperation cancelled.\n");
                    }
                }
            }

            // Unrecognized Input
            else{
                printf("\t\tSyntax Error: Unrecognized command %s ...\n", input);
            }
        }
    }while(1);

    return 2;
}

// int main() {
//     menu1();
//     return 0;
// }
