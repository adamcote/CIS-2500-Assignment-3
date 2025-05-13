#include <stdio.h>
#include "copyrecords.h"
#include "decode_lib.h"
#include "frequency_table.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


// Variable declarations


int main(int argc, char ** argv) {
   int r_present = false;
   // int shift = 0;
   FILE * input_file = NULL;
   FILE * output_file = NULL;
   FILE * cipher_file = NULL;
   char * o_flag = NULL;
   char * f_flag = NULL;
   char * d_flag = NULL;
   int decode_shift = 0;
   int total = 0;
   int num_of_records = 0;
   char * buffer = malloc(sizeof(char) * 100);
   strcpy(buffer, "");
   char * file_contents = malloc(sizeof(char) * 100);
   strcpy(file_contents, "");


   //Checking command line flags that user can use in the program


   if (argc <= 1) {
       return 1;
   }


   for (int i = 1; i < argc; i++) {
       if (strcmp(argv[i], "-O") == 0) {
           i++;
           o_flag = malloc(sizeof(char) * strlen(argv[i]) + 1);
           strcpy(o_flag, argv[i]);
       }
       else if (strcmp(argv[i], "-F") == 0) {
           i++;
           f_flag = malloc(sizeof(char) * (strlen(argv[i])+ 1));
           strcpy(f_flag, argv[i]);
       }
       else if (strcmp(argv[i], "-D") == 0) {
           i++;
           d_flag = malloc(sizeof(char) * (strlen(argv[i])+ 1));
           strcpy(d_flag, argv[i]);
       }
       else if (strcmp(argv[i], "-r") == 0) {
           r_present = true;
       }
   }
 
  // conditions for -F flag


   if (f_flag == NULL) {
       fprintf(stderr, "Input file has not been given.\n");
       return 1;
   }
  
   else {
       input_file = fopen(f_flag, "r");
   }


   // conditions for -O flag


   if (o_flag == NULL) {
       fprintf(stderr, "Output file has not been given.\n");
       return 1;
   }


   else {
       output_file = fopen(o_flag, "wb");
   }


   //conditions for -D flag


   if (d_flag != NULL) {
       cipher_file = fopen(d_flag, "r");
       while (fgets(buffer, 100, cipher_file) != NULL) {
           file_contents = realloc(file_contents, sizeof(char) * (strlen(file_contents) + strlen(buffer) + 3));
           strcat(file_contents, buffer);
       }
       decode_shift = to_decode(encode_shift(file_contents));
       fclose(cipher_file);
   }


   num_of_records = file_size(input_file) / sizeof(record);
   fseek(input_file, 0L, SEEK_SET);


   // conditions for -R flag
  
   while (total < num_of_records) {
       if (r_present) {
           fseek(input_file, -sizeof(record) * (total + 1), SEEK_END);
       }
       record * temp = malloc(sizeof(record));
       fread(temp, sizeof(record), 1, input_file);
       encode_string(temp -> str1, decode_shift);
       encode_string(temp -> str2, decode_shift);
       fwrite(temp, sizeof(record), 1, output_file);
       total++;
   }
}


