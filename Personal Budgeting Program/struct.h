//Personal Budgeting Program
//Structure file
//Group 04
//Sayyid Dzaky A - 2306171846
//Hizkia Karl Anugrah N - 2306254810
//19-05-2024
//v 1.0

#include "header.h"

struct Transaction { // data struct for keeping each transaction data
    char type[8]; // "Income" or "Expense"
    int amount; // Storing the amount of money
    char date[11]; // Format DD-MM-YYYY
    char category[20]; 
};

struct Transaction transactions[MAX_TRANSACTIONS]; //calling the struct and assigning it  
int transactionCount = 0;