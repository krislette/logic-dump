#include <stdio.h>
#include <stdbool.h>

int count = 1; // variable for monitoring the number of seats occupied

// structure for the passenger seats
struct passengerSeat {
	int row;
	char a;
	char b;
	char c;
	char d;
};

// initializing the array of structures
struct passengerSeat seats[5] = {
	{1, 'A', 'B', 'C', 'D'}, 
	{2, 'A', 'B', 'C', 'D'}, 
	{3, 'A', 'B', 'C', 'D'},
	{4, 'A', 'B', 'C', 'D'}, 
	{5, 'A', 'B', 'C', 'D'}
};

void printSeats() {
	for (int i = 0; i < 5; i++) {
		printf("\t\t\t\b\b\b%d %c %c %c %c", seats[i].row, seats[i].a, seats[i].b, seats[i].c, seats[i].d);
		printf("\n");
	}
    printf("---------------------------------------------------\n");
}

// getting the integer input from the user for seat location
int getRow() {
	int rowNum;

	printf("Input row number: ");
	while (scanf("%d", 
		&rowNum) != 1 || rowNum < 1 || rowNum > 5) {
		printf("[Error] Enter integer values only, between 1 and 5.\n");
		
		while (getchar() != '\n');
		printf("Input row number: ");
	}

	return rowNum;
}

// getting the character input from the user for seat location
char getSeat() {
	char seatChar;

	printf("Input seat letter: ");
	scanf(" %c", 
		&seatChar);

	if (seatChar != 'A' && seatChar != 'B' && seatChar != 'C' && seatChar != 'D') {
		printf("[Error] Enter characters from A to D only.\n");
		return getSeat();
	}

	return seatChar;
}

// printing the passenger seat location
void printSeatLocation(int rowNum, char seatChar) {
	printf("---------------------------------------------------\n");
	printf("\t    Your desired seat is at: %d%c\n", rowNum, seatChar);
	printf("---------------------------------------------------\n");
}

// assigning the seat to the passenger
bool assignSeat(int rowNum, char seatChar) {
	int found = 0;

	for (int a = 0; a < 5; a++) {
		if (seats[a].row == rowNum) {
			if (seats[a].a == seatChar) {
				seats[a].a = 'X';
				found = 1;
				break;
			} else if (seats[a].b == seatChar) {
				seats[a].b = 'X';
				found = 1;
				break;
			} else if (seats[a].c == seatChar) {
				seats[a].c = 'X';
				found = 1;
				break;
			} else if (seats[a].d == seatChar) {
				seats[a].d = 'X';
				found = 1;
				break;
			}
		}
	}

	// printing the passenger seats after marking the empty seat with 'X'
	if (found) {
		printSeats();
		return true;
	} else {
		printf("\t    Your seat is already taken.\n");
		printf("---------------------------------------------------\n");
		return false;
	}
}

// checking if the user wants to get another seat
char checkUserAnswer(char userAnswer) {
	printf("Do you want to get another seat? \n[Y] Yes\n[N] No\nChoice: ");
	scanf(" %c", 
		&userAnswer);

	if (userAnswer != 'Y' && userAnswer != 'y' && userAnswer != 'N' && userAnswer != 'n') {
		printf("Invalid input. Enter y or n keys only.\n");
		while(getchar() != '\n');
		return checkUserAnswer(userAnswer);
	} else if (userAnswer == 'Y' || userAnswer == 'y') {
		count++;
	} 
	
	return userAnswer;
}

// main function 
int main(int argc, const char * argv[])  {
	char userAnswer; // variable for retrying the program
	
	// do while loop for looping the program until all seats are occupied
	// or until the user chooses to stop the program
	do {
    	printf("---------------------------------------------------\n");
    	printf("\t\t  PASSENGER SEATS");
    	printf("\n---------------------------------------------------\n");

		// printing the passenger seats
		printSeats();

		bool isOccupied = false;

		// do while loop for looping this block of code until the user inputs a valid seat
		while (!isOccupied) {
			int rowNum = getRow();
			char seatChar = getSeat();

			printSeatLocation(rowNum, seatChar);
			isOccupied = assignSeat(rowNum, seatChar);
		}

		// checking if all of the passenger seats are occupied
		if (count == 20) {
			printf("\t    All seats are now occupied.\n");
            break;
		}
		
		// program retry call
		userAnswer = checkUserAnswer(userAnswer);
    } while (userAnswer == 'Y' || userAnswer == 'y');
    
	printf("---------------------------------------------------\n");
    printf("Thank you for using the program!\n");
	printf("---------------------------------------------------\n");
    
	return 0;
}