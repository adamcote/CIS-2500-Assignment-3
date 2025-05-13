/*
 * frequency_main.c
 * 
 * This is the main program for Question 1 of the Caesar Cipher assignment.
 * It reads text (either from a file or standard input), analyzes the letter frequencies,
 * and prints a detailed report of the analysis.
 * 
 * Program Features:
 * 1. Can read input from either:
 *    - A file specified with -F command line argument
 *    - Standard input (keyboard) if no file is specified
 * 2. Handles files of any size by dynamically allocating memory
 * 3. Prints a detailed report showing:
 *    - Total number of letters found
 *    - Total number of characters
 *    - A frequency table showing how many times each letter appears
 * 
 * Usage:
 *   ./frequency_table              # Read from keyboard (press Ctrl+D when done)
 *   ./frequency_table -F file.txt  # Read from file.txt
 * 
 * Key Programming Concepts Used:
 * 1. Command Line Arguments: Processing -F flag and filename
 * 2. File I/O: Reading from files and standard input
 * 3. Dynamic Memory: Managing buffers for file contents
 * 4. String Handling: Concatenating and manipulating text
 */

#include <stdio.h>    /* For file operations and printf */
#include <stdlib.h>   /* For malloc, free, and realloc */
#include <string.h>   /* For string manipulation functions */
#include <stdbool.h>  /* For boolean type */
#include <ctype.h>    /* For character type checking */
#include "frequency_table.h"  /* Our frequency analysis functions */

int main(int argc, char ** argv) {
    /* Variables for input handling */
    int USE_STDIN = true;     /* Flag: true if reading from keyboard */
    int in_file = 0;          /* Index of input filename in argv */
    
    /* Buffer for reading file in chunks */
    char * buffer = malloc(sizeof(char) * 100);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for buffer\n");
        return 1;
    }
    strcpy(buffer, "");
    
    /* Storage for complete file contents */
    char * file_contents = malloc(sizeof(char) * 100);
    if (file_contents == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for file contents\n");
        free(buffer);
        return 1;
    }
    strcpy(file_contents, "");
    
    FILE * fp = NULL;  /* File pointer for reading from file */

    /* Process command line arguments */
    if (argc >= 2) {
        int next_is_input = false;  /* Flag: true if next argument is filename */
        
        /* Loop through all arguments looking for -F flag */
        for (int i = 1; i < argc; i++) {
            if (next_is_input == true) {
                /* We found -F in previous iteration, so this is the filename */
                USE_STDIN = false;
                in_file = i;
                next_is_input = false;
            }
            if (strcmp(argv[i], "-F") == 0) {
                /* Found -F flag, next argument will be filename */
                next_is_input = true;
            }
        }
    }

    /* Read input based on whether we're using file or stdin */
    if (USE_STDIN == true) {
        /* Read from keyboard (standard input) */
        if (fgets(file_contents, 100, stdin) == NULL) {
            fprintf(stderr, "Error: Failed to read from standard input\n");
            free(buffer);
            free(file_contents);
            return 1;
        }
        
        /* Remove newline if present */
        if (file_contents[strlen(file_contents) - 1] == '\n') {
            file_contents[strlen(file_contents) - 1] = '\0';
        }
    } else {
        /* Read from file */
        fp = fopen(argv[in_file], "r");
        if (fp == NULL) {
            fprintf(stderr, "Error: Could not open file %s\n", argv[in_file]);
            free(buffer);
            free(file_contents);
            return 1;
        }
        
        /* Read file in chunks and append to file_contents */
        while (fgets(buffer, 100, fp) != NULL) {
            /* Expand file_contents if needed */
            char * temp = realloc(file_contents, 
                                sizeof(char) * (strlen(file_contents) + strlen(buffer) + 1));
            if (temp == NULL) {
                fprintf(stderr, "Error: Failed to allocate memory for file contents\n");
                free(buffer);
                free(file_contents);
                fclose(fp);
                return 1;
            }
            file_contents = temp;
            strcat(file_contents, buffer);
        }
    }

    /* Print analysis results */
    printf("\n=== Letter Frequency Analysis ===\n\n");
    
    /* Count and print total letters */
    int count = letter_count(file_contents);
    printf("Letter Count: %d\n", count);
    
    /* Count and print total characters */
    int character_count = strlen(file_contents);
    printf("Character Count: %d\n\n", character_count);
    
    /* Generate and print frequency table */
    printf("Letter Frequency Table:\n");
    printf("Letter\tCount\n");
    printf("-----\t-----\n");
    int * freq_table = frequency_table(file_contents);
    if (freq_table != NULL) {
        for (int i = 0; i < 26; i++) {
            printf("%c\t%d\n", i + 65, freq_table[i]);  /* i + 65 converts 0-25 to A-Z */
        }
        free(freq_table);  /* Clean up frequency table */
    }

    /* Clean up allocated memory */
    free(buffer);
    free(file_contents);
    if (fp != NULL) {
        fclose(fp);
    }
    
    return 0;
}
