SRC_DIR = src

all: frequency_lib.o frequency_table.o frequency_table decode_lib.o decode.o decode copyrecords_lib.o copyrecords.o copyrecords

frequency_lib.o : $(SRC_DIR)/frequency_lib.c
	gcc -Wall -g -c -o frequency_lib.o -std=c99 $(SRC_DIR)/frequency_lib.c

frequency_table.o: $(SRC_DIR)/frequency_table.c
	gcc -Wall -g -c -o frequency_table.o -std=c99 $(SRC_DIR)/frequency_table.c

frequency_table: frequency_table.o frequency_lib.o
	gcc -Wall -g -o frequency_table frequency_lib.o -std=c99 frequency_table.o

decode_lib.o: $(SRC_DIR)/decode_lib.c
	gcc -Wall -g -c -o decode_lib.o -std=c99 $(SRC_DIR)/decode_lib.c

decode.o: $(SRC_DIR)/decode.c
	gcc -Wall -g -c -o decode.o -std=c99 $(SRC_DIR)/decode.c

decode: decode.o decode_lib.o frequency_lib.o
	gcc -Wall -g -lm -o decode decode_lib.o -std=c99 decode.o frequency_lib.o

copyrecords_lib.o: $(SRC_DIR)/copyrecords_lib.c
	gcc -Wall -g -c -o copyrecords_lib.o -std=c99 $(SRC_DIR)/copyrecords_lib.c

copyrecords.o: $(SRC_DIR)/copyrecords.c
	gcc -Wall -g -c -o copyrecords.o -std=c99 $(SRC_DIR)/copyrecords.c

copyrecords: copyrecords.o copyrecords_lib.o decode_lib.o frequency_lib.o
	gcc -Wall -g -lm -o copyrecords copyrecords_lib.o -std=c99 copyrecords.o decode_lib.o frequency_lib.o

clean:
	del *.o
	del frequency_table
	del decode
	del copyrecords
