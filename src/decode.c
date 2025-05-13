/*
 * decode.c
 * 
 * This is the main program for Question 2 of the Caesar Cipher assignment.
 * It implements a sophisticated Caesar cipher decoder that can:
 * 1. Read encoded text from a file or standard input
 * 2. Automatically determine the shift used to encode the text
 * 3. Decode the text using statistical analysis
 * 4. Output results in various formats based on command line options
 * 
 * Program Features:
 * 1. Multiple input sources:
 *    - File input using -F flag
 *    - Standard input (keyboard) if no file specified
 * 2. Multiple output options:
 *    - Standard output (default)
 *    - File output using -O flag
 * 3. Analysis options:
 *    - -s: Show decoding shift
 *    - -S: Show original encoding shift
 *    - -t: Show frequency table
 *    - -x: Show chi-squared values for all shifts
 *    - -n: Suppress decoded text output
 * 
 * Usage Examples:
 *   ./decode -F encoded.txt -O decoded.txt -s -t
 *   ./decode -F encoded.txt -S -x
 *   ./decode < encoded.txt
 * 
 * Key Programming Concepts:
 * 1. Command Line Arguments: Processing multiple flags and options
 * 2. File I/O: Reading from files and standard input
 * 3. Dynamic Memory: Managing buffers for file contents
 * 4. Statistical Analysis: Using chi-squared testing
 * 5. String Manipulation: Encoding/decoding text
 */

#include <stdio.h>    /* For file operations and printf */
#include <string.h>   /* For string manipulation */
#include "decode_lib.h"  /* For decoding functions */
#include "frequency_table.h"  /* For frequency analysis */
#include <stdlib.h>   /* For memory management */
#include <ctype.h>    /* For character type checking */
#include <stdbool.h>  /* For boolean type */

int main(int argc, char ** argv) {
    /* Command line flag variables */
    char * oFlag = NULL;  /* Output file name (-O) */
    char * fFlag = NULL;  /* Input file name (-F) */
    int n_present = false;  /* Suppress output flag (-n) */
    int s_present = false;  /* Show decode shift flag (-s) */
    int S_present = false;  /* Show encode shift flag (-S) */
    int t_present = false;  /* Show frequency table flag (-t) */
    int x_present = false;  /* Show chi-squared values flag (-x) */
    
    /* File handling variables */
    FILE * f = NULL;  /* Input file pointer */
    
    /* Buffer for reading input in chunks */
    char * buffer = malloc(sizeof(char) * 100);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for buffer\n");
        return 1;
    }
    strcpy(buffer, "");
    
    /* Storage for complete input text */
    char * file_contents = malloc(sizeof(char) * 100);
    if (file_contents == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for file contents\n");
        free(buffer);
        return 1;
    }
    strcpy(file_contents, "");

    /* Process command line arguments */
    if (argc > 0) {
        for (int i = 1; i < argc; i++) {
            /* Handle combined flags (e.g., -stx) */
            if (strlen(argv[i]) > 2 && argv[i][0] == '-') {
                for (int j = 1; j < strlen(argv[i]); j++) {
                    switch (argv[i][j]) {
                        case 'n': n_present = true; break;
                        case 's': s_present = true; break;
                        case 'S': S_present = true; break;
                        case 't': t_present = true; break;
                        case 'x': x_present = true; break;
                    }
                }
            }
            
            /* Handle individual flags and their arguments */
            if (strcmp(argv[i], "-O") == 0) {
                /* Get output filename */
                i++;
                oFlag = malloc(sizeof(char) * (strlen(argv[i]) + 1));
                if (oFlag == NULL) {
                    fprintf(stderr, "Error: Failed to allocate memory for output filename\n");
                    free(buffer);
                    free(file_contents);
                    return 1;
                }
                strcpy(oFlag, argv[i]);
            }
            else if (strcmp(argv[i], "-F") == 0) {
                /* Get input filename */
                i++;
                fFlag = malloc(sizeof(char) * (strlen(argv[i]) + 1));
                if (fFlag == NULL) {
                    fprintf(stderr, "Error: Failed to allocate memory for input filename\n");
                    free(buffer);
                    free(file_contents);
                    return 1;
                }
                strcpy(fFlag, argv[i]);
            }
            /* Handle individual flags */
            else if (strcmp(argv[i], "-n") == 0) n_present = true;
            else if (strcmp(argv[i], "-s") == 0) s_present = true;
            else if (strcmp(argv[i], "-S") == 0) S_present = true;
            else if (strcmp(argv[i], "-t") == 0) t_present = true;
            else if (strcmp(argv[i], "-x") == 0) x_present = true;
        }

        /* Read input text */
        if (fFlag == NULL) {
            /* Read from standard input */
            while (fgets(buffer, 100, stdin) != NULL) {
                char * temp = realloc(file_contents, 
                                    sizeof(char) * (strlen(file_contents) + strlen(buffer) + 3));
                if (temp == NULL) {
                    fprintf(stderr, "Error: Failed to allocate memory for file contents\n");
                    free(buffer);
                    free(file_contents);
                    return 1;
                }
                file_contents = temp;
                strcat(file_contents, buffer);
            }
        } else {
            /* Read from file */
            f = fopen(fFlag, "r");
            if (f == NULL) {
                fprintf(stderr, "Error: Could not open input file %s\n", fFlag);
                free(buffer);
                free(file_contents);
                free(fFlag);
                return 1;
            }
            while (fgets(buffer, 100, f) != NULL) {
                char * temp = realloc(file_contents, 
                                    sizeof(char) * (strlen(file_contents) + strlen(buffer) + 3));
                if (temp == NULL) {
                    fprintf(stderr, "Error: Failed to allocate memory for file contents\n");
                    free(buffer);
                    free(file_contents);
                    free(fFlag);
                    fclose(f);
                    return 1;
                }
                file_contents = temp;
                strcat(file_contents, buffer);
            }
            fclose(f);
        }

        /* Process output flags */
        if (S_present) {
            /* Show original encoding shift */
            int min_shift = encode_shift(file_contents);
            printf("Encoded Shift: %d\n\n", min_shift);
        }

        if (s_present) {
            /* Show decoding shift */
            int min_shift = to_decode(encode_shift(file_contents));
            printf("Decoded Shift: %d\n\n", min_shift);
        }

        if (t_present) {
            /* Show frequency table */
            int * freq_table = frequency_table(file_contents);
            if (freq_table != NULL) {
                printf("Letter Frequency Table:\n");
                printf("Letter\tCount\n");
                printf("-----\t-----\n");
                for (int i = 0; i < 26; i++) {
                    printf("%c\t%d\n", i + 65, freq_table[i]);
                }
                
                /* Show character counts */
                int count = letter_count(file_contents);
                printf("\nLetter Count: %d\n", count);
                int character_count = strlen(file_contents);
                printf("Character Count: %d\n\n", character_count);
                
                free(freq_table);
            }
        }

        if (x_present) {
            /* Show chi-squared values for all possible shifts */
            printf("Chi-Squared Analysis:\n");
            printf("Shift\tChi-Squared Value\n");
            printf("-----\t----------------\n");
            for (int i = 0; i < 26; i++) {
                printf("%d\t%f\n", i, chi_sq(file_contents, i));
            }
            printf("\n");
        }

        /* Decode the text */
        char * decoded = malloc(sizeof(char) * (strlen(file_contents) + 1));
        if (decoded == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory for decoded text\n");
            free(buffer);
            free(file_contents);
            free(fFlag);
            free(oFlag);
            return 1;
        }
        strcpy(decoded, file_contents);
        
        /* Find and apply the decoding shift */
        int shift = encode_shift(decoded);
        int decode_shift = to_decode(shift);
        encode_string(decoded, decode_shift);
        
        /* Output decoded text */
        if (oFlag == NULL && !n_present) {
            /* Print to standard output */
            printf("%s", decoded);
        } else if (oFlag != NULL) {
            /* Write to output file */
            FILE * new_file = fopen(oFlag, "w");
            if (new_file == NULL) {
                fprintf(stderr, "Error: Could not open output file %s\n", oFlag);
                free(buffer);
                free(file_contents);
                free(fFlag);
                free(oFlag);
                free(decoded);
                return 1;
            }
            fprintf(new_file, "%s", decoded);
            fclose(new_file);
        }
        
        /* Clean up allocated memory */
        free(decoded);
    }
    
    /* Clean up remaining allocated memory */
    free(buffer);
    free(file_contents);
    free(fFlag);
    free(oFlag);
    
    return 0;
}
