#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DIGITS 100
#define FIRST_PRIME 2
#define INPUT_ERR 100
#define GREATEST_POSSIBLE_DIVISOR 1000000

//Declarations of functions
bool validate_number(int* integer_num, int len);
int* convert(char* c, int len);
void do_logic(int* integer_num, int len);
void compute_prime_fact(int* integer_num, int len);
bool check_is_divided(int* integer_num, int divider, int len);
int divide_num(int* integer_num, int divider, int len);
void print_introductory_sentence(int* integer_num, int len);
void print_num(int power, bool* is_first, int divider);

/*
  MAIN
*/
int main(int argc, char* argv[]) {
  char input_num[MAX_DIGITS];
  int* integer_num = NULL;
  int len, r;
  len = r = 0;

  while(true) {
    r = scanf("%s", input_num);
    if(r != 1) {
      fprintf(stderr, "Error: Chybny vstup!\n");
      exit(INPUT_ERR);
    }

    len = strlen(input_num);
    integer_num = convert(input_num, len);
    bool is_ok = validate_number(integer_num, len);
    if(integer_num[0] == 0 && len == 1) {
      //Terminate loop
      free(integer_num);
      break;
    }else if(is_ok == true) {
      //Correct input
      do_logic(integer_num, len);
    }else {
      //Incorrect input
      free(integer_num);
      fprintf(stderr, "Error: Chybny vstup!\n");
      exit(INPUT_ERR);
    }
  }
  return 0;
}

//Definitions of functions
//Checks if it is a number i.e. if it contains only digits from 0 to 9
bool validate_number(int* integer_num, int len) {
  bool is_ok = true;
  for(int i = 0; i < len; i++) {
    if(integer_num[i] < 0 || integer_num[i] > 9) {
      is_ok = false;
      break;      
    }
  }
  return is_ok;
}

//https://snipplr.com/view/79201/convert-string-to-integer-array
//Converts an array of character digits to an array of integer digits and returns this new array
int* convert(char* c, int len) {
	int *a = malloc(sizeof(int) * len);
	for(int i = 0 ; i < len; i++) {
		a[i] = c[i] - 48;
  }

	return a;
}

void do_logic(int* integer_num, int len) {
  //Check if number from input is 1 or not
  if(integer_num[0] == 1 && len == 1) {
    printf("Prvociselny rozklad cisla 1 je:\n1\n");
  }else {
    //if number from input is greater than 1, perform the decomposition into primes
    print_introductory_sentence(integer_num, len);
    compute_prime_fact(integer_num, len);
  }
  free(integer_num);
}

//Computes the prime factors of the input number and prints them out.
void compute_prime_fact(int* integer_num, int len) {
  int new_len = len;
  int divider = FIRST_PRIME;
  int power = 0;
  bool is_divided;
  bool is_first = true;

  while(true) {
    //End of the loop
    if(divider >= GREATEST_POSSIBLE_DIVISOR) {
      break;
    }
    is_divided = check_is_divided(integer_num, divider, new_len);
    if(is_divided == true) {
      power++;
      //Perform division
      new_len = divide_num(integer_num, divider, new_len);
      //End loop if the input number is reduced to 1
      if(integer_num[0] == 1 && new_len == 1) {
        break;
      }
    }else {
      //Print the devider its power
      print_num(power, &is_first, divider);
      power = 0;
      divider++;
    }
  }
  //Print last number
  print_num(power, &is_first, divider);
  printf("\n");
}

//Checks if the input number is divisible by a given divider
bool check_is_divided(int* integer_num, int divider, int len) {
  int idx = 0;
  int digit = 0;
  bool result = false;
  //First number in an array number
  digit = integer_num[idx];
  
  while(true) {
    //If digit is greater than or equal to divider compute the the remainder
    if(digit >= divider) {
      digit = digit % divider;
    }
    digit = digit * 10;
    idx++;
    //End of loop
    if(idx >= len) {
      if(digit == 0) {
        //If digit is 0 i.e. there is no remainder - the number is divisible return true
        result = true;
      }
      break;
    }
    //Take next digit
    digit = digit + integer_num[idx];
  }
  return result;
}

int divide_num(int* integer_num, int divider, int len) {
  int digit = 0;
  int new_len = 0;
  int idx = 0;
  int tmp_calculation = 0;
  
  //First number in an array number
  digit = integer_num[idx];
  //Check if digit is smaller than divider, if so we must take next digit from the input number
  if(digit < divider) {
    digit = digit * 10;
    idx++;
    digit = digit + integer_num[idx];
  }

  while(true) {
    //Divide the digit by the divisor and store it on the new index
    tmp_calculation = digit / divider;
    integer_num[new_len] = tmp_calculation;
    new_len++;
    //Compute the the remainder
    digit = digit % divider;
    digit = digit * 10;
    idx++;
    //End of loop
    if(idx >= len) {
      break;
    }
    //Take next digit
    digit = digit + integer_num[idx];
  }
  return new_len;
}

void print_introductory_sentence(int* integer_num, int len) {
  printf("Prvociselny rozklad cisla ");
  for(int i = 0; i < len; i++) {
    printf("%i", integer_num[i]);
  }
  printf(" je:\n");
}

//Prints the prime factor and its power.
void print_num(int power, bool* is_first, int divider) {
  if(power != 0) {
    if(*is_first == true) {
      //Print first number without x character
      printf("%i", divider);
      if(power != 1) {
        printf("^%i", power);
      }
      *is_first = false;
    }else {
      //Print number with x character
      printf(" x %i", divider);
      if(power != 1) {
        printf("^%i", power);
      }
    }
  }
}
