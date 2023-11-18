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
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int menu1 (){
    printf("**********************************************************************************************************************\n");
    printf("*                                              Declaration                                                           *\n");
    printf("*  SIT's policy on copying does not allow the students to copy source code as well as assessment solutions           *\n");
    printf("*  from another person or other places. It is the students' responsibility to guarantee that their assessment        *\n");
    printf("*  solutions are their own work. Meanwhile, the students must also ensure that their work is not accessible          *\n");
    printf("*  by others. Where such plagiarism is detected, both of the assessments involved will receive ZERO mark.            *\n");
    printf("*                                                                                                                    *\n");
    printf("*  We hereby declare that:                                                                                           *\n");
    printf("*   -   We fully understand and agree to the abovementioned plagiarism policy.                                       *\n");
    printf("*   -   We did not copy any code from others or from other places.                                                   *\n");
    printf("*   -   We did not share our codes with others or upload to any other places for public access.                      *\n");
    printf("*   -   We agree that our project will receive Zero mark if there is any plagiarism detected.                        *\n");
    printf("*                                                                                                                    *\n");
    printf("*  Declared by: Group Name: (please insert your group name)                                                          *\n");
    printf("*  Team members:                                                                                                     *\n");
    printf("*   1)  Mock Jun Yu                                                                                                  *\n");
    printf("*   2)  Ng Shu Yi                                                                                                    *\n");
    printf("*   3)  Julian Teo                                                                                                   *\n");
    printf("*   4)  Soon Jun Hong, Samuel                                                                                        *\n");
    printf("*   5)  Muhammad Yusri Bin Abdullah                                                                                  *\n");
    printf("*   6)  Tamo Cholo Rafael Tandoc                                                                                     *\n");
    printf("*  Date: (please insert the date when you submit your group project).                                                *\n");
    printf("*                                                                                                                    *\n");
    printf("**********************************************************************************************************************\n");

    //user input as a string
    char input[100];
    printf("What would you like to do?\n");
    printf("Type '?' for more information.\n");

    //while loop to keep the program running
    while (1) {
        scanf("%s", input);

        //if user input '?', display possible commands
        if (input[0] == '?') {
            printf("Possible commands:\n");
            printf("OPEN\n");
            printf("EXIT\n");
        }

        //if user input 'OPEN', open the file, clear the terminal, then go to menu2
        else if (input[0] == 'O' && input[1] == 'P' && input[2] == 'E' && input[3] == 'N') {

            // Animation to show that the file is being opened
            for(int i = 0; i < 3; i++) {
            printf("\rInitializing Database");
            for(int j = 0; j <= i; j++) {
                printf(".");
                fflush(stdout); // Flushes the output buffer of the stream
            }
            sleep(1);
            }
            printf("\n"); // Move to the next line after the animation

            //clear the console
            system("cls");

            //open the file using openFile() function from open.c
            // openFile();

            //go to menu2
            menu2();
            break;
        }

        //if user input 'EXIT', exit the program
        else if (input[0] == 'E' && input[1] == 'X' && input[2] == 'I' && input[3] == 'T') {
            printf("Exiting program\n");
            return 0;
            break;
        }

        //if none of the above, display error message
        else {
            printf("Invalid command. Please try again.\n");
        }
    }

    return 1;
}

int menu2(){
BaggageTable *myDatabase = createBaggageTable(200); // Please change this!

//open the file, then store the data into myDatabase
FILE *file = fopen("BaggageInfoEzDB.txt", "r");
if (file == NULL) {
    printf("Failed to open the file.\n");
    return 0;
}

// Initialize the database
char RFIDValue[256], Location[256];
while (fscanf(file, "%s %s", RFIDValue, Location) != EOF) {
    // Calculate the hash of the RFIDValue
    int index = calculateHash(RFIDValue, myDatabase->size);

    // Create a new Baggage node
    Baggage *newBaggage = malloc(sizeof(Baggage));
    newBaggage->RFIDValue = strdup(RFIDValue);
    newBaggage->Location = strdup(Location);

    // Insert the new node at the beginning of the linked list at the hashed index
    newBaggage->next = myDatabase->table[index];
    myDatabase->table[index] = newBaggage;
}

fclose(file);

    printf("  ______     ______     _____     ______               \n");
    printf(" /\\  ___\\   /\\___  \\   /\\  __-.  /\\  == \\       \n");
    printf(" \\ \\  __\\   \\/_/  /__  \\ \\ \\/\\ \\ \\ \\  __<   \n");
    printf("  \\ \\_____\\   /\\_____\\  \\ \\____-  \\ \\_____\\ \n");
    printf("   \\/_____/   \\/_____/   \\/____/   \\/_____/        \n");
    printf("                                                       \n");

    char quePasa[2] = {'?', '\0'};
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

    printf("What would you like to do?\n");
    printf("Type '?' for more information.\n");

    char input[100];

    do{
        fgets(input, 100, stdin);
        input[strcspn(input, "\n")] = 0; //remove the newline character from fgets
        char *token = strtok(input, " ");;//Get the first token

        if (token != NULL) {    // Check if token is NULL before using it
            // Empty Command Input
            if(token == NULL){
                printf("Syntax Error: Please enter a command!\n");
            }
            // ?
            else if(strcmp(token, quePasa) == 0){
                printf("?        - Show all commands    \n");
                printf("SHOW ALL - SHOW ALL             \n");
                printf("INSERT   - INSERT A12345C ANT   \n");
                printf("QUERY    - QUERY A12345C        \n");
                printf("UPDATE   - UPDATE A12345C BNT   \n");
                printf("DELETE   - DELETE A12345C       \n");
                printf("SAVE     - SAVE 'fileName.txt'  \n");
                printf("BACK     - BACK                 \n");
            }

            // INSERT
            else if(strcmp(token, InsertWord) == 0) {
                token = strtok(NULL, " ");
                tempRFID = token;
                token = strtok(NULL, " ");
                tempLocation = token;
                token = strtok(NULL, " ");
                lastWord = token;

                if(validateRFID(tempRFID) == 0 && validateAirportName(tempLocation) == 0 && lastWord == NULL){
                    insertRecord(myDatabase, tempRFID, tempLocation);
                }
                else if(validateRFID(tempRFID) != 0)    {
                    printf("\n-----------------------------\n");
                    printf("Syntax Error: ");
                    handleError(validateRFID(tempRFID));
                    printf("-----------------------------\n");
                }
                else if(validateAirportName(tempLocation) != 0)    {
                    printf("\n-----------------------------\n");
                    printf("Syntax Error: ");
                    handleError(validateAirportName(tempLocation));
                    printf("-----------------------------\n");
                }
                else{
                    printf("\n-----------------------------\n");
                    printf("Syntax Error: Additional Input Detected!\n");
                    printf("-----------------------------\n");
                }
            }

            // SHOW ALL
            else if(strcmp(token, ShowWord) == 0){
                token = strtok(NULL, " ");
                char* secondWord = token;
                token = strtok(NULL, " ");
                lastWord = token;

                if (secondWord == NULL){
                    printf("\n-----------------------------\n");
                    printf("Syntax Error: Did you mean SHOW ALL?\n");
                    printf("-----------------------------\n");
                }
                else if (strcmp(secondWord, "ALL") == 1){
                    printf("\n-----------------------------\n");
                    printf("Syntax Error: Did you mean SHOW ALL?\n");
                    printf("-----------------------------\n");
                }
                else if(strcmp(secondWord, "ALL") == 0 && lastWord == NULL){
                    showAll(myDatabase);
                }
                else{
                    printf("\n-----------------------------\n");
                    printf("Syntax Error: Additional Input Detected!\n");
                    printf("-----------------------------\n");
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
                    printf("\n-----------------------------\n");
                    printf("Syntax Error: ");
                    handleError(validateRFID(tempRFID));
                    printf("-----------------------------\n");
                }
                else{
                    printf("\n-----------------------------\n");
                    printf("Syntax Error: Additional Input Detected!\n");
                    printf("-----------------------------\n");
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
                    printf("\n-----------------------------\n");
                    printf("Syntax Error: ");
                    handleError(validateRFID(tempRFID));
                    printf("-----------------------------\n");
                }
                else if(validateAirportName(tempLocation) != 0)    {
                    printf("\n-----------------------------\n");
                    printf("Syntax Error: ");
                    handleError(validateAirportName(tempLocation));
                    printf("-----------------------------\n");
                }
                else{
                    printf("\n-----------------------------\n");
                    printf("Syntax Error: Additional Input Detected!\n");
                    printf("-----------------------------\n");
                }
            }

            // DELETE
            else if(strcmp(token, DeleteWord) == 0){
                token = strtok(NULL, " ");
                tempRFID = token;
                token = strtok(NULL, " ");
                lastWord = token;

                if(validateRFID(tempRFID) == 0 && lastWord == NULL){
                    deleteRow(myDatabase, tempRFID);
                }
                else if (validateRFID(tempRFID) != 0){
                    printf("\n-----------------------------\n");
                    printf("Syntax Error: ");
                    handleError(validateRFID(tempRFID));
                    printf("-----------------------------\n");
                }
                else{
                    printf("\n-----------------------------\n");
                    printf("Syntax Error: Additional Input Detected!\n");
                    printf("-----------------------------\n");
                }
            }

            //Go back to menu1
            else if(strcmp(token, backWord) == 0){
                printf("Going back to menu1...\n");
                freeBaggageTable(myDatabase);
                system("cls");
                menu1();
                break;
            }

            // Unrecognized Input
            else{
                printf("Syntax Error: Unrecognized command %s ...\n", input);
            }
        }
    }while(1);

    return 2;
}

int main() {
    menu1();
    return 0;
}
