#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERR 100
#define INTERVAL_ERR 101
#define ODD_ERR 102
#define FENCE_ERR 103

/*
    Declaration of functions
*/
int valide_inputs(int width, int height, int fence, int r1, int r2);
void print_roof(int width);
void print_house(int width, int height);
void print_house_with_fence(int width, int height, int fence);
void print_center_of_house_and_fence(int i, int last_col, int last_row, int width, int height, int fence);
void print_center_of_house(int i, int k);
void print_fence(int k, int i,int height, int fence);
void print_last_row_of_house(int width, int fence);
void print_x_row(int width);


/*
    The main program
*/
int main(int argc, char *argv[]) {
    int width, height, r1, r2, ret, fence;
    width = height = r1 = r2 = ret = fence = 0;

    /*
        Reading input
    */
    r1 = scanf("%d%d", &width, &height);

    /*
        If user entered 2 same odd numbers read input again
    */
    if(width == height) {
        r2 = scanf("%d", &fence);
    }

    /*
        Validate inputs, if there is an error, return number of that error, if not return 0
    */
    ret = valide_inputs(width, height, fence, r1, r2);

    /*
        If there is no error, execute these commands and print a house
    */
    if(ret == EXIT_SUCCESS) {
        print_roof(width);
        if(width == height) {
            print_house_with_fence(width, height, fence);
        }else {
            print_house(width, height);
        }
    }

    return ret;
}


/*
    Functions
*/
int valide_inputs(int width, int height, int fence, int r1, int r2) {
   if(r1 != 2) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return INPUT_ERR; 
    }

    if(width < 3 || width > 69 || height < 3 || height > 69) {
        fprintf(stderr, "Error: Vstup mimo interval!\n");
        return INTERVAL_ERR;
    }

    if(width % 2 == 0) {
        fprintf(stderr, "Error: Sirka neni liche cislo!\n");
        return ODD_ERR;
    }

    if(width == height) {
        if(r2 != 1) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            return INPUT_ERR; 
        }
        if(fence >= height || fence < 1) {
            fprintf(stderr, "Error: Neplatna velikost plotu!\n");
            return FENCE_ERR;
        }
    }

    return EXIT_SUCCESS;
}

void print_roof(int width) {
    int middle, increase_middle, decrease_middle;
    middle = increase_middle = decrease_middle = 0;

    /* Find horizontal middle of the house */
    middle = (width + 1) / 2;
    /* In increase and decrease variables is stored value, where should be X printed */
    increase_middle = middle;
    decrease_middle = middle;

    for(int i = 0; i < middle - 1; ++i) {
        for (int k = 1; k <= width - 1; ++k) {
            if(k == increase_middle || k == decrease_middle) {
                printf("%c", 'X');
            }else if(k < increase_middle) {
                printf(" ");
            }
        }
        printf("\n");
        increase_middle++;
        decrease_middle--;
    }
}

void print_house(int width, int height) {
    int last_row = height - 1;
    int last_col = width - 1;

    for (int i = 0; i < height; ++i) {
        if(i == 0 || i == last_row) {
            /* Print the first and the last row of the house */
            print_x_row(width);
        }else {
            /* Print middle of the house */
            for (int k = 0; k < width; ++k) {
                if(k == 0 || k == last_col) {
                    printf("%c", 'X');
                }else {
                    printf(" ");
                }
            } 
        }
        printf("\n");
    }
}

void print_house_with_fence(int width, int height, int fence) {
    int last_row = height - 1;
    int last_col= width - 1;

    for (int i = 0; i < height; ++i) {
        if(i == 0) {
            /* Print the first row of the house */
            print_x_row(width);
        }else if(i == last_row) {
            print_last_row_of_house(width, fence);
        }else {
            print_center_of_house_and_fence(i, last_col, last_row, width, height, fence);
        }
        printf("\n");
    } 
}

void print_center_of_house_and_fence(int i, int last_col, int last_row, int width, int height, int fence){
    for (int k = 0; k < (width + fence); ++k) {
        if(k == 0 || k == last_col) {
            /* Print the first and the last column of the house*/
            printf("%c", 'X');
        }else if(k > 0 && k < last_col){
            print_center_of_house(i, k);
        }else {
            if(i > last_row - fence) {
                print_fence(k, i, height, fence);

            }
        }
    }
}

void print_center_of_house(int i, int k) {
    /* Check if the row is even or odd */
    if(i % 2 == 0) {
        if(k % 2 == 0) {
            printf("%c", 'o'); 
        }else {
            printf("%c", '*'); 
        }
    }else {
        if(k % 2 == 0) {
            printf("%c", '*'); 
        }else {
            printf("%c", 'o'); 
        }
    }
}

void print_last_row_of_house(int width, int fence) {
    for (int k = 0; k < width + fence; ++k) {
        if(k >= width) {
            /* Print the last row of fence and check if with of the fence is even or odd */
            if(fence % 2 == 0) {
                if(k % 2 == 0) {
                    printf("%c", '|');
                }else {
                    printf("%c", '-');
                }
            }else {
                if(k % 2 == 0) {
                    printf("%c", '-');
                }else {
                    printf("%c", '|');
                }
            }
        }else {
            /* Print the last row of house */
            printf("%c", 'X');
        }
    }
}

void print_fence(int k, int i,int height, int fence) {
    /* Starting point where should fence start to print */
    int fence_upper_start = height - fence;

    /* Check if with of the fence is even or odd */
    if (fence % 2 == 0) {
        if(k % 2 == 0) {
            printf("%c", '|');
        }else {
            if(i == fence_upper_start) {
                printf("%c", '-');
            }else {
                printf(" ");
            }
        }
    }else {
        if(k % 2 == 0) {
            if (i == fence_upper_start) {
                printf("%c", '-');
            }else {
                printf(" ");
            }
        }else {
            printf("%c", '|');
        }
    }  
}

void print_x_row(int width) {
    for (int k = 0; k < width; ++k) {
        printf("%c", 'X');
    }
}
