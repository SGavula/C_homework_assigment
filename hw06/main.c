//Source of pseudocode for matrix multiplication - https://www.baeldung.com/cs/matrix-multiplication-algorithms - The Naive Matrix Multiplication Algorithm
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERR_TEXT "Error: Chybny vstup!\n"

//Error numbers
enum {
    ERR_INPUT = 100,
    ERR_MALLOC
};

//Declaration of functions
int** malloc_matrix(int rows, int cols);
void free_matrix(int** matrix, int rows);
void free_matrices(int rows1, int rows2, int rows3, int** matrix1, int** matrix2, int** matrix3);
int** loading_matrix(int* res, int* rows, int* cols, int** matrix);
int load_size_of_matrix(int* rows, int* cols);
int read_matrix(int rows, int cols, int** matrix);
int load_sign(char* sign);
int perform_counting_logic(char sign1, int rows1, int cols1, int rows2, int cols2, int** matrix1, int** matrix2);
int** perform_add_or_sub(int* res, char* sign1, char sign2, int rows1, int cols1, int* rows2, int* cols2, int rows3, int cols3, int** matrix1, int** matrix2, int** matrix3);
int** perform_multiplication_of_matrices(int* res, int* rows1, int* cols1, int rows2, int cols2, int* rows4, int* cols4, int** matrix1, int** matrix2, int** matrix4);
int** reload_matrices(int* rows2, int* cols2, int rows3, int cols3, int** matrix2, int** matrix3);
int last_operation_logic(char sign1, int rows1, int cols1, int rows2, int cols2, int rows3, int cols3, int** matrix1, int** matrix2, int** matrix3);
int perform_add_logic(int rows1, int cols1, int rows2, int cols2, int** matrix1, int** matrix2);
int perform_subtract_logic(int rows1, int cols1, int rows2, int cols2, int** matrix1, int** matrix2);
int check_size_of_matrices(int rows1, int cols1, int rows2, int cols2);
int perform_multiplication_logic(int rows1, int cols1, int rows2, int cols2, int rows3, int cols3, int** matrix1, int** matrix2, int** matrix3);
void add_matrices(int rows, int cols, int** matrix1, int** matrix2, int** matrix);
void subtract_matrices(int rows, int cols, int** matrix1, int** matrix2, int** matrix);
void multiply_matrices(int rows1, int rows2, int cols, int** matrix1, int** matrix2, int** matrix);
void rewrite_matrices(int rows, int cols, int** matrix1, int** matrix2);
void print_matrix(int rows, int cols, int** matrix);

/*
    MAIN
*/
int main(int argc, char* argv[]) {
    int res;
    int **matrix1, **matrix2;
    char sign1;
    int rows1, cols1, rows2, cols2;
    res = 0;
    matrix1 = matrix2 = NULL;
    rows1 = cols1 = rows2 = cols2 = 0;
    
    //Loading first matrix
    matrix1 = loading_matrix(&res, &rows1, &cols1, matrix1);
    if(res != 0) {
        free_matrix(matrix1, rows1);
        return res;
    }
    //First sign
    load_sign(&sign1);

    //Loading second matrix
    matrix2 = loading_matrix(&res, &rows2, &cols2, matrix2);
    if(res != 0) {
        free_matrix(matrix1, rows1);
        free_matrix(matrix2, rows2);
        return res;
    }

    res = perform_counting_logic(sign1, rows1, cols1, rows2, cols2, matrix1, matrix2);

    return res; 
}

int** malloc_matrix(int rows, int cols) {
    int** matrix = NULL;
    //Allocate memory for rows
    matrix = malloc(sizeof(int*) * rows);
    //Check if malloc was successful, if not handle free, if so return allocated memory
    if(matrix == NULL) {
        fprintf(stderr, "Error: Malloc\n");
        free(matrix);
        matrix = NULL;
        exit(ERR_MALLOC);
    }

    //Allocate memory for columns
    for(int i = 0; i < rows; i++) {
        matrix[i] = malloc(sizeof(int) * cols);
        //Check if malloc was successful, if not handle free, if so return allocated memory
        if(matrix[i] == NULL) {
            fprintf(stderr, "Error: Malloc\n");
            free(matrix);
            matrix = NULL;
            exit(ERR_MALLOC);
        }
    }

    return matrix;
}

void free_matrix(int** matrix, int rows) {
    //Handle free rows of matrix
    for(int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void free_matrices(int rows1, int rows2, int rows3, int** matrix1, int** matrix2, int** matrix3) {
    free_matrix(matrix1, rows1);
    free_matrix(matrix2, rows2);
    free_matrix(matrix3, rows3);
}

int** loading_matrix(int* res, int* rows, int* cols, int** matrix) {
    //Load size of matrix
    load_size_of_matrix(rows, cols);
    //Malloc space for matrix
    matrix = malloc_matrix(*rows, *cols); 
    //Read matrix and return if reading was successful or not
    *res = read_matrix(*rows, *cols, matrix);

    return matrix;
}

int load_size_of_matrix(int* rows, int* cols) {
    //Check if input contains two integers
    if(scanf("%d %d", rows, cols) != 2) {
        fprintf(stderr, ERR_TEXT);
        return ERR_INPUT;
    }
    return EXIT_SUCCESS;
}

int read_matrix(int rows, int cols, int** matrix) {
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            if(scanf("%d", &matrix[r][c]) != 1) {
                fprintf(stderr, ERR_TEXT);
                return ERR_INPUT;
            }
        }
    }

    return EXIT_SUCCESS;
}

int load_sign(char* sign) {
    //Enter contains character '\n' - it is temporary variable
    char enter;
    if(scanf("%c %c", &enter, sign) != 2) {
        return ERR_INPUT;
    }
    return EXIT_SUCCESS;
}

int perform_counting_logic(char sign1, int rows1, int cols1, int rows2, int cols2, int** matrix1, int** matrix2) {
    int res, rows3, cols3, rows4, cols4;
    int **matrix3, **matrix4;
    char sign2;
    res = rows3 = cols3 = rows4 = cols4 = 0;
    matrix3 = matrix4 = NULL;
    
    //Load next matrices until the end of the file
    while(true) {
        int r = load_sign(&sign2);
        //Check if sign2 can be loaded, if so load next matrix and perform the operations, if not perform last operation and break cycle
        if(r != EXIT_SUCCESS) {
            res = last_operation_logic(sign1, rows1, cols1, rows2, cols2, rows3, cols3, matrix1, matrix2, matrix3);
            break;
        }else {
            free_matrix(matrix3, rows3);
            //Loading next matrix
            rows3 = cols3 = 0;
            matrix3 = loading_matrix(&res, &rows3, &cols3, matrix3);
            //Check if loading was successful
            if(res != EXIT_SUCCESS) {
                break;
            }

            //Perform operations
            if(sign1 != '*' && sign2 != '*') {
                matrix2 = perform_add_or_sub(&res, &sign1, sign2, rows1, cols1, &rows2, &cols2, rows3, cols3, matrix1, matrix2, matrix3);
            }else if(sign2 == '*') {
                matrix2 = perform_multiplication_of_matrices(&res, &rows2, &cols2, rows3, cols3, &rows4, &cols4, matrix2, matrix3, matrix4);
            }else {
                matrix1 = perform_multiplication_of_matrices(&res, &rows1, &cols1, rows2, cols2, &rows4, &cols4, matrix1, matrix2, matrix4);
                matrix2 = reload_matrices(&rows2, &cols2, rows3, cols3, matrix2, matrix3);
                sign1 = sign2;
            }

            //Check if the operations went well
            if(res != EXIT_SUCCESS) {
                break;
            }
        }
    }

    free_matrices(rows1, rows2, rows3, matrix1, matrix2, matrix3);

    return res;
}

int** perform_add_or_sub(int* res, char* sign1, char sign2, int rows1, int cols1, int* rows2, int* cols2, int rows3, int cols3, int** matrix1, int** matrix2, int** matrix3) {
    //Check size of matrices, if we can add them or substract
    *res = check_size_of_matrices(rows1, cols1, *rows2, *cols2);
    if(*res == 0) {
        //Check the sign and decide which operation  will perform
        if(*sign1 == '+') {
            add_matrices(rows1, cols1, matrix1, matrix2, matrix1);
        }else {
            subtract_matrices(rows1, cols1, matrix1, matrix2, matrix1);
        }
        //Rewrite numbers from the matrix3 to the matrix2
        matrix2 = reload_matrices(rows2, cols2, rows3, cols3, matrix2, matrix3);
        //Rewrite sign1 for sign2
        *sign1 = sign2;
    }

    return matrix2;
}

int** perform_multiplication_of_matrices(int* res, int* rows1, int* cols1, int rows2, int cols2, int* rows4, int* cols4, int** matrix1, int** matrix2, int** matrix4) {
    //Check size of matrices, if we can multiply them
    if(rows2 != *cols1) {
        fprintf(stderr, ERR_TEXT);
       *res = ERR_INPUT;
    }
    //Prepare matrix4 for result of multiplication
    *rows4 = *rows1;
    *cols4 = cols2;
    matrix4 = malloc_matrix(*rows4, *cols4);
    //Multiply matrix1 by matrix2 and add the result to the matrix4
    multiply_matrices(*rows4, rows2, *cols4, matrix1, matrix2, matrix4);
    //Rewrite numbers from the matrix4 to the matrix1
    matrix1 = reload_matrices(rows1, cols1, *rows4, *cols4, matrix1, matrix4);
    free_matrix(matrix4, *rows4);
    return matrix1;
}

int** reload_matrices(int* rows1, int* cols1, int rows2, int cols2, int** matrix1, int** matrix2) {
    free_matrix(matrix1, *rows1);
    //Prepare matrix1 for rewriting
    *rows1 = rows2;
    *cols1 = cols2;
    matrix1 = malloc_matrix(*rows1, *cols1);
    //Rewrite numbers from the matrix2 to the matrix1
    rewrite_matrices(*rows1, *cols1, matrix1, matrix2);
    return matrix1;
}

int last_operation_logic(char sign1, int rows1, int cols1, int rows2, int cols2, int rows3, int cols3, int** matrix1, int** matrix2, int** matrix3) {
    int res = 0;
    //Find out operation and perform it
    switch(sign1){
        case '+':
            res = perform_add_logic(rows1, cols1, rows2, cols2, matrix1, matrix2);
            break;
        case '-':
            res = perform_subtract_logic(rows1, cols1, rows2, cols2, matrix1, matrix2);
            break;
        case '*':
            res = perform_multiplication_logic(rows1, cols1, rows2, cols2, rows3, cols3, matrix1, matrix2, matrix3);
            break;
    }

    return res;
}

int perform_add_logic(int rows1, int cols1, int rows2, int cols2, int** matrix1, int** matrix2) {
    int res;
    //Check if matrices have same size for addition
    res = check_size_of_matrices(rows1, cols1, rows2, cols2);
    if(res == 0) {
        add_matrices(rows1, cols1, matrix1, matrix2, matrix1);
        print_matrix(rows1, cols1, matrix1);
    }
    return res;
}

int perform_subtract_logic(int rows1, int cols1, int rows2, int cols2, int** matrix1, int** matrix2) {
    int res;
    //Check if matrices have same size for subtraction
    res = check_size_of_matrices(rows1, cols1, rows2, cols2);
    if(res == 0) {
        subtract_matrices(rows1, cols1, matrix1, matrix2, matrix1);
        print_matrix(rows1, cols1, matrix1);
    }
    return res;
}

int check_size_of_matrices(int rows1, int cols1, int rows2, int cols2) {
    if(rows1 != rows2 || cols1 != cols2) {
        fprintf(stderr, ERR_TEXT);
        return ERR_INPUT;
    }
    return EXIT_SUCCESS;
}

int perform_multiplication_logic(int rows1, int cols1, int rows2, int cols2, int rows3, int cols3, int** matrix1, int** matrix2, int** matrix3) {
    //Check size of matrices, if we can multiply them
    if(rows2 != cols1) {
        fprintf(stderr, ERR_TEXT);
        return ERR_INPUT;
    }
    //Prepare matrix3 for result of multiplication
    rows3 = rows1;
    cols3 = cols2;
    matrix3 = malloc_matrix(rows3, cols3);
    //Multiply matrix1 by matrix2 and add the result to matrix3
    multiply_matrices(rows3, rows2, cols3, matrix1, matrix2, matrix3);
    //Write the resulting matrix
    print_matrix(rows3, cols3, matrix3);
    free_matrix(matrix3, rows3);
    return EXIT_SUCCESS;
}

//Loop through matrix1 and matrix2 and add the corresponding numbers - write it to the matrix1
void add_matrices(int rows, int cols, int** matrix1, int** matrix2, int** matrix) {
    int r, c;
    for(r = 0; r < rows; r++) {
	    for(c = 0; c < cols; c++) {
		    matrix[r][c] = matrix1[r][c] + matrix2[r][c];
        }
    }
}

//Loop through matrix1 and matrix2 and calculate the difference between the corresponding numbers - write it to the matrix1
void subtract_matrices(int rows, int cols, int** matrix1, int** matrix2, int** matrix) {
    int r, c;
    for(r = 0; r < rows; r++) {
	    for(c = 0; c < cols; c++) {
		    matrix[r][c] = matrix1[r][c] - matrix2[r][c];
	    }
    }
}

void multiply_matrices(int rows1, int rows2, int cols, int** matrix1, int** matrix2, int** matrix) {
    int r1, c, r2;
    for(r1 = 0; r1 < rows1; r1++) {
	    for(c = 0; c < cols; c++) {
            matrix[r1][c] = 0;
            for(r2 = 0; r2 < rows2; r2++) {
                matrix[r1][c] += matrix1[r1][r2] * matrix2[r2][c];
            }
        }
    }
}

//Loop through matrices and rewrite every position of matrix2 to matrix1
void rewrite_matrices(int rows, int cols, int** matrix1, int** matrix2) {
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            matrix1[r][c] = matrix2[r][c];
        }
    }
}

void print_matrix(int rows, int cols, int** matrix) {
    bool first;
    //Print size of the resulting matrix
    printf("%i %i\n", rows, cols);

    //Print matrix
    for(int r = 0; r < rows; r++) {
        first = true;
        for(int c = 0; c < cols; c++) {
            //Check if it is the first cycle or not
            if(first == true) {
                //Print without space
                printf("%d", matrix[r][c]);
            }else {
                //Print with space
                printf(" %d", matrix[r][c]);
            }
            first = false;
        }
        printf("\n");
    }
}
