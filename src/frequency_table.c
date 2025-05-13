#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "frequency_table.h"


int main( int argc, char ** argv) {
   int USE_STDIN = true;
   int in_file = 0;
   char * buffer = malloc(sizeof(char) * 100);
   strcpy(buffer, "");
   char * file_contents = malloc(sizeof(char) * 100);
   strcpy(file_contents, "");
   FILE * fp = NULL;
  
/*if (argc == 1) {
       fprintf(stderr, "%s\n", "Not enough arguments.");
   }*/
   if (argc >= 2) {


       int next_is_input = false;
       for (int i = 1; i < argc; i++) {
           if (next_is_input == true) {


               USE_STDIN = false;
               in_file = i;
               next_is_input = false;
           }
           if (strcmp(argv[i], "-F") == 0) {
               next_is_input = true;
           }
       }
       /*USE_STDOUT = false;
       if (fp == NULL) {
           USE_STDIN = true;
       }*/
   }
   if (USE_STDIN == true) {
       // if (file_contents[strlen(file_contents)] == '\n') {
       //     file_contents[strlen(file_contents)] = '\0';
       while (fgets(buffer, 100, stdin) != NULL) {
           file_contents = realloc(file_contents, sizeof(char) * (strlen(file_contents) + strlen(buffer) + 1));
           strcat(file_contents, buffer);
       }
   }
   else {
       fp = fopen(argv[in_file], "r");
       while (fgets(buffer, 100, fp) != NULL) {
           file_contents = realloc(file_contents, sizeof(char) * (strlen(file_contents) + strlen(buffer) + 1));
           strcat(file_contents, buffer);
       }
       printf("File Contents: %s\n", file_contents);
       fclose(fp);
   }


 
   int count = letter_count(file_contents);
   printf("Letter Count: %d\n", count);


   int character_count = strlen(file_contents);
   printf("Character Count: %d\n", character_count);


   int * freq_table = frequency_table(file_contents);
   for (int i = 0; i < 26; i++) {
       printf("%c\t", i + 65);
       printf("%d\n", freq_table[i]);
   }


   free(buffer);
   free(file_contents);
   free(freq_table);


  
}
