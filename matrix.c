#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double** initialize(int row, int col) {
    double** arr = calloc(row, sizeof(double*));
    for (int i = 0; i < row; i++) {
        arr[i] = calloc(col, sizeof(double));
    }
    return arr;
}

void freeMatrix(double **arr, int num) {
    for (int i = 0; i < num; i++) {
        free(arr[i]);
    }
    free(arr);
}

void printMatrix(double **arr, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%.2lf\t", arr[i][j]);
        }
        printf("\n");
    }
}

double** matrixMultiplication(double **arr1, double **arr2, int row1, int col1, int row2, int col2) {
    if (col1 != row2) {
        return NULL; 
    }

    double **matrix = initialize(row1, col2);
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            for (int k = 0; k < col1; k++) {
                matrix[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
    return matrix;
}

int det(int n, double **arr) {
    int detResult = 0;
    int sign = 1;
    double **smallArr = initialize(n - 1, n - 1);
    if (n == 1) {
        freeMatrix(smallArr, n - 1);
        return arr[0][0];
    }
    if (n == 2) {
        freeMatrix(smallArr, n - 1);
        return (arr[0][0] * arr[1][1]) - (arr[1][0] * arr[0][1]);
    }
    else {
        for (int a = 0; a < n; a++) {
            int y = 0, x = 0;
            for (int i = 1; i < n; i ++) {
                for (int j = 0; j < n; j++) {
                    if (j != a) {
                        smallArr[y][x] = arr[i][j];
                        x++;
                    }
                }
                y++;
                x = 0;
            }
            detResult += sign * (arr[0][a] * det(n-1, smallArr));
            sign = sign * -1;
        }
    }
    freeMatrix(smallArr, n-1);
    return detResult;
}

int main(int argc, char* argv[argc + 1]) {

    int row, col;
    int status = 0;
    int s;
    while (status < 1){
        printf("Enter the number of rows of your matrix:\n");
        scanf("%d", &row);
        printf("Enter the number of columns of your matrix:\n");
        scanf("%d", &col);
        double **matrix = initialize(row, col);
        printf("Enter your matrix entries, one at a time:\n");
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                scanf("%lf", &matrix[r][c]);
            }
        }
        printMatrix(matrix, row, col);
        printf("This is your matrix. Enter 1 to calculate the determinant, or 2 to multiply it with another matrix. If you would like to input a new matrix, enter 0:\n");
        int result;
        scanf("%d", &result);
        if (result > 2 || result < 0) {
            printf("ERROR, input is invalid. Input must be 0, 1, or 2. Try again.\n");
        } else if (result == 0) {
            printf("Re-enter your matrix.\n");
        } else if (result == 1) {
            if (row == col) {
                int determinant = det(row, matrix);
                printf("The determinant of the matrix is %d\n", determinant);
            } else {
                printf("ERROR, determinants can only be calculated for a square matrix.\n");
            }       
        } else {
            int row1, col1;
            printf("Enter the number of rows of your second matrix:\n");
            scanf("%d", &row1);
            printf("Enter the number of columns of your second matrix:\n");
            scanf("%d", &col1);
            double **arr = initialize(row1, col1);
            printf("Enter your second matrix entries, one at a time:\n");
            for (int r = 0; r < row1; r++) {
                for (int c = 0; c < col1; c++) {
                    scanf("%lf", &arr[r][c]);
                }
            }
            if (col != row1) {
                printf("Matrices cannot be multiplied, as dimensions are not compatible.\n");
                freeMatrix(arr, row1);
            } else {
                double **result = matrixMultiplication(matrix, arr, row, col, row1, col1);
                printMatrix(result, row, col1);
                freeMatrix(result, row);
                freeMatrix(arr, row1);
            }
        }
        printf("If you would like to find the product between two other matrices, or find a new determinant, enter 0. If not, enter 1:\n");
        scanf("%d", &s);
        if (s == 1) {
            status++;
        }
        freeMatrix(matrix, row);
    }

    printf("Thank you for using this program!\n");
    return EXIT_SUCCESS;
}
