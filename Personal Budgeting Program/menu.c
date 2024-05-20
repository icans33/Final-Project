//Personal Budgeting Program
//Menu handling file
//Group 04
//Sayyid Dzaky A - 2306171846
//Hizkia Karl Anugrah N - 2306254810
//19-05-2024
//v 1.1

#include "header.h"

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
                    addTransaction("Income"); // Calling addTransaction function for income
                    secondMenu("Income"); // displaying second menu after transaction
                } while (1); // Always display second menu after adding transaction 
                break;
            case 2:
                do {
                    addTransaction("Expense"); // Calling addTransaction function for Expense
                    secondMenu("Expense"); // displaying second menu
                } while (1); // Always display second menu after adding transaction 
                break;
            case 3:
                viewAllTransactions(); // Calling view all transaction function
                continueText(); // Displaying the continue text 
                break;
            case 4:
                viewBudgetSummary(); // Calling view all transaction function
                continueText(); // Dislaying the continue text
                break;
            case 5:
                searchChoice(); // Calling the seachChoice menu function
                continueText(); // Displaying continue text
                break;
            case 6:
                editTransaction(); // calling function for editing transactions
                break;
            case 7:
                deleteAllTransactions(); // calling deleteAllTransaction function to delete all the existing transactions
                continueText(); // displaying continue text
                break;
            case 0:
                exitProgram(); // Function to exit the program
                break;
            default:
                printf("Invalid choice. Please try again.\n"); // Type eror handling
                break;
        }
    } while (choice != 0 );
}

void secondMenu(const char *transactionType) { // Function for displaying second menu
    int choice;
    do {
        programHeader(); // calling program header
        printf("|1. Continue the transaction|\n"); 
        printf("|2. Go to Main Menu         |\n");  
        printf("|0. Exit The Program        |\n");
        printf("-----------------------------\n"); // Menu display
        printf("Enter your choice: ");
        scanf("%d", &choice); 

        switch (choice) { // Iterating the option
        case 1:
            addTransaction(transactionType); // calling addTransaction of the respecting transaction type 
            break;
        case 2:
            menu(); // Go back to the main menu
        case 0:
            printf("Exiting program...\n");
            exitProgram(); // Exit the prgram
        default:
            printf("Invalid choice, please try again.\n");
            break;
        }
    } while (choice != 2 && choice != 0);
}

void searchChoice() { // Function for displaying menu for search choices
    int choice;

    printf("Search by: \n");
    printf("|1. Category                    |\n");
    printf("|2. Date                        |\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) // Iterating the choices 
    {
    case 1:
        searchTransactions(); // Calling the searchTransaction function
        break;
    case 2:
        searchTransactionsByDate(); // Calling the searchTransactionByDate function
        break;
    default:
        printf("Invalid choice, please try again.\n");
        break;
    }
}