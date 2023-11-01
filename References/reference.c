#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for each row of data
typedef struct {
    int id;
    char name[100];
    int age;
} Row;

// Function prototypes
void showall(Row *data, int rows);
void insert(Row *data, int *rows);
void query(Row *data, int rows);
void update(Row *data, int rows);
void delete(Row *data, int *rows);

// Main function
int main() {
    Row data[1000];
    int rows = 0;
    int choice;

    while (1) {
        printf("1. Show all\n");
        printf("2. Insert\n");
        printf("3. Query\n");
        printf("4. Update\n");
        printf("5. Delete\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showall(data, rows);
                break;
            case 2:
                insert(data, &rows);
                break;
            case 3:
                query(data, rows);
                break;
            case 4:
                update(data, rows);
                break;
            case 5:
                delete(data, &rows);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

// Function definitions
void showall(Row *data, int rows) {
    FILE *file = fopen("database.txt", "r");
    if (file == NULL) {
        printf("Error: unable to open file\n");
        return;
    }

    int id;
    char name[100];
    int age;
    while (fscanf(file, "%d %s %d", &id, name, &age) != EOF) {
        printf("%d %s %d\n", id, name, age);
    }

    fclose(file);
}

void insert(Row *data, int *rows) {
    FILE *file = fopen("database.txt", "a");
    if (file == NULL) {
        printf("Error: unable to open file\n");
        return;
    }

    int id;
    char name[100];
    int age;
    printf("Enter ID: ");
    scanf("%d", &id);
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter age: ");
    scanf("%d", &age);

    fprintf(file, "%d %s %d\n", id, name, age);
    fclose(file);
    (*rows)++;
}

void query(Row *data, int rows) {
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    FILE *file = fopen("database.txt", "r");
    if (file == NULL) {
        printf("Error: unable to open file\n");
        return;
    }

    int i = 0;
    while (fscanf(file, "%d %s %d", &data[i].id, data[i].name, &data[i].age) != EOF) {
        if (data[i].id == id) {
            printf("Found record with ID %d\n", id);
            printf("%d %s %d\n", data[i].id, data[i].name, data[i].age);
            break;
        }
        i++;
    }

    fclose(file);
}

void update(Row *data, int rows) {
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    FILE *file = fopen("database.txt", "r");
    if (file == NULL) {
        printf("Error: unable to open file\n");
        return;
    }

    int i = 0;
    while (fscanf(file, "%d %s %d", &data[i].id, data[i].name, &data[i].age) != EOF) {
        if (data[i].id == id) {
            printf("Updating record with ID %d\n", id);
            printf("Enter new name: ");
            scanf("%s", data[i].name);
            printf("Enter new age: ");
            scanf("%d", &data[i].age);

            file = freopen("database.txt", "w", file);
            if (file == NULL) {
                printf("Error: unable to open file\n");
                return;
            }

            for (int j = 0; j < rows; j++) {
                fprintf(file, "%d %s %d\n", data[j].id, data[j].name, data[j].age);
            }
            break;
        }
        i++;
    }

    fclose(file);
}

void delete(Row *data, int *rows) {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    FILE *file = fopen("database.txt", "r");
    if (file == NULL) {
        printf("Error: unable to open file\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error: unable to open file\n");
        fclose(file);
        return;
    }

    int i = 0;
    while (fscanf(file, "%d %s %d", &data[i].id, data[i].name, &data[i].age) != EOF) {
        if (data[i].id != id) {
            fprintf(temp, "%d %s %d\n", data[i].id, data[i].name, data[i].age);
        } else {
            printf("Deleting record with ID %d\n", id);
        }
        i++;
    }

    fclose(file);
    fclose(temp);

    file = fopen("database.txt", "w");
    if (file == NULL) {
        printf("Error: unable to open file\n");
        return;
    }

    temp = fopen("temp.txt", "r");
    if (temp == NULL) {
        printf("Error: unable to open file\n");
        fclose(file);
        return;
    }

    while (fscanf(temp, "%d %s %d", &data[i].id, data[i].name, &data[i].age) != EOF) {
        fprintf(file, "%d %s %d\n", data[i].id, data[i].name, data[i].age);
        i++;
    }

    fclose(file);
    fclose(temp);

    (*rows)--;
}

int main() {
    int rows = 0;
    load(&rows);

    int choice;
    do {
        printf("1. Insert\n");
        printf("2. Query\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        Row data[100];
        switch (choice) {
            case 1:
                insert(data, &rows);
                break;
            case 2:
                query(data, rows);
                break;
            case 3:
                update(data, rows);
                break;
            case 4:
                delete(data, &rows);
                break;
            case 5:
                display(data, rows);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
//end{code}

//Note:

//Please replace `"database.txt"` and `"temp.txt"` with your actual file paths.

//The above code allows you to perform the following operations:
//\begin{itemize}
//\item Insert
//\item Query
//\item Update
//\item Delete
//\item Display
//\end{itemize}

//You can test this program by running it and choosing an operation. Please make sure to provide valid inputs while performing any operation.

//For example, when inserting, make sure to provide a unique ID, a name, and an age.

//Please let me know if you have any further questions or need help with something else.

