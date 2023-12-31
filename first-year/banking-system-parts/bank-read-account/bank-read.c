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
void pinChecker(int);
int accountNoChecker();
int validInputChecker(int, int, int); 
int getInput(int, int);
void displayQuestion();

// main function
int main(int argc, const char * argv[]) {
    int choice, exitChoice;

    fileChecker();

    readAccounts();

    // checks if the file has any account details in it
    if (indexAccounts == 0) {
        printf("\n");
        dividerDesign(80);
        printf("\nDatabase empty. No existing account found.\n\n");
        dividerDesign(80);
        printf("\n");
        return 0;
    }
    
    printf("\n");
    printf("\t     +---------------------------------------------------+\n");  // program introductory title
    printf("\t     |       Welcome to PUP-On-Line Banking Systems      |\n");  
    printf("\t     +---------------------------------------------------+\n");
	printf("\t     |                 BALANCE INQUIRY                   |\n");
	printf("\t     +---------------------------------------------------+\n");
    
    do {
        do {
            // gets the account from the user and returns the index of the account if it is found existing
            int accountIndex = accountNoChecker();
        
            // after the account number and pin are checked, proceeds to the display the current balance
            printf("\nYour balance is: P%0.2f\n\n", accounts[accountIndex].accountBalance);
        
            displayQuestion();
            choice = getInput(1, 2); // has two parameters: min, max

        } while (choice == 1);
    
        printf("\nAre you sure you want to exit?\n\n[1] Yes\n[2] No\n\nChoice: ");
        exitChoice = getInput(1, 2); 

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

// function to check the pin entered by the user
void pinChecker(int index) {
	int numberInput; // takes an integer input from the user (to be used for checking because we can't check strings 
    char pin[5]; // the character array storage for a valid account number
    
    printf("Enter PIN: ");
    // takes an integer account number input from the user to be checked 
    while (scanf("%d", &numberInput) != 1) {
    	printf("Invalid input. Try again.\n");
    	
    	while (getchar() != '\n');
    	printf("Enter PIN: ");
	}
    
	// checks if the account number inputted by the user is a 4-digit number
	if (numberInput > 9999 || numberInput < 1000) {
		printf("Invalid input. Your PIN should consist of 4 digits only.\n");
		return pinChecker(index);
	}
	// converts the int input to string and stores 
	itoa(numberInput, pin, 10); // syntax: itoa(int value, char str, int base) 

    if (strcmp(pin, accounts[index].accountPin) != 0) {
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
	
    printf("\nEnter account number: ");
    // takes an integer account number input from the user to be checked 
    while (scanf("%d", &numberInput) != 1) {
    	printf("Invalid input. Try again.\n");
    	
    	while (getchar() != '\n');
    	return accountNoChecker();
	} 

	// checks if the account number inputted by the user is a 5-digit number
	if (numberInput > 99999 || numberInput < 10000) {
		printf("Invalid input. Your account number should consist of 5 digits only.\n");
		return accountNoChecker();
	}
	// converts the int input to string and stores 
	itoa(numberInput, accNo, 10); // syntax: itoa(int value, char str, int base) 

    for (int i = 0; i < MAX_ACC_DETAILS; i++) {
        if (strcmp(accounts[i].accountNumber, accNo) == 0) {
            found = 1;
            index = i;
            pinChecker(i);
        }
    }

    if (!found) {
        printf("Account Number not found. Try again.\n");
        return accountNoChecker();
    }

    return index;
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
    printf("[1] Do the transaction again\n");
    printf("[2] Exit the program\n\n");
    printf("Choice: ");
}