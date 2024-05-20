//Personal Budgeting Program
//Main file
//Group 04
//Sayyid Dzaky A - 2306171846
//Hizkia Karl Anugrah N - 2306254810
//19-05-2024
//v 2.1

#include "header.h"
#include "menu.c"
#include "struct.h"

int main() { // main function to call all the necessary function to run the program
    programHeader(); // calling program header
    loadTransactionsFromFile(); // loading existed transaction from previous program run
    menu(); // calling menu function
    return 0;
}

void programHeader() { // Program welcoming word
    printf("-----------------------------\n");
    printf("| Personal Budgeting System |\n");
    printf("-----------------------------\n");
}

void loadTransactionsFromFile() { // Function for reading and loading the saved transaction
    FILE *file = fopen("transactions.txt", "r"); // Opening external file with fopen and read "r"
    if (file == NULL) { 
        printf("| No previous transactions. |\n");
        return;
    }

    while (fscanf(file, "%s %d %s %[^\n]", transactions[transactionCount].type, &transactions[transactionCount].amount, transactions[transactionCount].date, transactions[transactionCount].category) == 4) {
        transactionCount++; // Counting transaction count
        if (transactionCount >= MAX_TRANSACTIONS) break;
    }

    fclose(file); //closing file
    printf("| Prev transactions loaded  |\n");
}

void continueText() { // function for asking continue text 
    printf("Would you like to continue? (Y/N) ");
    char choice;
    scanf(" %c", &choice); 
    if (choice == 'Y' || choice == 'y') {
        menu();
    } 
    else if (choice == 'N' || choice == 'n') {
        exitProgram();
    } else {
        printf("Invalid choice, please try again.\n");
        continueText();
    }   
}

void exitProgram() {
    saveTransactionsToFile();
    printf("Exiting program...\n");
    exit(0);
}