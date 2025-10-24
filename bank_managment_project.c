#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

// Structure to hold account information
typedef struct {
    char name[50];
    int accountNumber;
    char password[20];
    int balance;
} Account;

void createAccount();
void atmOptions(Account* account);
void viewAccountDetails();
void saveAccount(Account account);
int authenticateUser(int accountNumber, char* password, Account* account);
void deposit_money(Account* account);
void withdraw_money(Account* account);
void transfer_money(Account* account);
void checkDetail(Account* account);
void transaction_details();
void LastDetail(Account* account);
void bankMenu(); // Renamed to avoid conflict with login menu
void closeBank();
void fordelay(int j);
void loginMenu();
void closeLogin();

// Main function (Login System)
int main() {
    char pass[10];
    char password[10] = "pass";
    int i = 0, main_exit;
    printf("\n\n\n\t\t\t\t   Bank  management system [ DEVELOPED BY AYUSH ANAND TELI ] \n\t\t\t\t\t User Login ");
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login: ");
    scanf("%9s", pass);  // Limiting input to 9 characters to avoid buffer overflow

    if (strcmp(pass, password) == 0) {
        printf("\n\nPassword Match!\nLOADING");
        for (i = 0; i <= 6; i++) {
            fordelay(100000000);
            printf(". ");
        }
        printf("\n");
        system("pause");
        system("cls");
        bankMenu();  // Go to bank management system after successful login
    } else {
        printf("\n\nWrong password!!\a\a\a");
        while (1) {
            printf("\nEnter 1 to try again and 0 to exit: ");
            scanf("%d", &main_exit);

            if (main_exit == 1) {
                system("cls");
                main();  // Restart the login process
            } else if (main_exit == 0) {
                system("cls");
                closeLogin();
                break;
            } else {
                printf("\nInvalid!");
                fordelay(1000000000);
                system("cls");
            }
        }
    }
    return 0;
}

// Simulate delay
void fordelay(int j) {
    for (int i = 0; i < j; i++) {
        // No operation, just delay
    }
}

// Closing function for login system
void closeLogin() {
    printf("Exiting the system...\n");
    exit(0);
}

// Bank Management System Menu
void bankMenu() {
    int choice;
    while (1) {
        printf("Welcome to Ayush Bank\n");
        printf("1. Create an Account\n");
        printf("2. ATM Options\n");
        printf("3. View Account Details\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2: {
                int accountNumber;
                char password[20];
                Account account;

                printf("Enter your account number: ");
                scanf("%d", &accountNumber);

                printf("Enter your password: ");
                scanf("%s", password);

                if (authenticateUser(accountNumber, password, &account)) {
                    atmOptions(&account);
                } else {
                    printf("Authentication failed! Wrong account number or password.\n");
                }
                break;
            }
            case 3:
                viewAccountDetails();
                break;
            case 4:
                closeBank();
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

// Closing function for bank management system
void closeBank() {
    printf("Exiting the system...\n");
    exit(0);
}

// Function to create a new account
void createAccount() {
    Account account;

    printf("Enter your name: ");
    getchar();  // To consume the newline left by scanf
    fgets(account.name, 50, stdin);
    account.name[strcspn(account.name, "\n")] = 0; // Remove trailing newline

    printf("Create an account number: ");
    scanf("%d", &account.accountNumber);

    printf("Create a password: ");
    scanf("%s", account.password);

    account.balance = 1000; // Initial balance

    saveAccount(account);

    printf("Account created successfully!\n");
}

// Function for ATM Options
void atmOptions(Account* account) {
    int ch;
    while (1) {
        menu();
        printf("\nEnter your choice:\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                deposit_money(account);
                break;
            case 2:
                withdraw_money(account);
                break;
            case 3:
                transfer_money(account);
                break;
            case 4:
                checkDetail(account);
                break;
            case 5:
                transaction_details();
                break;
            case 6:
                LastDetail(account);
                closeBank();
                break;
            default:
                printf("*****Invalid choice*****\n");
        }
    }
}

// Function to display the ATM menu
void menu() {
    printf("\n\tATM MENU\n");
    printf("==============================================\n");
    printf("1. Deposit Money\n");
    printf("2. Withdraw Money\n");
    printf("3. Transfer Money\n");
    printf("4. Account details\n");
    printf("5. Transaction details\n");
    printf("6. Exit\n");
    printf("==============================================\n");
}

// Function to deposit money
void deposit_money(Account* account) {
    int dip_amt;
    time_t tm;
    time(&tm);

    FILE *ptr = fopen("Account.txt", "a");
    printf("*****DEPOSITING MONEY*****\n");
    printf("Enter the amount you want to deposit: ");
    scanf("%d", &dip_amt);

    account->balance += dip_amt;
    printf("****Money Deposited****\n");
    printf("New balance: %d\n", account->balance);
    fprintf(ptr, "Rs%d deposited to account %d on %s\n", dip_amt, account->accountNumber, ctime(&tm));

    fclose(ptr);
    printf("Press any key....\n");
    getch();
}

// Function to withdraw money
void withdraw_money(Account* account) {
    int with_amt;
    time_t tm;
    time(&tm);

    FILE *ptr = fopen("Account.txt", "a");
    printf("*****WITHDRAWING MONEY*****\n");
    printf("Enter the amount you want to withdraw: ");
    scanf("%d", &with_amt);

    if (account->balance < with_amt) {
        printf("****Insufficient balance****\n");
    } else {
        account->balance -= with_amt;
        printf("*****Money withdrawn*****\n");
        printf("New balance: %d\n", account->balance);
        fprintf(ptr, "Rs%d withdrawn from account %d on %s\n", with_amt, account->accountNumber, ctime(&tm));
    }

    fclose(ptr);
    printf("Press any key....\n");
    getch();
}

// Function to transfer money
void transfer_money(Account* account) {
    int trans_amt, target_acc_no;
    time_t tm;
    time(&tm);

    FILE *ptr = fopen("Account.txt", "a");
    printf("*****TRANSFERRING MONEY*****\n");
    printf("Enter the account number to transfer money: ");
    scanf("%d", &target_acc_no);
    printf("Enter the amount you want to transfer: ");
    scanf("%d", &trans_amt);

    if (account->balance < trans_amt) {
        printf("****Insufficient balance****\n");
    } else {
        account->balance -= trans_amt;
        printf("****Money Transferred****\n");
        printf("New balance: %d\n", account->balance);
        fprintf(ptr, "Rs%d transferred from account %d to account %d on %s\n", trans_amt, account->accountNumber, target_acc_no, ctime(&tm));
    }

    fclose(ptr);
    printf("Press any key....\n");
    getch();
}

// Function to check account details
void checkDetail(Account* account) {
    printf("ACCOUNT DETAILS\n");
    printf("==============================================\n");
    printf("Name: %s\n", account->name);
    printf("Account Number: %d\n", account->accountNumber);
    printf("Balance: %d\n", account->balance);
    printf("==============================================\n");
    printf("Press any key.....\n");
    getch();
}

// Function to view transaction details
void transaction_details() {
    system("cls");

    FILE *ptr = fopen("Account.txt", "r");
    char c;

    if (ptr == NULL) {
        printf("No transaction details available.\n");
        return;
    }

    printf("TRANSACTION DETAILS\n");
    printf("==============================================\n");
    c = fgetc(ptr);
    while (c != EOF) {
        putchar(c);
        c = fgetc(ptr);
    }
    printf("\n==============================================\n");

    fclose(ptr);
    printf("Press any key....\n");
    getch();
}

// Function to view last account details
void LastDetail(Account* account) {
    checkDetail(account);
    printf("\n\nPress any key to exit.....");
    getch();
}

// Function to view account details
void viewAccountDetails() {
    int accountNumber;
    char password[20];
    Account account;

    printf("Enter your account number: ");
    scanf("%d", &accountNumber);

    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticateUser(accountNumber, password, &account)) {
        checkDetail(&account);
    } else {
        printf("Authentication failed! Wrong account number or password.\n");
    }
}

// Function to save account information to file
void saveAccount(Account account) {
    FILE *file = fopen("clients.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s %d %s %d\n", account.name, account.accountNumber, account.password, account.balance);
    fclose(file);
}

// Function to authenticate user
int authenticateUser(int accountNumber, char* password, Account* account) {
    FILE *file = fopen("clients.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    while (fscanf(file, "%s %d %s %d", account->name, &account->accountNumber, account->password, &account->balance) != EOF) {
        if (account->accountNumber == accountNumber && strcmp(account->password, password) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
