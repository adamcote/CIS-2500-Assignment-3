#frequency_lib.c and frequency_table.c - Name of programs that contain first question

#Descriptions

frequency_table.c - contains main function, code is explained further in file
frequency_lib.c - contains library of functions used to make the frequency frequency_table

#Source Files
frequency_table.h
frequency_lib.c
frequency_lib.c
Makefile

#Compilation
make clean (not required, but good practice nonetheless)
make all

#Execution 
./frequency_table (with stdin)
./frequency_table -F myfile.txt (with -F flag included)

#decode_lib.c and decode.c - Name of programs that contain second question

#Descriptions

#decode_lib.c - contains functions used in programs, comments briefly explain code
#decode.c - main program, code is elaborated upon briefly in program

#Source Files
decode_lib.h
frequency_table.h
decode_lib.c
decode.c
Makefile

#Compilation
make clean
make all

#Execution
./decode
./decode -stx -F myfile.txt -O decodedfile.txt (example of how to run the program with flags)
* Flag options are -s, -S, -t, -x, -n, -F, and -O. -F and -O are compulsory for input and output.

#copyrecords.c and copyrecords_lib.c - Name of programs that contain third question

#Descriptions

copyrecords.c - main program, comments explain functionality briefly
copyrecords_lib.c - contains functions used for program, explained briefly through comments

#Source Files
copyrecords_lib.h
copyrecords_lib.c
copyrecords.c
Makefile

#Compilation
make clean
make all

#Execution
./copyrecords
./copyrecords -D myfile.txt -r -F sample_records.rec -O test.rec (example with all flags) 
