#include <stdio.h> // for standard input output functions
#include <string.h> // for strcmp
#include <stdlib.h> // for itoa

#define MAX_ACC_DETAILS 50 
#define BANK_DETAILS_FILE "accounts.txt"
#define BANK_HISTORY_FILE "history.txt"

FILE *file; // file pointer for accounts.txt
FILE *file1; // file pointer for the transaction history (history.txt)

int indexAccounts = 0;

struct accountDetails {
    char accountNumber[6];
    char accountPin[5];
    float accountBalance;
} accounts[MAX_ACC_DETAILS];

// function prototypes
void dividerDesign(int);
int fileChecker();
void readAccounts();
int getDateMonth();
int getDateDay(int);
int getDateYear();
void writeFile();
void pinChecker(int);
int accountNoChecker();
int validInputChecker(int, int, int); 
int getInput(int, int);
void depositMoney(int, int, int, int);
void withdrawMoney(int, int, int, int);
void displayQuestion();

// main function
int main(int argc, const char * argv[]) {
    
    fileChecker();

    readAccounts();

    // checks if the file has any account details in it
    if(indexAccounts == 0) {
        printf("\n");
        dividerDesign(80);
        printf("\nDatabase empty. No existing account found.\n\n");
        dividerDesign(80);
        printf("\n");
        return 0;
    }

    printf("\t\t\t      UPDATE AN ACCOUNT\n");
    dividerDesign(80);

    // asks for the date from the user
    int month, day, year;

    printf("\nEnter the date [MM/DD/YYYY]:\n");
    printf("Example: 06/18/2023\n\n");
    month = getDateMonth();
    day = getDateDay(month);
    year = getDateYear();
    printf("\n");
    dividerDesign(80);
    printf("\n");

    // gets the account from the user and returns the index of the account if it is found existing 
    int accountIndex = accountNoChecker();

    printf("\n");
    dividerDesign(80);

    // after the account number and pin are checked,
    // proceeds to the actual program
    do {
        int choice;
        printf("\n");
        printf("\t     +---------------------------------------------------+\n");  // program introductory title
        printf("\t     |       Welcome to PUP-On-Line Banking Systems      |\n");  
        printf("\t     +---------------------------------------------------+\n");
        printf("\t     |                 UPDATE AN ACCOUNT                 |\n");
        printf("\t     +---------------------------------------------------+\n");
        printf("\t     |                  [1] DEPOSIT                      |\n");
        printf("\t     |                  [2] WITHDRAW                     |\n");
        printf("\t     |                  [3] EXIT                         |\n"); 
        printf("\t     +---------------------------------------------------+\n\n");

        printf("Press the number of your choice: ");
        choice = getInput(1, 3); // has two parameters: min, max

        switch(choice) {
            case 1: {
                depositMoney(accountIndex, month, day, year);
                break;
            }
            case 2: {
                withdrawMoney(accountIndex, month, day, year);
                break;
            }
            case 3: {
                printf("\nAre you sure you want to exit the program?\n\n[1] Yes\n[2] No\n\nChoice: ");
                int exitChoice = getInput(1, 2);

                if(exitChoice == 1) {
                    printf("\nThank you for using the program.\n");
                    return 0;
                }
            }
        }
    } while(1);

    return 0;
}

// function for printing '='
void dividerDesign(int count) {
    int i;

    for(i = 0; i < count - 1; i++) {
        printf("=");
    }   
    printf("=\n");
}

// function to check if the file is existing or not 
int fileChecker() {
    file = fopen(BANK_DETAILS_FILE, "r"); // opens the file in read mode

    if(file == NULL) {
        dividerDesign(80);
        printf("\n\t\t\t\t\b\bUnable to open file.\n\n");
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

// retrieves account details from the file
void readAccounts() {
    file = fopen(BANK_DETAILS_FILE, "r");

    for(int i = 0; i < MAX_ACC_DETAILS; i++) {
        fscanf(file, "%s %s %f\n", accounts[i].accountNumber, accounts[i].accountPin, &accounts[i].accountBalance);

        if(strlen(accounts[i].accountNumber) != 0) {
            indexAccounts++;
        }
    }
    fclose(file);
}

int getDateMonth() {
    int month;

    printf("Month: ");
    while(scanf("%d", &month) != 1 || month < 1 || month > 12) {
        printf("Invalid input. Enter a valid number for month.\n");

        while(getchar() != '\n');
        printf("Month: ");
    }

    return month;
}

int getDateDay(int month) {
    int day;

    printf("Day: ");
    if(month == 4 || month == 6 || month == 9 || month == 11) {
        while(scanf("%d", &day) != 1 || day < 1 || day > 30) {
            printf("Invalid input. Enter days from 1-30 only.\n");

            while(getchar() != '\n');
            printf("Day: ");
        }
    }
    else if(month == 2) {
        while(scanf("%d", &day) != 1 || day < 1 || day > 28) {
            printf("Invalid input. Enter days from 1-28 only.\n");

            while(getchar() != '\n');
            printf("Day: ");
        }
    }
    else {
        while(scanf("%d", &day) != 1 || day < 1 || day > 31) {
            printf("Invalid input. Enter days from 1-31 only.\n");

            while(getchar() != '\n');
            printf("Day: ");
        }
    }

    return day;
}

int getDateYear() {
    int year;

    printf("Year: ");
    while(scanf("%d", &year) != 1 || year < 1000 || year > 9999) {
        printf("Invalid input. Enter a valid year.\n");

        while(getchar() != '\n');
        printf("Year: ");
    }

    return year;
}

// function for writing data entered into a text file
void writeFile() {
    file = fopen(BANK_DETAILS_FILE, "w");
    for(int i = 0; i < indexAccounts; i++) {
        fprintf(file, "%s %s %0.2f\n", accounts[i].accountNumber, accounts[i].accountPin, accounts[i].accountBalance);
    }
    fclose(file);
}

// function to check the pin entered by the user
void pinChecker(int index) {
	int numberInput; // takes an integer input from the user (to be used for checking because we can't check strings 
    char pin[5]; // the character array storage for a valid account number
    
    printf("Enter PIN: ");
    // takes an integer account number input from the user to be checked 
    while(scanf("%d", &numberInput) != 1) {
    	printf("Invalid input. Try again.\n");
    	
    	while(getchar() != '\n');
    	printf("Enter PIN: ");
	}
	// checks if the account number inputted by the user is a 4-digit number
	if(numberInput > 9999 || numberInput < 1000) {
		printf("Invalid input. Your PIN should consist of 4 digits only.\n");
		return pinChecker(index);
	}
	// converts the int input to string and stores 
	itoa(numberInput, pin, 10); // syntax: itoa(int value, char str, int base) 

    if(strcmp(pin, accounts[index].accountPin) != 0) {
        printf("The pin you have entered is incorrect. Try again.\n");
        return pinChecker(index);
    }
}

// function to check the account number entered by the user
int accountNoChecker() {
    int numberInput; // takes an integer input from the user (to be used for checking because we can't check strings 
    char accNo[6]; // the character array storage for a valid account number
    int found = 0; 
    int index;
	
    printf("Enter account number: ");
    // takes an integer account number input from the user to be checked 
    while(scanf("%d", &numberInput) != 1) {
    	printf("Invalid input. Try again.\n");
    	
    	while(getchar() != '\n');
    	printf("Enter account number: ");
	}
	// checks if the account number inputted by the user is a 5-digit number
	if(numberInput > 99999 || numberInput < 10000) {
		printf("Invalid input. Your account number should consist of 5 digits only.\n");
		return accountNoChecker();
	}
	// converts the int input to string and stores 
	itoa(numberInput, accNo, 10); // syntax: itoa(int value, char str, int base) 

    for(int i = 0; i < MAX_ACC_DETAILS; i++) {
        if(strcmp(accounts[i].accountNumber, accNo) == 0) {
            found = 1;
            index = i;
            pinChecker(i);
        }
    }

    if(!found) {
        printf("Account Number not found. Try again.\n");
        return accountNoChecker();
    }

    return index;
}

// function for checking if the choice entered by the user is a valid input
int validInputChecker(int input, int min, int max) {
    if(input < min || input > max) return 0;
    else return 1;
}

// function for getting input from the user with foolproofing
int getInput(int min, int max) {
    int userInput;

    scanf("%d",
        &userInput);

    int validInput = validInputChecker(userInput, min, max);

    if(!validInput) {
		printf("Invalid input. Enter numbers from %d-%d only.\n", min, max);

		while(getchar() != '\n');  // clears the input buffer
		userInput = getInput(min, max);
	}

	return userInput; // returns the valid user input
}


// function for case 1: depositing the money
void depositMoney(int index, int month, int day, int year) {
    int caseOneChoice;

    do {
        float deposit;
        float givenBalanceTemp;

        printf("Enter the amount you want to deposit: ");
        while(scanf("%f", &deposit) != 1) {
            printf("Invalid input. Enter float or integer values only.\n");

            while(getchar() != '\n');
            printf("Enter the amount you want to withdraw: ");
        }

        // sa temp muna istore para if ever na sobra,
        // yung temp ang magbabago at hindi yung accountbalance variable
        givenBalanceTemp = accounts[index].accountBalance;
        givenBalanceTemp += deposit; 

        // checks if the current balance is too large for the bank to handle
        if(givenBalanceTemp > 1000000.0)
            printf("Invalid amount. Your deposit have exceeded the bank capacity.\n\n");
        else if(deposit < 500.0)
            printf("Invalid amount. The minimum deposit amount should be 500.00.\n\n");
        else {
            accounts[index].accountBalance = givenBalanceTemp;
            printf("\nAmount successfully deposited to your account.\n\n");

            writeFile(); // updates the file based on the successful transaction

            // opens the second file to update the transaction history
            file1 = fopen(BANK_HISTORY_FILE, "a"); // opens the second file in append mode
            fprintf(file1, "\n| %-13s | %-8s | %0.2d/%0.2d/%d | %-13.2f |               | %-13.2f |",
                accounts[index].accountNumber, accounts[index].accountPin, month, day, year, deposit, accounts[index].accountBalance);
            fprintf(file1, "\n+---------------+----------+------------+---------------+---------------+---------------+");
            fclose(file1); 
        }

        displayQuestion(); 
        caseOneChoice = getInput(1, 2);
    } while(caseOneChoice == 1);
}

// function for case 2: withdrawing money
void withdrawMoney(int index, int month, int day, int year) {
    int caseTwoChoice;

    do {
        float withdraw;

        printf("Enter the amount you want to withdraw: ");
        while(scanf("%f", &withdraw) != 1) {
            printf("Invalid input. Enter float or integer values only.\n");

            while(getchar() != '\n');
            printf("Enter the amount you want to withdraw: ");
        }

        // checks if the desired amount to withdraw is
        // greater than the user's current balance
        if(withdraw > accounts[index].accountBalance)
            printf("Invalid amount. The amount you want to withdraw exceeded your current balance.\n\n");
        else if(withdraw < 500.0) 
            printf("Invalid amount. The minimum withdrawal amount should be 500.00.\n\n");
        else {
            accounts[index].accountBalance -= withdraw;
            printf("\nAmount successfully withdrawn from your account.\n\n");

            writeFile(); // updates the file based on the successful transaction

            // opens the second file to update the transaction history
            file1 = fopen(BANK_HISTORY_FILE, "a"); // opens the second file in append mode
            fprintf(file1, "\n| %-13s | %-8s | %0.2d/%0.2d/%d |               | %-13.2f | %-13.2f |",
                accounts[index].accountNumber, accounts[index].accountPin, month, day, year, withdraw, accounts[index].accountBalance);
            fprintf(file1, "\n+---------------+----------+------------+---------------+---------------+---------------+");
            fclose(file1);  
        }
                    
        displayQuestion();
        caseTwoChoice = getInput(1, 2);
    } while(caseTwoChoice == 1);
}

// function for displaying a question for the user
void displayQuestion() {
    printf("[1] Do the transaction again\n");
    printf("[2] Go back to main menu\n\n");
    printf("Choice: ");
}