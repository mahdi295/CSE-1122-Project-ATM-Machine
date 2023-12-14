#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

// Structure to store account details

struct atm
{
    char name[30];
    char password[30];
    int balance;
} details;

// File pointer for file operations, and counters for transactions and statements

FILE *fp = NULL;
int count = 0;
int count1 = 0;
int count2 = 0;
int count3 = 0;

// Function to clear the console screen

void clearScreen()
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Unix/Linux
#endif
}

// Function to pause execution and wait for a key press

void pauseExecution()
{
    printf("\n                                                  Press any key to continue...");
    getch(); // Using getch() for better user interaction
    clearScreen();
}

// Function to open a new account

void Account()
{
    clearScreen();
    printf("                                                  Welcome to ABC account opening form\n");
    printf("                                                  Please fill in your details\n");
    printf("\n");
    printf("                                                  Enter your name: ");
    fflush(stdin);
    gets(details.name);
    printf("                                                  Create password: ");
    fflush(stdin);
    gets(details.password);
    printf("                                                  Enter opening balance: ");
    scanf("%d", &details.balance);
    clearScreen();
    printf("                                                  Congrats! Your Account has been opened.\n");
    pauseExecution();
}

// Function to check account balance

void checkBalance()
{
    clearScreen();
    printf("                                                  %d taka in your Account\n", details.balance);
    pauseExecution();
}

// Function to deposit money into the account

void depositMoney()
{
    int depositAmount;

    printf("                                                  Enter the amount you want to deposit: ");
    scanf("%d", &depositAmount);

    if (depositAmount > 0)
    {
        details.balance += depositAmount;
        clearScreen();
        printf("                                                  %d taka successfully deposited into your Account\n", depositAmount);
    }
    else
    {
        clearScreen();
        printf("                                                  Invalid deposit amount. Please enter an amount greater than zero.\n");
    }
    pauseExecution();
}

// Function to withdraw money from the account

void withdrawMoney()
{
    int amount;
    int checkName, checkPass;
    char username[30];
    char userpassword[30];
    fp = fopen("withdraw.txt", "w");

Tryagain:
    printf("                                                  Enter your name: ");
    fflush(stdin);
    gets(username);
    printf("                                                  Enter your password: ");
    fflush(stdin);
    gets(userpassword);

Tryagain1:
    printf("                                                  Enter amount: ");
    scanf("%d", &amount);

    checkName = strcmp(username, details.name);
    checkPass = strcmp(userpassword, details.password);

    if (checkName == 0 && checkPass == 0)
    {
        if (amount > details.balance || amount < 1)
        {
            clearScreen();
            printf("                                                  Invalid withdrawal amount.\n");
            goto Tryagain1;
        }
        else
        {
            details.balance -= amount;
            printf("\n");
            clearScreen();
            printf("                                                  %d taka successfully withdrawn from your Account\n", amount);

            count++;
        }
    }
    else
    {
        clearScreen();
        printf("                                                  Invalid username or password. Please try again.\n");
        goto Tryagain;
    }

    fwrite(&amount, sizeof(amount), 1, fp);
    fwrite(&details.balance, sizeof(details.balance), 1, fp);
    fclose(fp);
    pauseExecution();
}

// Function to transfer money from one account to another

void TransferMoney()
{
    int amount;
    int checkName, checkPass;
    int receiverAcc;
    char receivername[30];
    char username[30];
    char userpassword[30];
    fp = fopen("transfer.txt", "w");

Tryagain:
    printf("                                                  Enter your name: ");
    fflush(stdin);
    gets(username);
    printf("                                                  Enter your password: ");
    fflush(stdin);
    gets(userpassword);
    printf("                                                  Enter receiver name: ");
    fflush(stdin);
    gets(receivername);
    printf("                                                  Enter receiver account number: ");
    scanf("%d", &receiverAcc);

Tryagain1:
    printf("                                                  Enter amount: ");
    scanf("%d", &amount);

    checkName = strcmp(username, details.name);
    checkPass = strcmp(userpassword, details.password);

    if (checkName == 0 && checkPass == 0)
    {
        if (amount > details.balance || amount < 1)
        {
            clearScreen();
            printf("                                                  Invalid transfer amount.\n");

            goto Tryagain1;
        }
        else
        {
            clearScreen();
            details.balance -= amount;
            printf("                                                  %d taka successfully transferred to %s's Account\n", amount, receivername);

            count1++;
        }
    }
    else
    {
        clearScreen();
        printf("                                                  Invalid username or password. Please try again.\n");

        goto Tryagain;
    }

    fwrite(&amount, sizeof(amount), 1, fp);
    fwrite(&details.balance, sizeof(details.balance), 1, fp);
    fclose(fp);
    pauseExecution();
}

// Function to view transaction statements

void seeStatement()
{
    int wamount, tamount;
    int wbalance, tbalance;
    fp = fopen("withdraw.txt", "r");
    printf("\n                                                        *****Withdraw statement*****\n");
    printf("                                                  Withdraw Amount           Account balance\n");
    for (int i = 0; i < count; i++)
    {
        fread(&wamount, sizeof(wamount), 1, fp);
        fread(&wbalance, sizeof(wbalance), 1, fp);
        printf("                                                        %d                 %d\n", wamount, wbalance);
    }
    fclose(fp);

    fp = fopen("transfer.txt", "r");
    printf("\n                                                        *****Transfer statement*****\n");
    printf("                                                  Transferred Amount            Account balance\n");
    for (int j = 0; j < count1; j++)
    {
        fread(&tamount, sizeof(tamount), 1, fp);
        fread(&tbalance, sizeof(tbalance), 1, fp);
        printf("                                                         %d                   %d\n", tamount, tbalance);
    }
    fclose(fp);
    pauseExecution();
}

// Function to display the main menu

void menu()
{
    char ch;
    int ch1;
    printf("\n");
    printf("\n");
    printf("                                                  |--------------------------------------|\n");
    printf("                                                  |--------------------------------------|");
    printf("\n                                                  | ***Hello Sir! Welcome To ABC ATM *** |\n");
    printf("                                                  |--------------------------------------|\n");
    printf("                                                  |--------------------------------------|\n\n\n");
    //printf("                 \n");
    //printf("                  \n");
    printf("                                                  First, you need to open your account.\n");

Tryagain:
    printf("                                                  Press Y or y to start the account opening process: ");
    scanf(" %c", &ch);
    printf("\n");
    if (ch == 'y' || ch == 'Y')
    {
        Account();
    }
    else
    {
        clearScreen();
        printf("                                                  Sorry! You have pressed an invalid key. Try again.\n");
        printf("\n\n");
        goto Tryagain;
    }

    while (1)
    {
        printf("\n");
        printf("                                                  Enter 1. for depositing money\n");
        printf("                                                  Enter 2. for checking your balance\n");
        printf("                                                  Enter 3. for withdrawing money\n");
        printf("                                                  Enter 4. for transferring money\n");
        printf("                                                  Enter 5. for viewing transaction statements\n");
        printf("                                                  Enter 6. for exit\n");
        printf("                                                  Please choose any option: ");
        scanf("%d", &ch1);

        switch (ch1)
        {
        case 1:
            clearScreen();
            depositMoney();
            break;
        case 2:
            clearScreen();
            checkBalance();
            break;
        case 3:
            clearScreen();
            withdrawMoney();
            break;
        case 4:
            clearScreen();
            TransferMoney();
            break;
        case 5:
            clearScreen();
            seeStatement();
            break;
        case 6:
            exit(0);
            break;
        default:
            clearScreen();
            printf("                                                  Sorry! Invalid number. Try again.\n");
            break;
        }
    }
}

// Main function

int main()
{
    menu();
    return 0;
}
