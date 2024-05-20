//Personal Budgeting Program
//Feature function file
//Group 04
//Sayyid Dzaky A - 2306171846
//Hizkia Karl Anugrah N - 2306254810
//19-05-2024
//v 1.1

#include "header.h"
#include "struct.h"

void addTransaction(const char *type) { // Function for adding transactions
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
        if (sscanf(tempAmount, "%d", &transactions[transactionCount].amount) == 1) { // Type eror handling for money input
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
            isdigit(tempDate[6]) && isdigit(tempDate[7]) && isdigit(tempDate[8]) && isdigit(tempDate[9])) { // Type eror handling for date format
            validInput = 1; // Correct date format
        } else {
            printf("Invalid date format. Please enter date in DD-MM-YYYY format.\n");
        }
    }

    printf("Enter category: ");
    scanf("%s", transactions[transactionCount].category);
    strcpy(transactions[transactionCount].type, type); // Storing the transaction type
    strcpy(transactions[transactionCount].date, tempDate); // Storing the date

    transactionCount++; // keeping track of the number transaction inputted
    printf("Transaction added successfully!\n");
}

void viewAllTransactions() { // Function for viewing all transaction
    if (transactionCount == 0) {
        printf("No transactions recorded.\n");
        return;
    } else {
        printf("This is all of your transactions:\n");
    }

    for (int i = 0; i < transactionCount; i++) { // Looping the transaction data structure to get all the transaction out
        printf("%d. %s - Rp. %d - %s - %s\n", i + 1, transactions[i].type, transactions[i].amount, transactions[i].date, transactions[i].category); // Printing all the transactions detail
    }
}

void viewBudgetSummary() { // Function to calculate and display the budget summary 
    int totalIncome = 0, totalExpense = 0, i;

    printf ("Your budget summary are as follows: \n");

    for (i = 0; i < transactionCount; i++) { //loop through the transaction data structure to get the total incomes and expenses
        if (strcmp(transactions[i].type, "Income") == 0) { // strcmp for comparing the transaction type
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
    char searchCategory[20]; // limit the searchCategory to 19 character
    printf("Enter category to search: ");
    scanf("%s", searchCategory);

    int found = 0, i;
    for (i = 0; i < transactionCount; i++) { // Looping through the transaction count
        if (strcmp(transactions[i].category, searchCategory) == 0) {// searching the transaction based on the category in the transaction data structure
            printf("%d. %s - %d - %s - %s\n", i + 1, transactions[i].type, transactions[i].amount, transactions[i].date, transactions[i].category);
            found = 1;
        }
    }

    if (!found) { 
        printf("No transactions found under category '%s'.\n", searchCategory);
    }
}

void searchTransactionsByDate() { // Function for searching transactions based on the date (MM) or (YYYY)
    char datePart[5]; // Limiting the date part to 4 char
    printf("Entter montr (MM) or year (YYYY) to search: ");
    scanf("%s", datePart);

    int found = 0, i;
    for (i = 0; i < transactionCount; i++) {
        if (strstr(transactions[i].date, datePart)) { // strstr for string matching (essentially searching the same string) the date
            printf("%d. %s - Rp. %d - %s - %s\n", i + 1, transactions[i].type, transactions[i].amount, transactions[i].date, transactions[i].category);
            found = 1;
        }
    }

    if (!found) {
        printf("No transactions found on %s.\n", datePart);
    }
}

void editTransaction() { // Function for editing the transactions
    int transactionIndex;
    viewAllTransactions();
    printf("Enter the transaction number to edit: "); 
    scanf("%d", &transactionIndex);
    transactionIndex--;

    if (transactionIndex < 0 || transactionIndex >= transactionCount) { // Type eror handling for the searching of the transactions index
        printf("Invalid transaction number.\n");
        return;
    }

    printf("Enter new details for this transaction: \n");
    printf("Enter amount: ");
    scanf("%d", &transactions[transactionIndex].amount);
    printf("Enter date (DD-MM-YYYY): ");
    scanf("%s", transactions[transactionIndex].date);
    printf("Enter category: ");
    scanf("%s", transactions[transactionIndex].category);

    printf("Transaction edited successfully!\n");
}

void deleteAllTransactions() { // Function for deleting all the transaction (includong all the saved transactions in the txt file)
    transactionCount = 0; // Reset the count effectively removes all transactions
    printf("All transactions have been deleted.\n"); 
}

void saveTransactionsToFile() { // Function to save transactions to a file
    FILE *file = fopen("transactions.txt", "w"); // Opening transaction file and writing it with "r"
    if (file == NULL) { // Eror handling type
        printf("Failed to open file.\n");
        return;
    }

    for (int i = 0; i < transactionCount; i++) { // looping through transaction count to print all the details of the transactions
        fprintf(file, "%s %d %s %s\n", transactions[i].type, transactions[i].amount, transactions[i].date, transactions[i].category);
    }

    fclose(file);
    printf("Transactions saved.\n");
}
