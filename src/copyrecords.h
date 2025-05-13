/*
 * copyrecords.h
 * 
 * This header file defines the interface for Question 3 of the Caesar Cipher assignment.
 * It implements a record copying system that can:
 * 1. Read binary records from an input file
 * 2. Optionally decode Caesar-encoded strings within the records
 * 3. Write the records to an output file
 * 
 * The program handles a custom binary record format that contains:
 * - Two string fields (24 and 144 characters)
 * - An array of 24 double values
 * - An array of 12 integers
 * 
 * Key Features:
 * 1. Binary file I/O: Reading and writing fixed-size records
 * 2. Optional Caesar cipher decoding of string fields
 * 3. Forward or reverse record copying
 * 4. File size calculation and record counting
 * 
 * Usage:
 * The program is typically run with command line arguments:
 *   -F <input_file>: Input file containing binary records
 *   -O <output_file>: Output file for processed records
 *   -D <cipher_file>: Optional file containing text to determine decode shift
 *   -r: Optional flag to copy records in reverse order
 */

#include <stdio.h>    /* For file operations */
#include "decode_lib.h"  /* For Caesar cipher functions */
#include "frequency_table.h"  /* For frequency analysis */
#include <stdlib.h>   /* For memory management */
#include <string.h>   /* For string operations */
#include <ctype.h>    /* For character type checking */
#include <stdbool.h>  /* For boolean type */

/* 
 * Record Structure
 * 
 * This structure defines the format of each record in the binary file:
 * - str1: First string field (24 characters)
 * - dbl: Array of 24 double-precision floating point numbers
 * - str2: Second string field (144 characters)
 * - nums: Array of 12 integers
 * 
 * The total size of this structure is fixed and can be calculated using sizeof(record).
 * This is important for binary file I/O operations.
 */
typedef struct record {
    char str1[24];    /* First string field */
    double dbl[24];   /* Array of 24 doubles */
    char str2[144];   /* Second string field */
    int nums[12];     /* Array of 12 integers */
} record;

/* 
 * file_size
 * 
 * Purpose: Calculate the total size of a file in bytes
 * 
 * Parameters:
 *   fp - File pointer to the file to measure
 * 
 * Returns:
 *   Total size of file in bytes
 * 
 * How it works:
 * 1. Seeks to end of file
 * 2. Gets current position (file size)
 * 3. Rewinds file pointer to start
 * 4. Returns size
 */
int file_size(FILE * fp);

/* 
 * readRecords
 * 
 * Purpose: Read records from a binary file into memory
 * 
 * Parameters:
 *   fp - File pointer to the input file
 * 
 * Returns:
 *   Array of pointers to record structures
 * 
 * Note: This function is currently a stub and needs implementation.
 * It should:
 * 1. Calculate number of records from file size
 * 2. Allocate array of record pointers
 * 3. Read each record into memory
 * 4. Return array of records
 */
struct record ** readRecords(FILE * fp);

