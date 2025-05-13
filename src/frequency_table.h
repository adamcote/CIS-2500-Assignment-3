/*
 * frequency_table.h
 * 
 * This header file defines the interface for analyzing letter frequencies in text.
 * It's a crucial first step in breaking Caesar ciphers, as letter frequency analysis
 * is one of the most effective ways to crack simple substitution ciphers.
 * 
 * The functions defined here are:
 * 1. letter_count: Counts how many letters (a-z, A-Z) are in a given text
 * 2. frequency_table: Creates a table showing how many times each letter appears
 * 
 * These functions are used to:
 * - Analyze the distribution of letters in English text
 * - Compare this distribution with encoded text to find the cipher shift
 * - Help determine if text is actually English (by comparing letter frequencies)
 */

int letter_count(char * );  /* Counts total number of letters in a string */
int * frequency_table(char *);  /* Creates a frequency table of letter occurrences */
