#include <stdio.h>
#include <stdlib.h>

// Define structures to represent tables

// AccountType
typedef struct {
    short TypeID;
    char TypeName[30];
    char Description[80];
} AccountType;

// Account
typedef struct {
    short AccountID;
    char Name[30];
    char Password[20];
    char EmailAddr[30];
    short AccType;
    char Role[20];
} Account;

// Food
typedef struct {
    short FoodID;
    short StallID;
    char FoodName[30];
    float Price;
    char Description[150];
    char FoodImage[100]; // Assuming an image is a string
} Food;

// CatList
typedef struct {
    short CatID;
    short FoodID;
} CatList;

// OrderTransaction
typedef struct {
    short TransID;
    short StallID;
    short FoodID;
    short StudentID;
} OrderTransaction;

// Stall
typedef struct {
    short StallID;
    short LocationID;
    char StallName[30];
    char OwnerName[30];
} Stall;

// Location
typedef struct {
    short LocationID;
    char LocationName[30];
    char BlkName[30];
} Location;

// Category
typedef struct {
    short CatID;
    char CatName[30];
} Category;

int main() {
    // TO REVIEW LINE 70 - 79
    AccountType accountTypes[] = {
        {1, "User", "Students and lecturer are able to register as a user."},
        {2, "Stall Owner", "Stall owners can view their stall orders and reviews."}
    };

    Account accounts[] = {
        {1, "Joanna Lim", "password", "joanna@gmail.com", 1, "User"},
        {2, "tester", "password", "tester@gmail.com", 1, "User"},
        {3, "stallownertester", "password", "stallowner@gmail.com", 2, "Store Owner"}
    };
// REVIEW END
    Food foods[] = {
        {1, 1, "Yong Tau Foo", 5.00, "Choose a minimum of 5 pieces of ingredients and a noodle type.", ""},
        {2, 1, "Economic Beehoon", 2.00, "Beehoon with 2 ingredients.", ""},
        {3, 3, "Chicken Cutlet Curry Rice", 5.50, "Curry rice topped with chicken cutlet.", ""},
        {4, 3, "Pork Cutlet Curry Rice", 5.50, "Curry rice topped with pork cutlet.", ""},
        {5, 6, "Fries", 2.00, "Ala carte packet of fries", ""},
        {6, 6, "Spaghetti", 4.00, "Pasta with tomato sauce.", ""},
        {7, 6, "Chicken Burger", 3.50, "Chicken burger with vegetables inside.", ""},
        {8, 7, "Ban Mian", 3.00, "Ban Mian with meat, vegetable and egg.", ""},
        {9, 7, "You Mian", 3.00, "You Mian with meat, vegetable and egg.", ""},
        {10, 8, "Petite Yogurt", 3.00, "Plain yogurt with 1 topping.", ""},
        {11, 9, "Roasted Chicken rice", 2.80, "", ""},
        {12, 10, "Kimchi Noodles", 3.50, "Shin instant noodles", ""},
        {13, 10, "Hotplate set", 3.50, "Choose between chicken or beef. Set comes with rice.", ""},
        {14, 11, "Mala Hotpot", 8.00, "Price differs by weight. Choose between the level of spiciness and dry or soup.", ""}
    };

    CatList catList[] = {
        {1, 2},
        {2, 1},
        {2, 3},
        {3, 3},
        {3, 5},
        {2, 6},
        {3, 6},
        {2, 7}
    };

    //OrderTransaction orderTransactions[] = {
        // Define your OrderTransaction data here
    //};

    //Stall stalls[] = {
        // Define your Stall data here
    //};

    //Location locations[] = {
        // Define your Location data here
    //};

    //Category categories[] = {
        // Define your Category data here
    //};

    // Perform database operations using the data

    return 0;
}
