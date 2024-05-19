#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"
//#include "fileHandling.h"


int main() {
    programHeader();
    loadTransactionsFromFile();
    menu();
    return 0;
}

void programHeader() { // Program welcoming word
    printf("-----------------------------\n");
    printf("| Personal Budgeting System |\n");
    printf("-----------------------------\n");
}

void addTransaction(const char *type) { //function for adding transactions
    if (transactionCount >= MAX_TRANSACTIONS) { // Setting max value for transaction addition
        printf("Transaction limit reached.\n");
        return;
    }

    int validInput = 0;
    char tempAmount[100]; // Temporary string to hold the amount input

    // Validate amount input
    while (!validInput) {
        printf("Enter the amount: ");
        scanf("%s", tempAmount);
        if (sscanf(tempAmount, "%d", &transactions[transactionCount].amount) == 1) {
            validInput = 1; // Correct integer format
        } else {
            printf("Invalid amount. Please enter a valid number.\n");
        }
    }

    validInput = 0;
    char tempDate[100]; // Temporary string to hold the date input

    // Validate date input
    while (!validInput) {
        printf("Enter date (DD-MM-YYYY): ");
        scanf("%s", tempDate);
        if (strlen(tempDate) == 10 && tempDate[2] == '-' && tempDate[5] == '-' &&
            isdigit(tempDate[0]) && isdigit(tempDate[1]) && isdigit(tempDate[3]) && isdigit(tempDate[4]) &&
            isdigit(tempDate[6]) && isdigit(tempDate[7]) && isdigit(tempDate[8]) && isdigit(tempDate[9])) {
            validInput = 1; // Correct date format
        } else {
            printf("Invalid date format. Please enter date in DD-MM-YYYY format.\n");
        }
    }

    printf("Enter category: ");
    scanf("%s", transactions[transactionCount].category);
    strcpy(transactions[transactionCount].type, type);
    strcpy(transactions[transactionCount].date, tempDate); // Add this line to store the date

    transactionCount++; // keeping track of the number transaction inputted
    printf("Transaction added successfully!\n");
}

void viewBudgetSummary() { // Function to calculate and display the budget summary 
    int totalIncome = 0, totalExpense = 0, i;

    printf ("Your budget summary are as follows: \n");

    for (i = 0; i < transactionCount; i++) { //loop through the transaction data structure to get the total incomes and expenses
        if (strcmp(transactions[i].type, "Income") == 0) {
            totalIncome += transactions[i].amount;
        } else if (strcmp(transactions[i].type, "Expense") == 0) {
            totalExpense += transactions[i].amount;
        }
    }

    printf("Total Income: Rp. %d\n", totalIncome);
    printf("Total Expenses: Rp. %d\n", totalExpense);
    printf("Net Balance: Rp. %d\n", totalIncome - totalExpense);
}

void searchTransactions() { //Function to search a transaction based on its category
    char searchCategory[20];
    printf("Enter category to search: ");
    scanf("%s", searchCategory);

    int found = 0, i;
    for (i = 0; i < transactionCount; i++) {
        if (strcmp(transactions[i].category, searchCategory) == 0) {// searching the transaction based on the category in the transaction data structure
            printf("%d. %s - %d - %s - %s\n", i + 1, transactions[i].type, transactions[i].amount, transactions[i].date, transactions[i].category);
            found = 1;
        }
    }

    if (!found) {
        printf("No transactions found under category '%s'.\n", searchCategory);
    }
}

void searchTransactionsByDate() {
    char datePart[5];
    printf("Entter montr (MM) or year (YYYY) to search: ");
    scanf("%s", datePart);

    int found = 0, i;
    for (i = 0; i < transactionCount; i++) {
        if (strstr(transactions[i].date, datePart)) {
            printf("%d. %s - Rp. %d - %s - %s\n", i + 1, transactions[i].type, transactions[i].amount, transactions[i].date, transactions[i].category);
            found = 1;
        }
    }

    if (!found) {
        printf("No transactions found on %s.\n", datePart);
    }
}

void editTransaction() {
    int transactionIndex;
    viewAllTransactions();
    printf("Enter the transaction number to edit: ");
    scanf("%d", &transactionIndex);
    transactionIndex--;

    if (transactionIndex < 0 || transactionIndex >= transactionCount) {
        printf("Invalid transaction number.\n");
        return;
    }

    printf("Enter new details fo this transaction: \n");
    printf("Enter amount: ");
    scanf("%d", &transactions[transactionIndex].amount);
    printf("Enter date (DD-MM-YYYY): ");
    scanf("%s", transactions[transactionIndex].date);
    printf("Enter category: ");
    scanf("%s", transactions[transactionIndex].category);

    printf("Transaction edited successfully!\n");
}

void deleteAllTransactions() {
    transactionCount = 0; // Reset the count effectively removes all transactions
    printf("All transactions have been deleted.\n"); 
}

void continueText() {
    printf("Would you like to continue? (Y/N) ");
    char choice;
    scanf(" %c", &choice); // Perhatikan spasi sebelum %c
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

void saveTransactionsToFile() { // Function to save transactions to a file
    FILE *file = fopen("transactions.txt", "w");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    for (int i = 0; i < transactionCount; i++) {
        fprintf(file, "%s %d %s %s\n", transactions[i].type, transactions[i].amount, transactions[i].date, transactions[i].category);
    }

    fclose(file);
    printf("Transactions saved.\n");
}

void loadTransactionsFromFile() {
    FILE *file = fopen("transactions.txt", "r");
    if (file == NULL) {
        printf("| No previous transactions. |\n");
        return;
    }

    while (fscanf(file, "%s %d %s %[^\n]", transactions[transactionCount].type, &transactions[transactionCount].amount, transactions[transactionCount].date, transactions[transactionCount].category) == 4) {
        transactionCount++;
        if (transactionCount >= MAX_TRANSACTIONS) break;
    }

    fclose(file);
    printf("| Prev transactions loaded  |\n");
}

void viewAllTransactions() { // Function for viewing all transaction
    if (transactionCount == 0) {
        printf("No transactions recorded.\n");
        return;
    } else {
        printf("This is all of your transactions:\n");
    }

    for (int i = 0; i < transactionCount; i++) { // Looping the transaction data structure to get all the transaction out
        printf("%d. %s - Rp. %d - %s - %s\n", i + 1, transactions[i].type, transactions[i].amount, transactions[i].date, transactions[i].category);
    }
}

void menu() { //Function for the main menu
    int choice;
    do {
        printf("|         == Menu ==        |\n");
        printf("-----------------------------\n");
        printf("|1. Add Income Transaction  |\n");
        printf("|2. Add Expense Transaction |\n");
        printf("|3. View All Transactions   |\n");
        printf("|4. View Budget Summary     |\n");
        printf("|5. Search Transactions     |\n");
        printf("|6. Edit transaction        |\n");
        printf("|7. Delete All Transactions |\n");
        printf("|0. Exit                    |\n");
        printf("-----------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                do {
                    addTransaction("Income");
                    secondMenu("Income");
                } while (1); // Terus tampilkan menu kedua setelah menambahkan transaksi
                break;
            case 2:
                do {
                    addTransaction("Expense");
                    secondMenu("Expense");
                } while (1); // Terus tampilkan menu kedua setelah menambahkan transaksi
                break;
            case 3:
                viewAllTransactions();
                continueText();
                break;
            case 4:
                viewBudgetSummary();
                continueText();
                break;
            case 5:
                searchChoice();
                continueText();
                break;
            case 6:
                editTransaction();
                break;
            case 7:
                deleteAllTransactions();
                break;
            case 0:
                exitProgram();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0 );
}

void secondMenu(const char *transactionType) {
    int choice;
    do {
        programHeader();
        printf("|1. Continue the transaction|\n");
        printf("|2. Go to Main Menu         |\n");
        printf("|0. Exit The Program        |\n");
        printf("-----------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addTransaction(transactionType);
            break;
        case 2:
            menu(); // Kembali ke menu utama
        case 0:
            printf("Exiting program...\n");
            exitProgram(); // Keluar dari program
        default:
            printf("Invalid choice, please try again.\n");
            break;
        }
    } while (choice != 2 && choice != 0);
}

void searchChoice() {
    int choice;

    printf("Search by: \n");
    printf("|1. Category                    |\n");
    printf("|2. Date                        |\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        searchTransactions();
        break;
    case 2:
        searchTransactionsByDate();
        break;
    default:
        printf("Invalid choice, please try again.\n");
        break;
    }
}