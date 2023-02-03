#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INPUT_ERR 100
#define MAX_INTERVAL 10000
#define MIN_INTERVAL -10000

/*
    Declaration of functions
*/
void sum_numbers(int *sum, int number);
void divide_to_pos_and_neg(int *pos_num, int *neg_num, int number);
void divide_to_even_and_odd(int *even_num, int *odd_num, int number);
void calculate_max(int *max_num, int number, bool first_cycle);
void calculate_min(int *min_num, int number, bool first_cycle);
float calculate_percentage(int numbers, int number_of_numbers);
void calculate_average(float *average, int sum, int numbers);
void print_numbers(int number, bool first_cycle);
void print_results(
    int numbers,
    int pos_num,
    int neg_num,
    float percentage_of_positive,
    float percentage_of_negative,
    int even_num,
    int odd_num,
    float percentage_of_even,
    float percentage_of_odd,
    float average,
    int max_num,
    int min_num
);


/* The main program */
int main(int argc, char *argv[])
{
    /*
        Initialization of variables
    */
    int number, sum, numbers, neg_num, pos_num, even_num, odd_num, max_num, min_num;
    number = sum = numbers = neg_num = pos_num = even_num = odd_num = max_num = min_num = 0;

    float percentage_of_positive, percentage_of_negative, percentage_of_even, percentage_of_odd, average;
    percentage_of_positive = percentage_of_negative = percentage_of_even = percentage_of_odd = average = 0;
    
    bool first_cycle = true;
    
    /*
        Read input
    */
    while(scanf("%i", &number) == 1) {
        /*
            Check if the number is in a valid interval
            If so, do the calculation
            If not, return the error
        */
        if(number >= MIN_INTERVAL && number <= MAX_INTERVAL) {
            numbers++;
            print_numbers(number, first_cycle);
            sum_numbers(&sum, number);
            divide_to_pos_and_neg(&pos_num, &neg_num, number);
            divide_to_even_and_odd(&even_num, &odd_num, number);
            calculate_max(&max_num, number, first_cycle);
            calculate_min(&min_num, number, first_cycle);
            first_cycle = false;
        }else {
            printf("\n");
            printf("Error: Vstup je mimo interval!\n");
            return INPUT_ERR;
        }

    }
    /*
        Calculate percentage of positive and negative numbers
    */
    percentage_of_positive = calculate_percentage(pos_num, numbers);
    percentage_of_negative = calculate_percentage(neg_num, numbers);
    /*
        Calculate percentage of even and odd numbers
    */
    percentage_of_even = calculate_percentage(even_num, numbers);
    percentage_of_odd = calculate_percentage(odd_num, numbers);
    /*
        Calculate average
    */
    calculate_average(&average, sum, numbers);
    /*
        Print all values
    */
    print_results(
        numbers,
        pos_num,
        neg_num,
        percentage_of_positive,
        percentage_of_negative,
        even_num,
        odd_num,
        percentage_of_even,
        percentage_of_odd,
        average,
        max_num,
        min_num
    );

    return EXIT_SUCCESS;
}

/*
    Functions
*/
void sum_numbers(int *sum, int number) {
    *sum = *sum + number;
}

void divide_to_pos_and_neg(int *pos_num, int *neg_num, int number) {
    if(number > 0) {
        *pos_num = *pos_num + 1;
    }else if(number < 0) {
        *neg_num = *neg_num + 1;
    }
}

void divide_to_even_and_odd(int *even_num, int *odd_num, int number) {
    if(number % 2 == 0) {
        *even_num = *even_num + 1;
    }else {
        *odd_num = *odd_num + 1;
    }
}

void calculate_max(int *max_num, int number, bool first_cycle) {
    if(first_cycle == true) {
         *max_num = number;
    }else {
        if(*max_num < number) {
            *max_num = number;
        }
    }
}

void calculate_min(int *min_num, int number, bool first_cycle) {
    if(first_cycle == true) {
         *min_num = number;
    }else {
        if(*min_num > number) {
            *min_num = number;
        }
    }
}


float calculate_percentage(int num_for_per, int numbers) {
    return num_for_per / (float)numbers * 100;
}

void calculate_average(float *average, int sum, int numbers) {
    *average = sum / (float)numbers;
}

void print_numbers(int number, bool first_cycle) {
    if(first_cycle == true) {
        printf("%i", number);
    }else {
        printf(", %i", number);
    }
}

void print_results(
    int numbers,
    int pos_num,
    int neg_num,
    float percentage_of_positive,
    float percentage_of_negative,
    int even_num,
    int odd_num,
    float percentage_of_even,
    float percentage_of_odd,
    float average,
    int max_num,
    int min_num
) {
    printf("\n");
    printf("Pocet cisel: %i\n", numbers);
    printf("Pocet kladnych: %i\n", pos_num);
    printf("Pocet zapornych: %i\n", neg_num);
    printf("Procento kladnych: %.2f\n", percentage_of_positive);
    printf("Procento zapornych: %.2f\n", percentage_of_negative);
    printf("Pocet sudych: %i\n", even_num);
    printf("Pocet lichych: %i\n", odd_num);
    printf("Procento sudych: %.2f\n", percentage_of_even);
    printf("Procento lichych: %.2f\n", percentage_of_odd);
    printf("Prumer: %.2f\n", average);
    printf("Maximum: %i\n", max_num);
    printf("Minimum: %i\n", min_num);
}
