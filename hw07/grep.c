#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

//Constants
#define INIT_SIZE 10
#define FILE_CLOSE_ERR -1

//Errors
enum {
    INPUT_ERR = 100,
    ALLOC_ERR,
    FILE_ERR,
};

typedef struct {
    char* msg;
    char* file_name;
    int *line;
    int* value_arr;
    int length;
    int line_size;
    int value_arr_size;
    int value_arr_row;
    int compared_text_ind;
    bool is_in_row;
    bool is_empty;
    bool is_color;
    bool is_stdin;
} t_my_struct;

//Declarations of functions
int compare(char a[],char b[]);
void load_instructions(t_my_struct* s1, int argc, char* argv[]);
void find_the_length(t_my_struct* s1);
int* my_malloc(int size);
int* my_realloc(int* size, int* arr);
void main_logic(FILE* f, t_my_struct* s1);
void find_word_in_text(t_my_struct* s1, char compared_text[], int idx, char letter);
void print_result(t_my_struct* s1, int idx);
void reset_values(t_my_struct* s1);
void print_line(int* line, int idx);
void close_file(FILE* f, t_my_struct s1);

/*
    MAIN
*/
int main(int argc, char* argv[]) {
    int res = 0;
    t_my_struct s1;
    s1.is_empty = true;
    s1.is_in_row = false;

    //Load instructions from standart input
    load_instructions(&s1, argc, argv);

    //Length of searching word
    find_the_length(&s1);

    //Declaration of file
    FILE *f;
    if(s1.is_stdin != true) {
        f = fopen(s1.file_name, "r");
        if(f == NULL) {
            fprintf(stderr, "Error: Cannot open the file\n");
            return FILE_ERR;
        }
    }

    main_logic(f, &s1);

    if(s1.is_stdin != true) {
        close_file(f, s1);
    }

    free(s1.line);
    free(s1.value_arr);
    
    //TODO: toto prerobit
    if(s1.is_empty == true) {
        res = 1;
    }
    
    return res;
}

//Definitions of functions
int compare(char a[],char b[]) {  
    int flag=0,i=0;  // integer variables declaration  
    while(a[i]!='\0' &&b[i]!='\0')  // while loop  
    {  
       if(a[i]!=b[i])  
       {  
           flag=1;  
           break;  
       }  
       i++;  
    }  
    if(flag==0) {
        return 0;  
    } else {
        return 1;  
    }
}

void load_instructions(t_my_struct* s1, int argc, char* argv[]) {
    s1->is_stdin = false;
    s1->is_color = false;
    if(argc < 2) {
        fprintf(stderr, "Error input\n");
        exit(INPUT_ERR);
    }else if(argc == 2) {
        s1->msg = argv[1];
        s1->is_stdin = true;
    }else if(argc == 3) {
        s1->msg = argv[1];
        s1->file_name = argv[2];
    }else {
        for(int i = 0; i < argc; i++) {
            if(compare(argv[i], "--color=always") == 0) {
                s1->is_color = true;
            }
        }
        s1->msg = argv[argc-2];
        s1->file_name = argv[argc-1];
    }
}

void find_the_length(t_my_struct* s1) {
    int i = 0;
    while(s1->msg[i] != '\0') {
        i++;
    }
    s1->length = i;
}

int* my_malloc(int size) {
    int* tmp = malloc(sizeof(int) * size);
    if(tmp == NULL) {
        fprintf(stderr, "Error: Cannot malloc!\n");
        free(tmp);
        exit(ALLOC_ERR);
    }
    return tmp;
}

int* my_realloc(int* size, int* arr) {
    int* tmp = NULL;
    *size = *size * 2;
    tmp = realloc(arr, sizeof(int) * *size);
    if(tmp == NULL) {
        fprintf(stderr, "Error: Cannot realloc!\n");
        free(arr);
        arr = NULL;
        exit(ALLOC_ERR);
    }
    return tmp;
};

void main_logic(FILE* f, t_my_struct* s1) {
    int idx = 0;
    char letter;
    char compared_text[s1->length + 1];
    s1->line_size = s1->value_arr_size = INIT_SIZE;
    s1->line = my_malloc(s1->line_size);
    s1->value_arr = my_malloc(s1->value_arr_size);
    s1->value_arr_row = 0;
    s1->compared_text_ind = 0;

    while(s1->is_stdin ? (letter = getchar()) != EOF : (letter = getc(f)) != EOF) {
        //Save content of line in array
        s1->line[idx] = letter;

        find_word_in_text(s1, compared_text, idx, letter);
        
        //Increase index
        idx++;

        //Realloc when there is no space for other elements
        if(idx >= s1->line_size) {
            s1->line = my_realloc(&s1->line_size, s1->line);
        }

        //Print result and reset values
        if(letter == '\n') {
            print_result(s1, idx);
            reset_values(s1);
            idx = 0;
        }
    }

    if(s1->is_in_row == true) {
        print_line(s1->line, idx);
    }
}

void find_word_in_text(t_my_struct* s1, char compared_text[], int idx, char letter) {
    if(s1->compared_text_ind == s1->length) {
        compared_text[s1->length] = '\0';
        int r = compare(compared_text, s1->msg);
        if(r == 0) {
            s1->is_in_row = true;
            s1->is_empty = false;
            s1->compared_text_ind = 0;
            
            compared_text[s1->compared_text_ind] = letter;
            s1->compared_text_ind++;
            s1->value_arr[s1->value_arr_row] = (idx - 1 - s1->length);
            s1->value_arr_row++;
            if(s1->value_arr_row >= s1->value_arr_size) {
                s1->value_arr = my_realloc(&s1->value_arr_size, s1->value_arr);
            }
        }else {
            for(int l = 0; l < (s1->length - 1); l++) {
                compared_text[l] = compared_text[l+1];
            }
            s1->compared_text_ind--;
            compared_text[s1->compared_text_ind] = letter;
            s1->compared_text_ind++;
        }
    }else {
        compared_text[s1->compared_text_ind] = letter;
        s1->compared_text_ind++;
    }
}

void print_result(t_my_struct* s1, int idx) {
    int row = 0;
    if(s1->is_in_row == true) {
        for(int j = 0; j < (idx - 1); j++) {
            if(s1->is_color == true) {
                if(row < s1->value_arr_row) {
                    if(s1->value_arr[row] == (-1) && j == 0) {
                        printf("\x1b[01;31m\x1b[K");
                    }
                }
            }
            printf("%c", s1->line[j]);

            if(s1->is_color == true) {
                if(row < s1->value_arr_row) {
                    if(j == (s1->value_arr[row] + s1->length)) {
                        printf("\x1b[m\x1b[K");
                        row++;
                    }
                }
                if(row < s1->value_arr_row) {
                    if(j == s1->value_arr[row]) {
                        printf("\x1b[01;31m\x1b[K");
                    }
                }
            }
        }

        printf("\n");
    }
}

void reset_values(t_my_struct* s1) {
    s1->is_in_row = false;
    free(s1->line);
    free(s1->value_arr);
    s1->line_size = s1->value_arr_size = INIT_SIZE;
    s1->line = my_malloc(s1->line_size);
    s1->value_arr = my_malloc(s1->value_arr_size);
    s1->value_arr_row = 0;
}

void print_line(int* line, int idx) {
    for(int j = 0; j < (idx-1); j++) {
            printf("%c", line[j]);
    }
    printf("\n");
}

void close_file(FILE* f, t_my_struct s1) {
    if (fclose(f) == EOF) {
        fprintf(stderr, "Error: Close file ’%s’\n", s1.file_name);
        exit(FILE_CLOSE_ERR);
    }
}
