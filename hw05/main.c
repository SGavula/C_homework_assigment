#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUMB_OF_SHIFTS 52
#define INIT_SIZE 11
#define SIGNS_BETWEEN_ALPHABET 6
#define SHIFT_BY_ALPH_INTERVAL 58

/*
    Source of the Wagner-Fisher Algorithm: https://www.lemoda.net/c/levenshtein/
*/

//Error numbers
enum {
    ERR_INPUT = 100,
    ERR_LENGTH
};

//Declaration of functions
int check_if_is_optional(int argc, char* argv[]);
int validate_input(char* line1, char* line2, bool optional);
void* malloc_memory(int size_of, int size);
char* realloc_memory(char* str, int* len, int* size);
char* load_line(int* size1);
void decode(int ret, char* line1, char* line2, char* decoded_word, char* msg, bool optional);
void make_shift(char* line1, char* decoded_word, int shift);
int do_shift_logic(int ascii_letter, int shift);
void compare_words(char* decoded_word, char* line2, char* msg, int* match_max);
void compare_words_with_distance(char* decoded_word, char* line2, char* msg, int* a, int k);
int distance(char* word1, char* word2, int len1, int len2);
void fill_first_matrix_col(int** matrix, int len1);
void fill_first_matrix_row(int** matrix, int len2); 
void fill_matrix(int** matrix, char * word1, char* word2,  int len1, int len2);
void do_wagner_fisher(int** matrix, char c1, char c2, int i, int j);
void print_msg(char* msg);
void free_memory(char* line1, char* line2, char* decoded_word, char* msg);

/*
    MAIN
*/
int main(int argc, char* argv[]) {
    char *line1, *line2, *decoded_word, *msg;
    int size1, size2, ret;    
    bool optional = false;
    line1 = line2 = decoded_word = msg = NULL;
    size1 = size2 = INIT_SIZE;
    ret = 0;

    optional = check_if_is_optional(argc, argv);

    line1 = load_line(&size1);
    line2 = load_line(&size2);

    //Check if lines are not empty
    if(line1 && line2) {
        ret = validate_input(line1, line2, optional);

        //Malloc for later use
        decoded_word = malloc_memory(sizeof(char), size1);
        msg = malloc_memory(sizeof(char), size1);

        decode(ret, line1, line2, decoded_word, msg, optional);
    }

    return ret;
}

int check_if_is_optional(int argc, char* argv[]) {
    return argc > 1 && strcmp(argv[1], "-prp-optional") == 0;
}

int validate_input(char* line1, char* line2, bool optional) {
    for(int i = 0; i < strlen(line1); i++) {
        int letter = line1[i];

        //Verify the input if it only contains letters from the alphabet
        if(letter < 'A' || letter > 'z'){
            fprintf(stderr, "Error: Chybny vstup!\n");
            return ERR_INPUT;
        }

        if(letter > 'Z' && letter < 'a') {
            fprintf(stderr, "Error: Chybny vstup!\n");
            return ERR_INPUT;
        }
    }

    //Validate words length only if not optional
    if(!optional) {
        if(strlen(line1) != strlen(line2)) {
            fprintf(stderr, "Error: Chybna delka vstupu!\n");
            return ERR_LENGTH;
        }
    }

    return EXIT_SUCCESS;
}

void* malloc_memory(int size_of, int size) {
    char* str = NULL;

    str = malloc(size_of * size);
    //Check if malloc was successful, if not hadle free, if so return char array 
    if (str == NULL) {
        fprintf(stderr, "ERROR: Malloc\n");
        free(str);
        str = NULL;
        exit(ERR_INPUT);
    }

    return str;
}

char* realloc_memory(char* str, int* len, int* size) {
    //Increase the size of the loaded characters
    *size = (*size * 2) + 1;
    char* tmp = realloc(str, sizeof(char) * (*size));
    
    //Check if realloc was successful, if not hadle free, if so return char array
    if (tmp == NULL) {
        free(str);
        str = NULL;
        *len = 0;
        fprintf(stderr, "ERROR: Realloc\n");
        exit(ERR_INPUT);
    }

    return tmp;
}

char* load_line(int* size) {
    char* str = NULL;
    char c;
    int len = 0;

    str = malloc_memory(sizeof(char), (*size + 1));
    
    //Read char by char in line and add each char to the char array
    while(scanf("%c", &c) != EOF && c != '\n') {
        if (len >= *size) {
            str = realloc_memory(str, &len, size);
        }
        str[len] = c;
        len++;
    }

    //Finish with end of string symbol
    if (str && len > 0) {
        str[len] = '\0';
    }else if (len == 0) {
        //If nothing to read, free memory
        free(str);
        str = NULL;
    }

    return str;
}

void decode(int ret, char* line1, char* line2, char* decoded_word, char* msg, bool optional) {
    int comparative_value, shift;
    comparative_value = 0;
    shift = 0;

    if(ret == EXIT_SUCCESS) {
        //Shift cycle
        for(int k = 0; k < NUMB_OF_SHIFTS; k++) {
            shift = k;
            make_shift(line1, decoded_word, shift);
            if(!optional) {
                compare_words(decoded_word, line2, msg, &comparative_value);
            }else {
                compare_words_with_distance(decoded_word, line2, msg, &comparative_value, k);
            }
        }
        print_msg(msg);
    }

    //Free all string arrays
    free_memory(line1, line2, decoded_word, msg);
}

void make_shift(char* line1, char* decoded_word, int shift) {
    for(int i = 0; i < strlen(line1); i++) {
        //Convert a character into an integer according to the ASCII table
        int ascii_letter = line1[i];
        int code = 0;
        
        code = do_shift_logic(ascii_letter, shift);
        
        //Convert a code (integer) back to a character and add it to the char array
        decoded_word[i] = (char)code;
    }
    //Finish with end of string symbol
    decoded_word[strlen(line1)] = '\0';
}

int do_shift_logic(int ascii_letter, int shift) {
    int code = 0;
    code = ascii_letter + shift;
    //Check if the number is uppercase or lowercase
    if(ascii_letter >= 'A' && ascii_letter <= 'Z') {
        if(code > 'Z') {
            //Increase by extra signs (signs between 'Z' and 'a' in ascii table)
            code = code + SIGNS_BETWEEN_ALPHABET;
        }
        if(code > 'z') {
            //Stay in an alphabetical interval
            code = code - SHIFT_BY_ALPH_INTERVAL;
        }
    }else {
        if(code > 'z') {
            //Stay in an alphabetical interval
            code = code - SHIFT_BY_ALPH_INTERVAL;
        }
        if(code >= 'a' && shift > 32) {
            code = code + SIGNS_BETWEEN_ALPHABET;
        }
        if(code > 'Z' && code < 'a') {
            //Increase by extra signs (signs between 'Z' and 'a' in ascii table)
            code = code + SIGNS_BETWEEN_ALPHABET;
        }
    }

    return code;
}

void compare_words(char* decoded_word, char* line2, char* msg, int* comparative_value){
    int match_value = 0;

    //Compare letters in the decoded word with the sample word (line2) and count how many letters are the same
    for(int i = 0; i < strlen(line2); i++) {
        if(decoded_word[i] == line2[i]) {
            match_value = match_value + 1;
        }
    }

    //Find decoded word with the largest number of identical letters and add it to the char array - message
    if(*comparative_value < match_value) {
        *comparative_value = match_value;

        for(int i = 0; i < strlen(decoded_word); i++) {
            msg[i] = decoded_word[i];
        }

        msg[strlen(decoded_word)] = '\0';
    }
}

void compare_words_with_distance(char* decoded_word, char* line2, char* msg, int* comparative_value, int k) {
    int len1, len2, d;
    len1 = len2 = d = 0;

    //Find out the length of the decoded code and sample word
    len1 = strlen(decoded_word);
    len2 = strlen(line2);

    //Find the distance between two words
    d = distance(decoded_word, line2, len1, len2);

    //Initial value of comparative_value
    if(k == 0) {
        *comparative_value = d;
    }

    //Find the decoded word, with the lowest distance and add it to the char array - message
    if(*comparative_value >= d) {
        *comparative_value = d;
        for(int i = 0; i < strlen(decoded_word); i++) {
            msg[i] = decoded_word[i];
        }
        msg[strlen(decoded_word)] = '\0';
    }
}

//Return distance between two words
int distance(char * word1, char* word2, int len1, int len2) {
    int rows = len1 + 1;
    int col = len2 + 1;
    int result = 0;
    int** matrix = NULL;

    //Allocate memory for matrix
    matrix = malloc_memory(sizeof(int *), rows);
    for(int i = 0; i < rows; i++) {
        matrix[i] = malloc_memory(sizeof(int), col);
    }

    fill_first_matrix_col(matrix, len1);
    fill_first_matrix_row(matrix, len2);
    fill_matrix(matrix, word1, word2, len1, len2);

    //save the last number in matrix - the lowest distance between two words
    result = matrix[len1][len2];

    //free memory
    for(int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return result;
}

void fill_first_matrix_col(int** matrix, int len1) {
    for (int i = 0; i <= len1; i++) {
        matrix[i][0] = i;
    }
}

void fill_first_matrix_row(int** matrix, int len2) {
    for (int i = 0; i <= len2; i++) {
        matrix[0][i] = i;
    }
}

void fill_matrix(int** matrix, char * word1, char* word2, int len1, int len2) {
    int i = 0;
    for (i = 1; i <= len1; i++) {
        int j;
        char c1;

        c1 = word1[i-1];
        for (j = 1; j <= len2; j++) {
            char c2;

            c2 = word2[j-1];
            do_wagner_fisher(matrix, c1, c2, i, j);
        }
    }
}

//Compute Wagner-Fischer algorithm
void do_wagner_fisher(int** matrix, char c1, char c2, int i, int j) {
    //If the letters are identical, add the value from the previous diagonal to the new matrix cell
    if (c1 == c2) {
        matrix[i][j] = matrix[i-1][j-1];
    } else {
        int delete, insert, substitute, minimum;
        delete = insert = substitute = minimum = 0;

        //Make the operations
        delete = matrix[i-1][j] + 1;
        insert = matrix[i][j-1] + 1;
        substitute = matrix[i-1][j-1] + 1;
        minimum = delete;
       //Find the minimum value from operations (delete, insert, replace)
        if (insert < minimum) {
            minimum = insert;
        }
        if (substitute < minimum) {
            minimum = substitute;
        }
        //Set the minimum value in the new cell of matrix
        matrix[i][j] = minimum;
    }
}

void print_msg(char* msg) {
    for(int i = 0; i < strlen(msg); i++) {
        printf("%c", msg[i]);
    }
    printf("\n");
}

void free_memory(char* line1, char* line2, char* decoded_word, char* msg) {
    free(line1);
    free(decoded_word);
    free(line2);
    free(msg);
}
