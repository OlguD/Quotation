CC=gcc
SOURCE_FILE=src/main.c	
OUTPUT_FILE=Generator
LIB=-lcurl

.PHONY:

make:
	$(CC) $(SOURCE_FILE) -o $(OUTPUT_FILE) $(LIB) 

run:
	./$(OUTPUT_FILE)

clean:
	rm -rf $(OUTPUT_FILE)