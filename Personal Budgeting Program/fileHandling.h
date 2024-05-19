#include "main.h"
//#include "test1.c"


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