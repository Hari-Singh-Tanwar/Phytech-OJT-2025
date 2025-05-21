#include <stdio.h>

// Function to calculate the factorial of a number
unsigned long long factorial(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}


unsigned long long binomialCoefficient(int n, int k) {
    if (k < 0 || k > n) {
        return 0; // Invalid input
    }
    if (k == 0 || k == n) {
        return 1; // Base case
    }
    if (k > n / 2) {
        k = n - k; // Optimization: nCr = nC(n-r)
    }
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int main() {
    int n; // Number of rows in Pascal's Triangle
    printf("Enter the number of rows: ");
    scanf("%d", &n);

    // Print Pascal's Triangle
    for (int i = 0; i < n; i++) {
        // Print leading spaces for alignment
        for (int space = 0; space < n - i; space++) {
            printf(" ");
        }

        // Print numbers in the current row
        for (int j = 0; j <= i; j++) {
            printf("%llu ", binomialCoefficient(i, j)); // Use binomialCoefficient to get the values
        }
        printf("\n"); // Move to the next line
    }

    return 0;
}