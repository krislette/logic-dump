#include <stdio.h> // for standard input output functions
#include <string.h> // for strcmp
#include <stdlib.h> // for itoa

#define MAX_ACC_DETAILS 50 // the maximum number of account details that the program and the file can hold
#define BANK_DETAILS_FILE "accounts.txt"
#define BANK_HISTORY_FILE "history.txt"

FILE *file; // file pointer for accounts.txt
FILE *file1; // file pointer for the transaction history (history.txt)

int indexAccounts = 0; // global variable for monitoring the number of accounts in the file

struct accountDetails {
    char accountNumber[6];
    char accountPin[5];
    float accountBalance;
} accounts[MAX_ACC_DETAILS]; // array of structures for holding the account details 

// function prototypes... each functon is discussed thoroughly on their respective definition
void dividerDesign(int);
int fileChecker();
void readAccounts();
int getDateMonth();
int getDateDay(int);
int getDateYear();
void writeFile();
void firstDisplay();
void createNewAccount();
float createDeposit();
void deleteAccount();
void pinChecker(int);
int accountNoChecker();
int validInputChecker(int, int, int); 
int getInput(int, int);
void viewBalance(int);
void depositMoney(int, int, int, int);
void withdrawMoney(int, int, int, int);
void displayQuestion();

// main function
int main(int argc, const char * argv[]) {
    if (!fileChecker()) return 1; // checks if the file exists or not 
    readAccounts(); // calls the function for reading the details from the .txt file

    int choice;

    do {
        printf("\n+---------------------------------------------------+\n");
        printf("| PUP-On-Line Banking Systems                       |\n");
        printf("+---------------------------------------------------+\n");
        printf("|\t[1] Open an existing account                |\n");
        printf("|\t[2] Create an account                       |\n");
        printf("|\t[3] Delete an account                       |\n");
        printf("|\t[4] Exit                                    |\n"); 
        printf("+---------------------------------------------------+\n\n");

        printf("Press the number of your choice: ");
        choice = getInput(1, 4); // has two parameters: min, max

        switch (choice) {
            case 1: {
                firstDisplay(); // goes back to main and proceeds with the actual program
                break;
            }
            case 2: {
                createNewAccount(); // calls the function for creating a new account
                break;
            }
            case 3: {
                deleteAccount(); // calls the function for deleting an existing account
                break;
            }
            case 4: {
                printf("Are you sure you want to exit the program?\n\n[1] Yes\n[2] No\n\nChoice: ");
                int exitChoice = getInput(1, 2);

                if (exitChoice == 1) {
                    printf("\nThank you for using PUP-On-Line Banking Systems.\n");
                    return 0;
                }
                break;
            }
        }
    } while (1);

    return 0;
}

// function for printing '='
void dividerDesign(int count) {
    for (int i = 0; i < count - 1; i++) {
        printf("=");
    }   
    printf("=\n");
}

// function for checking if the file exists or not 
int fileChecker() {
    file = fopen(BANK_DETAILS_FILE, "r"); // opens the file in read mode

    // checks if the file is existing or not by comparing to null
    if (file == NULL) {
        dividerDesign(80);
        printf("\n\n\t\t\t\t\b\bUnable to open file.\n\n");
        fclose(file);
        dividerDesign(80);
        printf("\n");

        return 0; 
    }
    dividerDesign(80);
    printf("\n\t\t\t   File opened successfully.\n\n");
    fclose(file);
    dividerDesign(80);

    return 1; 
}

// function for reading all of the account details from the file
void readAccounts() {
    file = fopen(BANK_DETAILS_FILE, "r");

    // retrieves account details from the file
    for (int i = 0; i < MAX_ACC_DETAILS; i++) {
        fscanf(file, "%s %s %f\n", accounts[i].accountNumber, accounts[i].accountPin, &accounts[i].accountBalance);

        if (strlen(accounts[i].accountNumber) != 0) {
            indexAccounts++; // variable increments as the program encounters a valid account detail from the .txt file
        }
    }
    fclose(file);
}

// function for checking if the month entered by the user is a valid month number
int getDateMonth() {
    int month;

    printf("Month: ");
    while (scanf("%d", &month) != 1 || month < 1 || month > 12) {
        printf("Invalid input. Enter a valid number for month.\n");

        while (getchar() != '\n');
        printf("Month: ");
    }

    return month; // returns the valid month value
}

// function for checking if the day entered by the user is valid with respect to the month entered
int getDateDay(int month) {
    int day;

    printf("Day: ");
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        while (scanf("%d", &day) != 1 || day < 1 || day > 30) {
            printf("Invalid input. Enter days from 1-30 only.\n");

            while (getchar() != '\n');
            printf("Day: ");
        }
    } else if (month == 2) {
        while (scanf("%d", &day) != 1 || day < 1 || day > 28) {
            printf("Invalid input. Enter days from 1-28 only.\n");

            while (getchar() != '\n');
            printf("Day: ");
        }
    } else {
        while (scanf("%d", &day) != 1 || day < 1 || day > 31) {
            printf("Invalid input. Enter days from 1-31 only.\n");

            while (getchar() != '\n');
            printf("Day: ");
        }
    }

    return day; // returns the valid day value 
}

// function for checking if the year entered by the user is valid year number
int getDateYear() {
    int year;

    printf("Year: ");
    while (scanf("%d", &year) != 1 || year < 1000 || year > 9999) {
        printf("Invalid input. Enter a valid year.\n");

        while (getchar() != '\n');
        printf("Year: ");
    }

    return year; // returns the valid year value
}

// function for overwriting the file based on the updated account details
void writeFile() {
    file = fopen(BANK_DETAILS_FILE, "w");
    for (int i = 0; i < indexAccounts; i++) {
        fprintf(file, "%s %s %0.2f\n", accounts[i].accountNumber, accounts[i].accountPin, accounts[i].accountBalance);
    }
    fclose(file);
}

// function for displaying and manipulating the first segment of the program
void firstDisplay() {
    // checks if the file has any account details in it
    if (indexAccounts == 0) {
        printf("\n");
        dividerDesign(80);
        printf("\nDatabase empty. No existing account found.\n\n");
        dividerDesign(80);
        printf("\n");
        return;
    }

    // asks for the date from the user
    int month, day, year;

    printf("\nEnter the date [MM/DD/YYYY]:\n");
    printf("Example: 06/18/2023\n\n");
    month = getDateMonth(); // calls the function for getting a valid month number and assigns the returned value to variable month
    day = getDateDay(month); // calls the function for getting a valid day number for its corresponding month number
    year = getDateYear(); // calls the function for getting a valid year number and assigns the returned value to variable year
    printf("\n");
    dividerDesign(80);
    printf("\n");

    // gets the account from the user and returns the index of the account if it is found existing 
    int accountIndex = accountNoChecker();

    printf("\n");
    dividerDesign(80);

    // after the account number and pin are checked, proceeds to the actual program
    do {
        int choice;
        printf("\n");
        printf("+---------------------------------------------------+\n");
        printf("| Welcome to PUP-On-Line Banking Systems            |\n");
        printf("+---------------------------------------------------+\n");
        printf("|\t[1] Balance Inquiry                         |\n");
        printf("|\t[2] Deposit                                 |\n");
        printf("|\t[3] Withdraw                                |\n");
        printf("|\t[4] Exit                                    |\n");
        printf("+---------------------------------------------------+\n\n");

        printf("Press the number of your choice: ");
        choice = getInput(1, 4); // calls the function getinput which checks if the input is valid & it has two parameters: min, max

        switch (choice) {
            case 1: {
                viewBalance(accountIndex);
                break;
            }
            case 2: {
                depositMoney(accountIndex, month, day, year);
                break;
            }
            case 3: {
                withdrawMoney(accountIndex, month, day, year);
                break;
            }
            case 4: {
                printf("Are you sure you want to exit from this account?\n\n[1] Yes\n[2] No\n\nChoice: ");
                int exitChoice = getInput(1, 2);

                if (exitChoice == 1) {
                    return;
                }
                break;
            }  
        }
    } while(1);
}

// function for creating a new account
void createNewAccount() {
    int createAgain;

    do {
        // checks if the maximum account details is reached
        if (indexAccounts >= MAX_ACC_DETAILS) {
            printf("\n");
            dividerDesign(80);
            printf("\nMaximum number of accounts reached. Cannot add more accounts.\n\n");
            dividerDesign(80);
            printf("\n");
            return;
	    }

        int newAccountNo; // takes an integer input from the user
        char accNo[6]; // the character array storage for a valid account number 

        printf("\n");
        dividerDesign(80);
        printf("\t\t\t\tCREATE NEW ACCOUNT\n");
        dividerDesign(80);
        printf("\nEnter a new account number: ");
        // takes an integer account number input from the user to be checked 
        while (scanf("%d", &newAccountNo) != 1) {
            printf("Invalid input. Try again.\n");
            
            while (getchar() != '\n');
            printf("Enter a new account number: ");
        }
        // checks if the account number inputted by the user is a 5-digit number
        if (newAccountNo > 99999 || newAccountNo < 10000) {
            printf("Invalid input. Your account number should consist of 5 digits only.\n");
            return createNewAccount();
        }
        // converts the int input to string and stores it to a character array
        itoa(newAccountNo, accNo, 10); // syntax: itoa(int value, char str, int base) 

        // checks if there if the account number given by the user already exists
        int found = 0;
        for (int i = 0; i < MAX_ACC_DETAILS; i++) {
            if (strcmp(accounts[i].accountNumber, accNo) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            printf("Account Number already exists. Try again.\n");
            return createNewAccount();
        }
        printf("Account Number acknowledged.\n");

        int newPin;
        char pin[5]; // the character array storage for a valid pin

        printf("\nEnter a new PIN for the account: ");
        // takes an integer account pin input from the user to be checked 
        while (scanf("%d", &newPin) != 1 || newPin > 9999 || newPin < 1000) {
            printf("Invalid input. Try again.\n");
            
            while (getchar() != '\n');
            printf("Enter a new pin for the account: ");
        }
        // converts the int input to string and stores it to a character array
        itoa(newPin, pin, 10);
        printf("PIN acknowledged.\n");

        float initialBalance = createDeposit(); // calls the function for checking for a valid initial deposit

        for (int i = 0; i < MAX_ACC_DETAILS; i++) {
            if (strlen(accounts[i].accountNumber) == 0) {
                indexAccounts = i; // finds the index to which the program will store the new account details
                break;
            }
        }

        // stores the new account details to the program
        strcpy(accounts[indexAccounts].accountNumber, accNo);
        strcpy(accounts[indexAccounts].accountPin, pin);
        accounts[indexAccounts].accountBalance = initialBalance;

        indexAccounts++; // increments the monitor variable for the number of accounts stored in both the program and the .txt file
        writeFile(); // calls the function which updates the details on the .txt file
        
        printf("\nAccount created succesfully.\n\n");

        displayQuestion();
        createAgain = getInput(1, 2);
    } while (createAgain == 1);
}

// function that will check the initial balance entered by the user
float createDeposit() {
    float deposit;

    printf("\nEnter initial deposit of at least P100 for the account: ");
    // takes a float integer for initial deposit input from the user to be checked 
    while (scanf("%f", &deposit) != 1) {
    	printf("Invalid input. Try again.\n");
    	
    	while (getchar() != '\n');
    	printf("Enter initial deposit for the account: ");
	}
    // checks if the initial deposit inputted by the user is a valid amount
	if (deposit > 1000000.00 || deposit < 99.99) {
		printf("Invalid amount. Initial deposit should at least be P100.\n");
		return createDeposit();
	}
    printf("Initial deposit acknowledged.\n");

    return deposit; // returns the valid deposit 
}

// function for deleting an existing account
void deleteAccount() {
    int deleteAgain;
    
    do {
        // checks if the file is empty [no single account stored]
        if (indexAccounts == 0) {
            printf("\n");
            dividerDesign(80);
            printf("\nDatabase empty. No existing account found.\n\n");
            dividerDesign(80);
            printf("\n");
            return; // returns to the first segment of the program
        } else {
            int numberInp;
            char deleteAcc[6];
            int accInd;

            printf("\n");
            dividerDesign(80);
            printf("\t\t\t\tDELETE AN ACCOUNT\n");
            dividerDesign(80);
            printf("\n\tEnter the account number of the account you want to delete: ");
            // takes an integer account number input from the user to be checked 
            while (scanf("%d", &numberInp) != 1 || numberInp < 10000 || numberInp > 99999) {
                printf("\tInvalid input. Enter a valid account number.\n");

                while (getchar() != '\n');
                printf("\tEnter the account number of the account you want to delete: ");
            }
            // converts the int input to string and stores it to a character array
            itoa(numberInp, deleteAcc, 10);

            int found = 0;
            for (int i = 0; i < MAX_ACC_DETAILS; i++) {
                if (strcmp(accounts[i].accountNumber, deleteAcc) == 0) {
                    found = 1;
                    accInd = i;
                    pinChecker(i); // if the account number exists, checks for the matching pin
                    break;
                }
            }
            
            if (!found) {
                printf("\tAccount Number not found. Try again.\n");
                return deleteAccount();
            }

            printf("\n");
            dividerDesign(80);
    
            printf("\nAre you sure you want to delete this account?\n\n[1] Yes\n[2] No\n\n");
            printf("Choice: ");

            if (getInput(1, 2) == 2) return;

            // deletes the given account with the use of swapping
            for (int i = 0; i < indexAccounts; i++) {
                if (i >= accInd) {
                    accounts[i] = accounts[i + 1];
                }
            }

            indexAccounts--; // decrements the variable monitor for the number of accounts
            writeFile(); // updates the details in the .txt file

            printf("Account deleted successfully.\n\n");

            displayQuestion();
            deleteAgain = getInput(1, 2);
        }
    } while (deleteAgain == 1);
}

// function to check the pin entered by the user
void pinChecker(int index) {
	int numberInput; // takes an integer input from the user (to be used for checking because we can't check strings 
    char pin[5]; // the character array storage for a valid account number
    
    printf("\tEnter PIN: ");
    // takes an integer PIN input from the user to be checked 
    while (scanf("%d", &numberInput) != 1) {
    	printf("\tInvalid input. Try again.\n");
    	
    	while (getchar() != '\n');
    	printf("\tEnter PIN: ");
	}
	// checks if the PIN inputted by the user is a 4-digit number
	if (numberInput > 9999 || numberInput < 1000) {
		printf("\tInvalid input. Your PIN should consist of 4 digits only.\n");
		return pinChecker(index);
	}
	// converts the int input to string and stores it to a character array
	itoa(numberInput, pin, 10); // syntax: itoa(int value, char str, int base) 

    if (strcmp(pin, accounts[index].accountPin) != 0) {
        printf("\tThe pin you have entered is incorrect. Try again.\n");
        return pinChecker(index);
    }
}

// function to check the account number entered by the user
int accountNoChecker() {
    int numberInput; // takes an integer input from the user (to be used for checking because we can't check strings 
    char accNo[6]; // the character array storage for a valid account number
    int found = 0; 
    int index;
	
    printf("\tEnter account number: ");
    // takes an integer account number input from the user to be checked 
    while (scanf("%d", &numberInput) != 1) {
    	printf("\tInvalid input. Try again.\n");
    	
    	while (getchar() != '\n');
    	printf("\tEnter account number: ");
	}
	// checks if the account number inputted by the user is a 5-digit number
	if (numberInput > 99999 || numberInput < 10000) {
		printf("\tInvalid input. Your account number should consist of 5 digits only.\n");
		return accountNoChecker();
	}
	// converts the int input to string and stores it to a character array
	itoa(numberInput, accNo, 10); // syntax: itoa(int value, char str, int base) 

    for (int i = 0; i < MAX_ACC_DETAILS; i++) {
        if (strcmp(accounts[i].accountNumber, accNo) == 0) {
            found = 1;
            index = i;
            pinChecker(i); // checks for the matching pin
        }
    }

    if (!found) {
        printf("\tAccount Number not found. Try again.\n");
        return accountNoChecker();
    }

    return index; // returns the index to main, to be used for succeeding parts of the program
}

// function for checking if the choice entered by the user is a valid input
int validInputChecker(int input, int min, int max) {
    if (input < min || input > max) return 0; // returns 0 for false
    else return 1; // returns 1 for true
}

// function for getting input from the user with foolproofing
int getInput(int min, int max) {
    int userInput;

    scanf("%d",
        &userInput);

    int validInput = validInputChecker(userInput, min, max); // checks if the input is valid 

    if (!validInput) {
		printf("Invalid input. Enter numbers from %d-%d only.\n", min, max);

		while (getchar() != '\n'); // clears the input buffer
		userInput = getInput(min, max);
	}

	return userInput; // returns the valid user input
}

// function for case 1: viewing the balance to main
void viewBalance(int index) {
    int caseOneChoice;
    do {
        // prints the current balance of the user
        printf("Your balance is: P%0.2f\n\n", accounts[index].accountBalance);

        displayQuestion();
        caseOneChoice = getInput(1, 2);
    } while (caseOneChoice == 1);
}

// function for case 2: depositing the money
void depositMoney(int index, int month, int day, int year) {
    int caseTwoChoice;

    do {
        float deposit;
        float givenBalanceTemp;

        printf("Enter the amount you want to deposit: ");
        while (scanf("%f", &deposit) != 1) {
            printf("Invalid input. Enter float or integer values only.\n");

            while (getchar() != '\n');
            printf("Enter the amount you want to deposit: ");
        }

        givenBalanceTemp = accounts[index].accountBalance; // stores data to temp to avoid 
        givenBalanceTemp += deposit; 

        // checks if the current balance is too large for the bank to handle
        if (givenBalanceTemp > 1000000.0) {
            printf("Invalid amount. Your deposit have exceeded the bank capacity.\n\n");
        } else if (deposit < 500.0) {
            printf("Invalid amount. The minimum deposit amount should be 500.00.\n\n");
        } else {
            accounts[index].accountBalance = givenBalanceTemp;
            printf("Amount successfully deposited to your account.\n\n");

            writeFile(); // updates the file based on the successful transaction

            // opens the second file to update the transaction history
            file1 = fopen(BANK_HISTORY_FILE, "a"); // opens the second file in append mode
            fprintf(file1, "\n| %-13s | %-8s | %0.2d/%0.2d/%d | %-13.2f |               | %-13.2f |",
                accounts[index].accountNumber, accounts[index].accountPin, month, day, year, deposit, accounts[index].accountBalance);
            fprintf(file1, "\n+---------------+----------+------------+---------------+---------------+---------------+");
            fclose(file1); 
        }

        displayQuestion(); 
        caseTwoChoice = getInput(1, 2);
    } while (caseTwoChoice == 1);
}

// function for case 3: withdrawing money
void withdrawMoney(int index, int month, int day, int year) {
    int caseThreeChoice;

    do {
        float withdraw;

        printf("Enter the amount you want to withdraw: ");
        while (scanf("%f", &withdraw) != 1) {
            printf("Invalid input. Enter float or integer values only.\n");

            while (getchar() != '\n');
            printf("Enter the amount you want to withdraw: ");
        }

        // checks if the desired amount to withdraw is greater than the user's current balance
        if (withdraw > accounts[index].accountBalance) {
            printf("Invalid amount. The amount you want to withdraw exceeded your current balance.\n\n");
        } else if (withdraw < 500.0) {
            printf("Invalid amount. The minimum withdrawal amount should be 500.00.\n\n");
        } else {
            accounts[index].accountBalance -= withdraw;
            printf("Amount successfully withdrawn from your account.\n\n");

            writeFile(); // updates the file based on the successful transaction

            // opens the second file to update the transaction history
            file1 = fopen(BANK_HISTORY_FILE, "a"); // opens the second file in append mode
            fprintf(file1, "\n| %-13s | %-8s | %0.2d/%0.2d/%d |               | %-13.2f | %-13.2f |",
                accounts[index].accountNumber, accounts[index].accountPin, month, day, year, withdraw, accounts[index].accountBalance);
            fprintf(file1, "\n+---------------+----------+------------+---------------+---------------+---------------+");
            fclose(file1);  
        }
                    
        displayQuestion();
        caseThreeChoice = getInput(1, 2);
    } while (caseThreeChoice == 1);
}

// function for displaying a question for the user
void displayQuestion() {
    printf("[1] Do the transaction again\n");
    printf("[2] Go back to main menu\n\n");
    printf("Choice: ");
}