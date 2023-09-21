#include <stdio.h>

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

// main function
int main(int argc, const char * argv[])  {
	char ans; // variable for retrying the program
	int count = 1; // variable for monitoring the number of seats occupied
	
	// do while loop for looping the program until all seats are occupied
	// or until the user chooses to stop the program
	do {
		int rowNum; 
		char seatChar;

    	printf("---------------------------------------------------\n");
    	printf("\t\t  PASSENGER SEATS");
    	printf("\n---------------------------------------------------\n");

		// print the passenger seats
		for (int i = 0; i < 5; i++) {
			printf("\t\t\t\b\b\b%d %c %c %c %c", seats[i].row, seats[i].a, seats[i].b, seats[i].c, seats[i].d);
			printf("\n");
		}
    	printf("---------------------------------------------------\n");

		// getting the integer input from the user for seat location
    	A:
			printf("Input row number: ");
			while (scanf("%d", 
				&rowNum) != 1 || rowNum < 1 || rowNum > 5) {
				printf("[Error] Enter integer values only, between 1 and 5.\n");
		
				while (getchar() != '\n');
				printf("Input row number: ");
			}

		// getting the character input from the user for seat location
		printf("Input seat letter: ");
		scanf(" %c", 
			&seatChar);

		if (seatChar != 'A' && seatChar != 'B' && seatChar != 'C' && seatChar != 'D') {
			printf("[Error] Enter characters from A to D only.\n");
			goto A;
		}
		
		// printing the seat location chosen by the user
		printf("---------------------------------------------------\n");
		printf("\t    Your desired seat is at: %d%c\n", rowNum, seatChar);
		printf("---------------------------------------------------\n");
		
		// finding the seat location... marks the seat 'X' if the desired location is unoccupied
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
			for (int i = 0; i < 5; i++) {
            	printf("\t\t\t\b\b\b%d %c %c %c %c", seats[i].row, seats[i].a, seats[i].b, seats[i].c, seats[i].d);
				printf("\n");
        	}
    	} else {
        	printf("\t    Your seat is already taken.\n");
			printf("---------------------------------------------------\n");
        	goto A; // passes the program control back to user input if the desired location is already occupied
    	}

		// checking if all of the passenger seats are occupied
		if (count == 20) {
			printf("---------------------------------------------------\n");
			printf("\t    All seats are now occupied.\n");
            break;
		}
		
		printf("---------------------------------------------------\n");
		
		// program retry block
		loop:
			printf("Do you want to get another seat? \n[Y]\n[N]\nChoice: ");
			scanf(" %c", &ans);
	
			if (ans == 'Y' || ans == 'y') {
				count++; // adds 1 to variable 'count' each run of the program
				ans = 'Y';
			} else if (ans == 'N'|| ans == 'n') { 
				break;
			} else {
            	printf("Invalid input. Enter y or n keys only.\n");
            	goto loop;
        	}
    } while (ans == 'Y' || ans == 'y');
    
	printf("---------------------------------------------------\n");
    printf("Thank you for using the program!\n");
	printf("---------------------------------------------------\n");
    
	return 0;
}