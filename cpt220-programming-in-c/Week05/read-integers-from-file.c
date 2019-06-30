#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_INTS 10
#define EXPECTED_ARGS 2
#define DELIMITER ","
#define BUFFER_SIZE 256

/*
 * argc = argument count
 * argv = array of arguments, the 0 element is always the program name.
 */ 
int main(int argc, char *argsv[])
{
	FILE *inputFilePointer;
	FILE *outputFilePointer;
	int numbers[MAX_INPUT_INTS] = {0};
	int i;
	char *tokenPointer;
	char aLine[BUFFER_SIZE];
	char *strtolRemainderPointer;
	long sum;

	puts("# Read Integers From File");
	/*
	 * Remember to add 1 because the program name is always passed
	 */ 
	if(argc != EXPECTED_ARGS + 1) {
		fprintf(stderr, "[ERROR] Invalid arguments supplied. Should only be %d but got %d.\n", EXPECTED_ARGS, argc);
	}

	puts("## Program Arguments");
	for (i = 0; i < EXPECTED_ARGS + 1; i++) {
		printf("Argument %d is %s\n", i, argsv[i]);
	}

	puts("\n## Opening I/O Files");
	/*
	 * Open for read only.
	 */ 
	if ((inputFilePointer = fopen(argsv[1], "r")) == NULL) {
		fprintf(stderr, "[ERROR] Input file couldn't be opened. Does it exist?.\n");
	}
	else {
		printf("Opened the input file %s\n", argsv[1]);
	}
	/*
	 * Create new file or overwrite existing file.
	 */ 
	if ((outputFilePointer = fopen(argsv[2], "w")) == NULL) {
		fprintf(stderr, "[ERROR] Output file couldn't be opened..\n");
	}
	else {
		printf("Created or opened and overwrote the output file %s\n", argsv[2]);
	}
	
	puts("\n## Reading Integers From Input File");

	/*
	 * Read characters from FILE pointer until newline, null controll characeter, or buffer exhausted. 
	 * Store these into an array with the size of BUFFER.
	 */ 
	while(fgets(aLine, BUFFER_SIZE, inputFilePointer) != NULL) {
		for(i = 0; i < BUFFER_SIZE; i++) {
			printf("Element %d is %c\n", i, aLine[i]);
			/*
			 * We read the whole line.
			 */ 
			if(aLine[i] == '\n') {
				break;
			}
			/*
			 * We found the end of the string.
			 */ 
			else if(aLine[i] == '\0') {
				break;
			}
		}
	}

	puts("## Tokenising Input File & Printing Tokens");
	/*
	 * Create first token
	 */
	tokenPointer = strtok(aLine, DELIMITER);
	i = 0;
	
	/*
	 * Need multiple calls to get all the tokens.
	 */ 
	while (tokenPointer != NULL) {
		if(i > MAX_INPUT_INTS) {
			fprintf(stderr, "[ERROR] Too many integers inside the input file. Maximum is ten, but found %d\n", i);
		}
		numbers[i] = strtol(tokenPointer, &strtolRemainderPointer, 0);
		printf("Token poitner is %s\n", tokenPointer);
		printf("numbers[%d] is %d\n", i, numbers[i]);
		/*
		 * The NULL argument tell strtok to keep going.
		 * NULL is returned when there are no more tokens.
		 */ 
		tokenPointer = strtok(NULL, DELIMITER);
		++i;
	}

	puts("## Writing Input Tokens And Sum");
	sum = 0;
	for(i = 0; i < MAX_INPUT_INTS; i++) {
		sum += numbers[i];
		fprintf(outputFilePointer, "%d%c", numbers[i], ',');
	}
	fprintf(outputFilePointer, "%ld\n", sum);

	puts("## Closing Open Resources");
	fclose(inputFilePointer);
	fclose(outputFilePointer);

	return EXIT_SUCCESS;
}
