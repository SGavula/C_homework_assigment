#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define INPUT_ERR 100
#define N 1000000
#define PRIME_SUME 78498
#define FIRST_PRIME 2

//Declaration of functions
int validate_input(long int number, int r);
void do_eratos_sieve(int sieve_arr[]);
void add_all_prime_to_arr(int sieve_arr[], int prime_arr[], int *arr_index);
int load_and_handle_input(int prime_arr[]);
void calculate_prime_factorization(long int *number, int prime_arr[]);
void print_one_number(int *mul_of_div, int *divisor);
void print_numbers(int *mul_of_div, int *divisor);

/*
    The main program
*/
int main(int argc, char *argv[]) {
    int sieve_arr[N];
    int prime_arr[PRIME_SUME];
    int arr_index = 0;
    int result = 0;

    //Calculate sieve of eratosthenes and return array (0, 1) - 0 is composite number, 1 is prime number
    do_eratos_sieve(sieve_arr);

    //Add all prime numbers from sieve of eratosthenes to prime array 
    add_all_prime_to_arr(sieve_arr, prime_arr, &arr_index);

    //Load and handle input and calculate prime factorization
    result = load_and_handle_input(prime_arr);

    return result;
}

//Functions
int validate_input(long int number, int r) {    
    if(number < 0 || r != 1) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return INPUT_ERR;
    }

    return EXIT_SUCCESS;
}

void do_eratos_sieve(int sieve_arr[]) {
    //Remove numbers 0 and 1 from sieve of eratosthenes
    sieve_arr[0] = 0;
    sieve_arr[1] = 0;

    //
    for(int i = FIRST_PRIME; i < N; i++) {
        sieve_arr[i] = 1;
    }

    //Cycle all numbers starting with 2 until square root of N
    for(int i = FIRST_PRIME; i < sqrt(N); i++) {
        //take prime number
        if(sieve_arr[i] != 0) {
            //remove multiples of that prime number from sieve
            for(int k = i * FIRST_PRIME; k < N; k = k + i) {
                if(sieve_arr[k] != 0) {
                    sieve_arr[k] = 0;
                }
            }
        }
    }
}

void add_all_prime_to_arr(int sieve_arr[], int prime_arr[], int *arr_index) {
    //Cycle sieve of eratosthenes and if value of number is 1, add this number to prime numbers array
    for(int i = 0; i < N; i++) {
        if(sieve_arr[i] == 1) {
            prime_arr[*arr_index] = i;
            *arr_index = *arr_index + 1;
        }
    }
};

int load_and_handle_input(int prime_arr[]) {
    long int number = 0;
    int ret = 0;

    while(true) {
        int r = 0;
        r = scanf("%ld", &number);
        //Validate input
        ret = validate_input(number, r);

        if(ret != EXIT_SUCCESS || number == 0) {
            break;
        }else if(number == 1) {
            printf("Prvociselny rozklad cisla 1 je:\n1\n");
        }else {
            calculate_prime_factorization(&number, prime_arr);
        }
        
    }

    return ret;
};

void calculate_prime_factorization(long int *number, int prime_arr[]) {
    //Add first prime number to variable
    int divisor = prime_arr[0];
    int mul_of_div = 0;
    bool is_divided_by = false;
    int pos = 0;

    printf("Prvociselny rozklad cisla %ld je:\n", *number);
    //Divide number by prime number in cycle until this number is 1
    while(*number >= 1) {
        //printf("Number %ld je:\n", *number);
        //Check if the number is divisible by a prime number
        if(*number % divisor == 0) {
            is_divided_by = true;
            mul_of_div++;
            *number = *number / divisor;
        }else if(*number == 1) {
            //If number is 1 print last number in prime factorization and terminate the cycle
            print_one_number(&mul_of_div, &divisor);
            break;
        }else {
            //If the number is divided by the prime number print prime number
            if(is_divided_by == true) {
                print_numbers(&mul_of_div, &divisor);
                is_divided_by = false;
            }
            //Go to next prime number in prime numbers array
            pos = pos + 1;
            divisor = prime_arr[pos];
            mul_of_div = 0;
        }
    }
}

void print_one_number(int *mul_of_div, int *divisor) {
    if(*mul_of_div > 1) {
        printf("%d^%d\n", *divisor, *mul_of_div);
    }else {
        printf("%d\n", *divisor);
    }
}

void print_numbers(int *mul_of_div, int *divisor) {
    if(*mul_of_div > 1) {
        printf("%d^%d x ", *divisor, *mul_of_div);
    }else {
        printf("%d x ", *divisor);
    }
}

