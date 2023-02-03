#include <stdio.h>

int main() {
    int input1, input2;
    int sum, sub, mul, div;
    float average;

    int r = scanf("%i%i", &input1, &input2);

    //Check if user's input is in the interval, if not print error
    if(input1 > 10000 || input1 < -10000 || input2 > 10000 || input2 < -10000) {
        fprintf(stderr, "Error: Vstup je mimo interval!\n");
        return 100;
    }

    //Check if user's input is not empty
    if(r != 0) {
        sum = input1 + input2;
        sub = input1 - input2;
        mul = input1 * input2;
        if(input2 != 0) {
            div = input1 / input2;
        }
        average = sum / 2.0;

        printf("Desitkova soustava: %d %d\n", input1, input2);
        printf("Sestnactkova soustava: %x %x\n", input1, input2);
        printf("Soucet: %d + %d = %d\n", input1, input2, sum);
        printf("Rozdil: %d - %d = %d\n", input1, input2, sub);
        printf("Soucin: %d * %d = %d\n", input1, input2, mul);
        if(input2 != 0) {
            printf("Podil: %d / %d = %d\n", input1, input2, div);
        }else {
            printf("Podil: %d / %d = %s\n", input1, input2, "NaN");
            fprintf(stderr, "Error: Nedefinovany vysledek!\n");
        }
        printf("Prumer: %.1f\n", average);
    }

    if(input2 == 0) {
        return 101;
    }

    return 0;
}