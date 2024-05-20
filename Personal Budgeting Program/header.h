//Personal Budgeting Program
//Shared header file
//Group 04
//Sayyid Dzaky A - 2306171846
//Hizkia Karl Anugrah N - 2306254810
//19-05-2024
//v 1.2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TRANSACTIONS 100

void programHeader();
void menu();
void addTransaction(const char *type);
void viewAllTransactions();
void viewBudgetSummary();
void searchTransactions();
void secondMenu(const char *transactionType);
void continueText();
void saveTransactionsToFile();
void loadTransactionsFromFile();
void editTransaction();
void exitProgram();
void searchTransactionsByDate();
void deleteAllTransactions();
void searchChoice();