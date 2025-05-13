/*
 * frequency_lib.c
 * 
 * This file implements the letter frequency analysis functions declared in frequency_table.h.
 * These functions are essential for breaking Caesar ciphers by analyzing letter patterns.
 * 
 * Key Concepts Used:
 * 1. String Handling: Using C's string functions to process text
 * 2. Memory Management: Dynamic allocation for the frequency table
 * 3. ASCII Manipulation: Converting between characters and their ASCII values
 * 4. Character Classification: Using ctype.h functions to identify letters
 */

#include "frequency_table.h"
#include <ctype.h>    /* For isalpha() - checks if a character is a letter */
#include <string.h>   /* For strlen() - gets length of strings */
#include <stdlib.h>   /* For malloc() - dynamic memory allocation */
#include <stdio.h>    /* For printf() - debugging output */

/*
 * letter_count
 * 
 * Purpose: Counts how many letters (a-z, A-Z) are in a given string
 * 
 * Parameters:
 *   string - A pointer to the text we want to analyze
 * 
 * Returns:
 *   The total number of letters found in the string
 * 
 * How it works:
 * 1. Initialize a counter to 0
 * 2. Loop through each character in the string
 * 3. For each character, check if it's a letter using isalpha()
 * 4. If it is a letter, increment the counter
 * 5. Return the final count
 * 
 * Example:
 *   Input: "Hello123"
 *   Output: 5 (counts 'H', 'e', 'l', 'l', 'o')
 */
int letter_count(char * string) {
    int count = 0;  /* Counter for letters found */
    
    /* Loop through each character in the string */
    for (int i = 0; i < strlen(string); i++) {
        /* isalpha() returns non-zero if character is a letter, 0 otherwise */
        if (isalpha(string[i]) > 0) {
            count++;  /* Found a letter, increment counter */
        }
    }
    return count;  /* Return total number of letters found */
}

/*
 * frequency_table
 * 
 * Purpose: Creates a table showing how many times each letter appears in the text
 * 
 * Parameters:
 *   string - A pointer to the text we want to analyze
 * 
 * Returns:
 *   A pointer to an array of 26 integers, where:
 *   - Index 0 represents 'A' or 'a'
 *   - Index 1 represents 'B' or 'b'
 *   - And so on until index 25 for 'Z' or 'z'
 * 
 * How it works:
 * 1. Allocate memory for 26 integers (one for each letter)
 * 2. Initialize all counts to 0
 * 3. Loop through each character in the string
 * 4. For each letter found:
 *    - Convert to uppercase using toupper()
 *    - Subtract 'A' (ASCII 65) to get index 0-25
 *    - Increment the count at that index
 * 5. Return the frequency table
 * 
 * Memory Management:
 * - Uses malloc() to create the table
 * - Caller is responsible for freeing the memory when done
 * 
 * Example:
 *   Input: "Hello"
 *   Output: [0,0,0,0,1,0,0,1,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,0,0,0]
 *           (counts for A-Z: H=1, E=1, L=2, O=1)
 */
int * frequency_table(char * string) {
    int * freq_table;  /* Pointer to our frequency table */
    
    /* Allocate memory for 26 integers (one for each letter) */
    freq_table = malloc(sizeof(int) * 26);
    if (freq_table == NULL) {
        /* Handle memory allocation failure */
        return NULL;
    }
    
    /* Initialize all counts to 0 */
    for (int i = 0; i < 26; i++) {
        freq_table[i] = 0;
    }
    
    /* Process each character in the string */
    for (int i = 0; i < strlen(string); i++) {
        if (isalpha(string[i]) > 0) {  /* If character is a letter */
            /* Convert to uppercase and subtract 'A' (65) to get index 0-25 */
            freq_table[toupper(string[i]) - 65] += 1;
        }
    }
    
    return freq_table;  /* Return the completed frequency table */
}
