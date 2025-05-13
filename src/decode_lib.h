/*
 * decode_lib.h
 * 
 * This header file defines the interface for decoding Caesar ciphers using statistical analysis.
 * It implements a sophisticated approach using chi-squared testing to determine the most likely
 * shift value used to encode the text.
 * 
 * Key Concepts:
 * 1. Caesar Cipher: A simple substitution cipher where each letter is shifted by a fixed amount
 * 2. Chi-Squared Test: A statistical method to compare observed frequencies with expected frequencies
 * 3. Letter Frequency Analysis: Using known English letter frequencies to break the cipher
 * 
 * The functions defined here are:
 * 1. encode: Encodes a single character using a given shift
 * 2. encode_string: Encodes an entire string using a given shift
 * 3. offset: Converts a letter to its position in the alphabet (0-25)
 * 4. chi_sq: Calculates the chi-squared value for a given shift
 * 5. encode_shift: Determines the most likely shift used to encode the text
 * 6. to_decode: Converts an encoding shift to a decoding shift
 * 
 * These functions work together to:
 * - Analyze encoded text using statistical methods
 * - Determine the most likely shift value used
 * - Decode the text back to its original form
 * - Handle both encoding and decoding operations
 */

#include <stdio.h>    /* For file operations */
#include <string.h>   /* For string manipulation */
#include <ctype.h>    /* For character type checking */
#include <stdbool.h>  /* For boolean type */
#include "frequency_table.h"  /* For letter frequency analysis */
#include <stdlib.h>   /* For memory management */

/* Encodes a single character using Caesar cipher with given shift */
char encode(char c, int shift);

/* Encodes an entire string using Caesar cipher with given shift */
void encode_string(char * string, int shift);

/* Converts a letter to its position in alphabet (0-25) */
int offset(char i);

/* Calculates chi-squared value for given shift to determine likelihood */
double chi_sq(char * c, int shift);

/* Determines most likely shift used to encode the text */
int encode_shift(char * c);

/* Converts encoding shift to decoding shift (e.g., shift 3 -> shift 23) */
int to_decode(int shift);
