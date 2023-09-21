#include <stdio.h>

int evenIndex = 0; // index and size tracker of even numbers
int oddIndex = 0; // index and size tracker of odd numbers

// function for placing odd and even numbers into their respective arrays
void oddEven(int numArray[], int arraySize, int evenArray[], int oddArray[]) {
    for(int i = 0; i < arraySize; i++) {
        if(numArray[i] % 2 == 0) {
            evenArray[evenIndex] = numArray[i];
            evenIndex++;
        } else {
            oddArray[oddIndex] = numArray[i];
            oddIndex++;
        }
    }
}

// function for printing odd numbers
void printOdd(int oddArray[]) {
    printf("Odd Numbers: ");
    for(int i = 0; i < oddIndex; i++) {
        printf("%d ", oddArray[i]);
    }
}

// function for printing even numbers
void printEven(int evenArray[]) {
    printf("\nEven Numbers: ");
    for(int i = 0; i < evenIndex; i++) {
        printf("%d ", evenArray[i]);
    }
}

int main(int argc, const char * argv[]) {
    int numberCollection[] = {33, 2, 70, 4, 52, 42, 8, 35, 9, 211}; 
    int numberCollectionSize = sizeof(numberCollection) / sizeof(numberCollection[0]); // calculates the size of the array

    int evenNumbers[numberCollectionSize]; // array for storing even numbers
    int oddNumbers[numberCollectionSize]; // array for strong odd numbers
    
    // calling the function for sorting the elements of the array
    oddEven(numberCollection, numberCollectionSize, evenNumbers, oddNumbers);
    // calling the function for printing odd numbers
    printOdd(oddNumbers);
    // calling the function for printing even numbers
    printEven(evenNumbers);

    return 0;
}