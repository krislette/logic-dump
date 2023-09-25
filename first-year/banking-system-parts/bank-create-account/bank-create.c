#include <stdio.h> // for standard input output functions
#include <string.h> // for strcmp
#include <stdlib.h> // for itoa

#define MAX_ACC_DETAILS 50
#define BANK_DETAILS_FILE "accounts.txt"

FILE *file; // file for accounts.txt

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
void writeFile();
void createNewAccount();
float createDeposit();
int validInputChecker(int, int, int); 
int getInput(int, int);
void displayQuestion();

// main function
int main(int argc, const char * argv[]) {
    int exitChoice;

    fileChecker();

    readAccounts();

    printf("\n");
    printf("\t     +---------------------------------------------------+\n");  // program introductory title
    printf("\t     |       Welcome to PUP-On-Line Banking Systems      |\n");  
    printf("\t     +---------------------------------------------------+\n");
	printf("\t     |               CREATE A NEW ACCOUNT                |\n");
	printf("\t     +---------------------------------------------------+\n");

    do {
        createNewAccount();
        
        printf("\nAre you sure you want to exit?\n\n[1] Yes\n[2] No\n\nChoice: ");
        exitChoice = getInput(1, 2); // has two parameters: min, max
        
	} while (exitChoice == 2);
        
    printf("\nThank you for using the program.\n");
    
    return 0;
}

// function for printing '='
void dividerDesign(int count) {
    for (int i = 0; i < count - 1; i++) {
        printf("=");
    }   
    printf("=\n");
}

// function to check if the file is existing or not 
int fileChecker() {
    file = fopen(BANK_DETAILS_FILE, "r"); // opens the file in read mode

    if (file == NULL) {
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

    for (int i = 0; i < MAX_ACC_DETAILS; i++) {
        fscanf(file, "%s %s %f\n", accounts[i].accountNumber, accounts[i].accountPin, &accounts[i].accountBalance);

        if (strlen(accounts[i].accountNumber) != 0) {
            indexAccounts++;
        }
    }
    fclose(file);
}

// function for writing data entered into a text file
void writeFile() {
    file = fopen(BANK_DETAILS_FILE, "w");
    for (int i = 0; i < indexAccounts; i++) {
        fprintf(file, "%s %s %0.2f\n", accounts[i].accountNumber, accounts[i].accountPin, accounts[i].accountBalance);
    }
    fclose(file);
}

// function to create a new account
void createNewAccount() {
    int createAgain;

    do {
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

        printf("\nEnter a new account number: ");
        // takes an integer account number input from the user to be checked 
        while (scanf("%d", &newAccountNo) != 1) {
            printf("Invalid input. Try again.\n");
            
            while (getchar() != '\n');
            return createNewAccount();
        }
        
        // checks if the account number inputted by the user is a 5-digit number
        if (newAccountNo > 99999 || newAccountNo < 10000) {
            printf("Invalid input. Your account number should consist of 5 digits only.\n");
            return createNewAccount();
        }
        // converts the int input to string and stores 
        itoa(newAccountNo, accNo, 10); // syntax: itoa(int value, char str, int base) 

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
        itoa(newPin, pin, 10);
        printf("PIN acknowledged.\n");

        float initialBalance = createDeposit();

        for (int i = 0; i < MAX_ACC_DETAILS; i++) {
            if (strlen(accounts[i].accountNumber) == 0) {
                indexAccounts = i;
                break;
            }
        }

        strcpy(accounts[indexAccounts].accountNumber, accNo);
        strcpy(accounts[indexAccounts].accountPin, pin);
        accounts[indexAccounts].accountBalance = initialBalance;

        indexAccounts++;
        writeFile();
        
        printf("\nAccount created succesfully.\n\n");

        displayQuestion();
        createAgain = getInput(1, 2);
    } while (createAgain == 1);
}

// function to create initial deposit
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

    return deposit;
}

// function for checking if the choice entered by the user is a valid input
int validInputChecker(int input, int min, int max) {
    if (input < min || input > max) return 0;
    else return 1;
}

// function for getting input from the user with foolproofing
int getInput(int min, int max) {
    int userInput;

    scanf("%d",
        &userInput);

    int validInput = validInputChecker(userInput, min, max);

    if (!validInput) {
		printf("Invalid input. Enter numbers from %d-%d only.\n", min, max);

		while (getchar() != '\n');  // clears the input buffer
		userInput = getInput(min, max);
	}

	return userInput; // returns the valid user input
}

// function for displaying a question for the user
void displayQuestion() {
    printf("[1] Create an account again\n");
    printf("[2] Exit the program\n\n");
    printf("Choice: ");
}