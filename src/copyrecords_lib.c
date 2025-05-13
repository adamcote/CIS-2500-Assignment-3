/*
 * copyrecords_lib.c
 * 
 * This file implements the library functions declared in copyrecords.h.
 * It provides functionality for:
 * 1. Calculating file sizes
 * 2. Reading binary records from files
 * 
 * Key Implementation Details:
 * 1. Binary File Operations: Using fseek, ftell, and fread
 * 2. Memory Management: Dynamic allocation of record arrays
 * 3. File Position Management: Proper handling of file pointers
 * 
 * Note: The readRecords function is currently a stub and needs implementation.
 * The commented code shows a partial implementation that can be used as a reference.
 */

#include "frequency_table.h"  /* For frequency analysis */
#include "decode_lib.h"       /* For Caesar cipher functions */
#include "copyrecords.h"      /* For record structure and function declarations */
#include <stdio.h>            /* For file operations */
#include <string.h>           /* For string operations */
#include <stdlib.h>           /* For memory management */
#include <ctype.h>            /* For character type checking */
#include <stdbool.h>          /* For boolean type */

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
 * Implementation Details:
 * 1. Uses fseek to move to end of file (SEEK_END)
 * 2. Uses ftell to get current position (file size)
 * 3. Uses rewind to restore file pointer to start
 * 4. Returns the size in bytes
 * 
 * Example:
 *   FILE *fp = fopen("data.bin", "rb");
 *   int size = file_size(fp);  // Gets total bytes in file
 *   int records = size / sizeof(record);  // Gets number of records
 */
int file_size(FILE * fp) {
    int sz = 0;  /* Size of file in bytes */
    
    /* Move to end of file */
    fseek(fp, 0L, SEEK_END);
    
    /* Get current position (file size) */
    sz = ftell(fp);
    
    /* Reset file pointer to start */
    rewind(fp);
    
    return sz;
}

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
 * Note: This is currently a stub implementation that only allocates
 * a single record pointer. The commented code below shows how it
 * should be implemented to:
 * 1. Read all records from the file
 * 2. Allocate memory for each record
 * 3. Store records in a dynamically sized array
 * 4. Handle memory allocation failures
 * 
 * TODO: Implement full functionality as shown in commented code
 */
struct record ** readRecords(FILE * fp) {
    /* Currently just allocates space for one record pointer */
    struct record ** records = malloc(sizeof(record *));
    if (records == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for records array\n");
        return NULL;
    }
    
    /* 
     * Implementation should follow this pattern:
     * 1. Calculate number of records from file size
     * 2. Allocate initial array of record pointers
     * 3. For each record:
     *    - Allocate memory for record
     *    - Read record from file
     *    - Add to array
     *    - Reallocate array if needed
     * 4. Return array of records
     * 
     * See commented code below for reference implementation
     */
    
    return records;
}

/* 
 * Reference implementation (commented out):
 * 
 * struct record ** readRecords(FILE * fp) {
 *     int total = 0;  // Number of records read
 *     struct record ** records = malloc(sizeof(record *));
 *     
 *     // Read each record
 *     while (!feof(fp)) {
 *         // Allocate memory for new record
 *         struct record * temp = malloc(sizeof(record));
 *         if (temp == NULL) {
 *             // Handle allocation failure
 *             for (int i = 0; i < total; i++) {
 *                 free(records[i]);
 *             }
 *             free(records);
 *             return NULL;
 *         }
 *         
 *         // Read record from file
 *         if (fread(temp, sizeof(record), 1, fp) != 1) {
 *             free(temp);
 *             break;
 *         }
 *         
 *         // Add to array
 *         records = realloc(records, sizeof(struct record *) * (total + 1));
 *         records[total] = temp;
 *         total++;
 *     }
 *     
 *     return records;
 * }
 */
