#define MAX_TRANSACTIONS 100

void programHeader();
void menu();
void addTransaction(const char *type);
void viewAllTransactions();
void viewBudgetSummary();
void searchTransactions();

struct Transaction { // data struct for keeping each transaction data
    char type[8]; // "Income" or "Expense"
    int amount;
    char date[11]; // Format DD-MM-YYYY
    char category[20];
};

struct Transaction transactions[MAX_TRANSACTIONS]; //calling the struct and assigning it  
int transactionCount = 0;