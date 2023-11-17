#include "menu.h"
#include "open.c"
#include "validation.c"
#include "query.c"
#include "Database.c"
#include "Database.h"
#include "fileio.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int menu1 (){
    printf("**********************************************************************************************************************\n");
    printf("*                                              Declaration                                                           *\n");
    printf("*  SIT’s policy on copying does not allow the students to copy source code as well as assessment solutions           *\n");
    printf("*  from another person or other places. It is the students’ responsibility to guarantee that their assessment        *\n");
    printf("*  solutions are their own work. Meanwhile, the students must also ensure that their work is not accessible          *\n");
    printf("*  by others. Where such plagiarism is detected, both of the assessments involved will receive ZERO mark.            *\n");
    printf("*                                                                                                                    *\n");
    printf("*  We hereby declare that:                                                                                           *\n");
    printf("*   •    We fully understand and agree to the abovementioned plagiarism policy.                                      *\n");
    printf("*   •   We did not copy any code from others or from other places.                                                   *\n");
    printf("*   •   We did not share our codes with others or upload to any other places for public access.                      *\n");
    printf("*   •   We agree that our project will receive Zero mark if there is any plagiarism detected.                        *\n");
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
            printf("1. OPEN\n");
            printf("2. EXIT\n");
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
    initializeDatabase(myDatabase);

    printf("  ______     ______     _____     ______               \n");
    printf(" /\\  ___\\   /\\___  \\   /\\  __-.  /\\  == \\       \n");
    printf(" \\ \\  __\\   \\/_/  /__  \\ \\ \\/\\ \\ \\ \\  __<   \n");
    printf("  \\ \\_____\\   /\\_____\\  \\ \\____-  \\ \\_____\\ \n");
    printf("   \\/_____/   \\/_____/   \\/____/   \\/_____/        \n");
    printf("                                                       \n");

    char infoWord[2] = {'?', '\0'};
    char ShowWord[9] = {'S', 'H', 'O', 'W','\0'};
    char InsertWord[9] = {'I', 'N', 'S', 'E', 'R', 'T','\0'};
    char QueryWord[6] = {'Q', 'U', 'E', 'R', 'Y', '\0'};
    char UpdateWord[9] = {'U', 'P', 'D', 'A', 'T', 'E','\0'};
    char DeleteWord[9] = {'D', 'E', 'L', 'E', 'T', 'E','\0'};

    char OpenWord[5] = {'O', 'P', 'E', 'N', '\0'};
    char SaveWord[5] = {'S', 'A', 'V', 'E', '\0'};

    char* tempRFID;
    char* tempLocation;

    printf("What would you like to do?\n");
    printf("Type '?' for more information.\n");

    char input[100];

    do{
        fgets(input, 100, stdin);
        input[strcspn(input, "\n")] = 0; //remove the newline character from fgets
        char *token = strtok(input, " ");;//Get the first token

        if (token != NULL) {    // Check if token is NULL before using it
            //if token is '?' display possible commands
            if (strcmp(token, infoWord) == 0) {
                printf("Possible commands:\n");
                printf("1. SHOW\n");
                printf("2. INSERT\n");
                printf("3. QUERY\n");
                printf("4. UPDATE\n");
                printf("5. DELETE\n");
                printf("6. OPEN\n");
                printf("7. SAVE\n");
                printf("8. EXIT\n");
            }

            //if token is 'SHOW', display the database
            else if (strcmp(token, ShowWord) == 0) {
                printf("Showing database...\n");
            }

            //if token is 'INSERT', insert a new baggage into the database
            else if (strcmp(token, InsertWord) == 0) {
                printf("Inserting new baggage...\n");
            }

            //if token is 'QUERY', query the database
            else if (strcmp(token, QueryWord) == 0) {
                printf("Querying database...\n");
            }

            //if token is 'UPDATE', update the database
            else if (strcmp(token, UpdateWord) == 0) {
                printf("Updating database...\n");
            }

            //if token is 'DELETE', delete a baggage from the database
            else if (strcmp(token, DeleteWord) == 0) {
                printf("Deleting baggage...\n");
            }

            //if token is 'OPEN', open the file
            else if (strcmp(token, OpenWord) == 0) {
                printf("Opening file...\n");
            }

            //if token is 'SAVE', save the file
            else if (strcmp(token, SaveWord) == 0) {
                printf("Saving file...\n");
            }

            //if token is 'EXIT', exit the program
            else if (strcmp(token, "EXIT") == 0) {
                printf("Exiting program\n");
                return 0;
                break;
            }
        }
    }while(1);

    return 2;
}

int main() {
    menu1();
    return 0;
}