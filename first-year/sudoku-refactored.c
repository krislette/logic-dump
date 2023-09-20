#include <stdio.h> 
#include <stdbool.h>

#define ROWS 3 // macro for the number of rows
#define COLS 3 // macro for the number of columns

int sudoku[3][3] = {}; // global variable for the sudoku table

// function for printing '='
void dividerDesign(int count) {
    for(int i = 0; i < count - 1; i++) {
        printf("=");
    }   

    printf("=\n");
}

// function for setting the array values to zero
void setZero() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            sudoku[i][j] = 0;
        }
    }
}

// function for checking the validity of the user's input
bool checkInput(int digit, int min, int max) {
    if (digit < min || digit > max) return false;
    else return true;
}

// function for checking if the user's digit input is unique
int checkSame(int digit) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (sudoku[i][j] == digit) return false;
        }
    }
    return true;
}

// function for getting the user's digit input
int getDigit(int min, int max) {
    int digitInput;

    scanf("%d", 
        &digitInput);

    bool isValid = checkInput(digitInput, min, max);

    if (!isValid) {
        printf("Invalid input. Enter numbers from %d-%d only.\n", min, max);
        while (getchar() != '\n');  
		digitInput = getDigit(min, max);
    }

    if (max == 2 || max == 3) return digitInput;
    else if (max == 9) {
        bool isUnique = checkSame(digitInput);

        if (!isUnique) {
            printf("Invalid input. Your digit must be different from your previous inputs.\n");
            while (getchar() != '\n');  
            digitInput = getDigit(min, max);
        }

        return digitInput;
    }
}

// function for checking if the user's row and column input is unique
bool checkRowCol(int digit, int row, int col) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (sudoku[row - 1][col - 1] != 0) {
                printf("Invalid input. There is an existing digit in this row and column combination.\n");
                return true;
            } 
        }
    }
    sudoku[row - 1][col - 1] = digit;

    return false;
}

// function for filling the remaining zeroes of the array with unique numbers from 1 to 9
void fillPuzzle(int first, int second, int third) {
    int fillerNum = 1;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (sudoku[i][j] == 0) {
                while (fillerNum == first || fillerNum == second || fillerNum == third) {
                    fillerNum++;
                }
                sudoku[i][j] = fillerNum++;
            }
        }
    }
}

// function for printing the solved sudoku table
void printPuzzle() {
    printf("\t\t\tHere is your solved Sudoku Table!\n");
    printf("\t\t\t\t\b+-----+-----+-----+\n");
    printf("\t\t\t\t\b|  %d  |  %d  |  %d  |\n", sudoku[0][0], sudoku[0][1], sudoku[0][2]);
    printf("\t\t\t\t\b+-----+-----+-----+\n");
    printf("\t\t\t\t\b|  %d  |  %d  |  %d  |\n", sudoku[1][0], sudoku[1][1], sudoku[1][2]);
    printf("\t\t\t\t\b+-----+-----+-----+\n");
    printf("\t\t\t\t\b|  %d  |  %d  |  %d  |\n", sudoku[2][0], sudoku[2][1], sudoku[2][2]);
    printf("\t\t\t\t\b+-----+-----+-----+\n");
    dividerDesign(80);
}

// main function
int main(int argc, const char * argv[]) {
    bool userConfirmation = true;
    
    while(userConfirmation) {
        printf("\n======================= WELCOME TO SUDOKU PUZZLE SOLVER ========================\n");
        printf("     Enter three different numbers with their corresponding row and column.\n");
        printf("\t\t\b\bYour desired number should range from 1 to 9 only.\n");
        printf("\t  The minimum row number is 1 and the maximum row number is 3.\n");
        dividerDesign(80);

        setZero(); // calls the function for setting the array values to zero

        // getting the first digit from the user
        int firstDigit, rowOne, colOne;
        bool isNotValid = true;

        while (isNotValid) {
            printf("First digit: ");
            firstDigit = getDigit(1, 9);

            printf("at row: ");
            rowOne = getDigit(1, 3);

            printf("at column: ");
            colOne = getDigit(1, 3);

            isNotValid = checkRowCol(firstDigit, rowOne, colOne);
        }
        dividerDesign(80);

        // getting the second digit from the user
        int secondDigit, rowTwo, colTwo;
        isNotValid = true;

        while (isNotValid) {
            printf("Second digit: ");
            secondDigit = getDigit(1, 9);
            
            printf("at row: ");
            rowTwo = getDigit(1, 3);

            printf("at column: ");
            colTwo = getDigit(1, 3);

            isNotValid = checkRowCol(secondDigit, rowTwo, colTwo);
        }
        dividerDesign(80);

        // getting the third digit from the user
        int thirdDigit, rowThree, colThree;
        isNotValid = true;

        while (isNotValid) {
            printf("Third digit: ");
            thirdDigit = getDigit(1, 9);

            printf("at row: ");
            rowThree = getDigit(1, 3);

            printf("at column: ");
            colThree = getDigit(1, 3);

            isNotValid = checkRowCol(thirdDigit, rowThree, colThree);
        }
        dividerDesign(80);

        fillPuzzle(firstDigit, secondDigit, thirdDigit); // function call for fillPuzzle()
        printPuzzle(); // function call for printPuzzle()

        printf("Are you sure you want to exit the program?\n\n[1] Yes\n[2] No\n\nChoice: ");
        int exitChoice = getDigit(1, 2);

        if (exitChoice == 1) userConfirmation = false;
        else userConfirmation = true;
    }
    printf("\nThank you for using my program!\n");

    return 0;
}