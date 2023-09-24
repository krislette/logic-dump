#include <stdio.h>
#include <stdlib.h>

// inner structure 1
struct fullName {
  char fName[80];
  char mName[80];
  char sName[80];
};

// inner structure 2
struct address {
    char city[80];
    char barangay[80];
};

// outer/main structure
struct student {
    struct fullName name; // 1
    struct address add; // 2
    int age;
    float allowance;
};

// function for printing the divider line
void divider(int count, char sign) {
    for (int i = 0; i < count - 1; i++) {
        printf("=");
    }   
    printf("%c\n", sign);
}

// declaring the pointer variable... data type: struct student
struct student *stud;

int main() {
	char answer; 
	
	do {
    	float aveAllowance = 0; // variable for average allowance
    
    	// allocating memory for size of 3 students
    	stud = (struct student*)malloc(3 * sizeof(struct student));
    
    	// instructions
    	printf("------------------------------------------------------\n");
    	printf("\t\t    STUDENT RECORD\n");
    	printf("------------------------------------------------------\n");
    	printf("  Enter your full name, address, age, and allowance.\n");
    	printf("------------------------------------------------------\n\n");

    	// for loop for getting the user input
    	// syntax for scanf:  &((stud + i)->age)
    	// no & for string scanf
    	for (int i = 0; i < 3; i++) {
        	divider(54, '=');
        	printf("\t\t\t\b\b\b[STUDENT %d]\n\n", i + 1);
        	printf("Enter First Name: ");
        	scanf("%[^\n]%*c",
            	((stud + i)->name.fName));
        	printf("Enter Middle Name: ");
        	scanf("%[^\n]%*c", 
            	((stud + i)->name.mName));
        	printf("Enter Surname: ");
        	scanf("%[^\n]%*c", 
            	((stud + i)->name.sName));
        	divider(54, '-');
        	printf("Enter Barangay Name: ");
        	scanf("%[^\n]%*c", 
            	((stud + i)->add.barangay));
        	printf("Enter City Name: ");
        	scanf("%[^\n]%*c", 
            	((stud + i)->add.city));
        	divider(54, '-');
        	printf("Enter Age: ");
        	scanf("%d", 
            	&((stud + i)->age));
        	divider(54, '-');
        	printf("Enter Allowance: ");
        	scanf("%f",
            	&((stud + i)->allowance));

        	aveAllowance += (stud + i)->allowance;
        
        	// used to clear the input buffer
        	// for the next iteration of the for loop
        	char c;
        	while ((c = getchar()) != '\n' && c != EOF);
    	}
    	divider(54, '=');

    	// printing the output
    	printf("\nHere is the record of the students:\n\n");
    	printf("+--------+-----------------------------------------------------------+----------------------------------------+-----+-----------+\n");
    	printf("| Number | Name                                                      | Address                                | Age | Allowance |\n");
    	printf("+--------+-----------------------------------------------------------+----------------------------------------+-----+-----------+\n");
    
    	// for loop for printing the values/strings inputted in a table format
    	// syntax for printf: (stud + i)->allowance
    	for (int i = 0; i < 3; i++) {
        	printf("| %-6d | %-18s  %-18s %-18s | %-18s  %-18s | %-3d | %-9.2f |\n", i + 1,
            	(stud + i)->name.fName, (stud + i)->name.mName, (stud + i)->name.sName,
            	(stud + i)->add.barangay, (stud + i)->add.city, (stud + i)->age, (stud + i)->allowance);
        	printf("+--------+-----------------------------------------------------------+----------------------------------------+-----+-----------+\n");
    	}	
    
    	// prints the average allowance
    	printf("\nThe average allowance of the students is: %0.2f\n", aveAllowance / 3);
    	
    	// try again prompt
		printf("\nDo you want to try the program again?\n[Y] Yes\n[N] No\n");
		
		A:
			printf("Choice: ");
			scanf(" %c",
				&answer);
			
			// condition to check if the input is y or n
			if (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n') {
				printf("invalid input. Enter y/n keys only.\n");
				goto A;
			}
		
		// clears the buffer if ever the user decides to use the program again
		char c;
        while ((c = getchar()) != '\n' && c != EOF);
	} while (answer == 'Y' || answer == 'y');
	
	printf("\nThank you for using the program!\n");

    return 0;
}
