#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Nag-set ta nga ang array adunay 10 ka elements.
#define SIZE 10
//Ipakita ang sulod sa array.
void displayArray(int arr[]) {

    int i;

    printf("[ ");
//Mag-loop gikan 0 hangtod 9 aron ma-print tanan numbers.
    for(i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }

    printf("]\n");
}

void generateRandomArray(int arr[]) {

    int i;
//Maghimo og random numbers gikan 1 to 100.
    for(i = 0; i < SIZE; i++) {
        arr[i] = (rand() % 100) + 1;
    }
}
//Mao ni ang sorting algorithm.Gigamit diri kay Bubble Sort.
void customSort(int arr[],
                int *comparisons,
                int *assignments,
                int *swaps) {

    int i, j, temp;
    int step = 1;

    for(i = 0; i < SIZE - 1; i++) {

        for(j = 0; j < SIZE - i - 1; j++) {

            /* Mo-stop ang display kung nakaabot na og 10 steps */
            if(step > 10) {
                return;
            }
			// compare sa duha ka numbers.
            (*comparisons)++;

            printf("Step %d: Comparing %d and %d",
                   step,
                   arr[j],
                   arr[j + 1]);

           //Kung ang wala nga number mas dako kaysa tuo:mag-ilis sila.
		    if(arr[j] > arr[j + 1]) {

                printf(",  swapping...\n");
				//Matag assign kay counted.
                temp = arr[j];
                (*assignments)++;

                arr[j] = arr[j + 1];
                (*assignments)++;

                arr[j + 1] = temp;
                (*assignments)++;
				//exchange sa duha ka numbers.
                (*swaps)++;

            } else {

                printf(", Correct \n");
            }

            printf("Current: ");
            displayArray(arr);
            printf("\n");

            step++;
        }
    }
}

int main() {

    int numbers[SIZE];

    int comparisons = 0;
    int assignments = 0;
    int swaps = 0;
//Aron lain-lain ang random numbers kada run sa program.
    srand(time(NULL));
//Maghimo og random array.
    generateRandomArray(numbers);

    printf("=== CUSTOM SORTING ANALYSIS ===\n\n");
//Ipakita ang original array before sorting.
    printf("Initial Array: ");
    displayArray(numbers);

    printf("\n--- SORTING PROGRESS ---\n\n");
//gamit ang address operator (&) aron mausab ang values sulod sa function.
    customSort(numbers,
               &comparisons,
               &assignments,
               &swaps);

    printf("=== OPERATION STATISTICS ===\n");
    printf("Comparisons: %d\n", comparisons);
    printf("Assignments: %d\n", assignments);
    printf("Swaps: %d\n", swaps);
    printf("Total Operations: %d\n",
           comparisons + assignments + swaps);

    return 0;
}
