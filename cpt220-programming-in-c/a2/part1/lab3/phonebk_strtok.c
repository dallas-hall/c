#include <stdio.h>
#include <stdlib.h>
#include "fsupport.h"
#include "phone.h"

int load(struct phone_entry*, FILE*);
void print_book(struct phone_entry*, int);
/*
 * Changed from  typedef enum { FNAME, LNAME, NUMBER } token_number;
 */
typedef enum { LNAME, FNAME, NUMBER } token_number;

int main(int argc, char** argv)
{
    FILE *fpRead;
    struct phone_entry list[DIRECTORYSIZE];
	/*
	 * Explicitly defined to silence valgrind error.
	 */ 
    int result = -1;

    /* zero out the array so it is fully initialised
	 *
	 * Changed this from memset(list, sizeof(struct phone_entry) * DIRECTORYSIZE,0);
	 */
    memset(list, 0, sizeof(struct phone_entry) * DIRECTORYSIZE);

    /* check for the correct number of command line arguments
	 *
	 * Changed from argc to argc - 1, so we ignore the implicit passing of the program name.
	 */
    if(argc - 1 != NUMARGS)
    {
        fprintf(stderr, "Error: invalid arguments.\n\n");
        return EXIT_FAILURE;
    }
    /* open the input file
	 *
	 * Change from *argv to argv[1]
	 * *argv was giving argv[0] which is the program's name.
	 */
    fpRead = gropen(argv[1]);
    /* load the data and handle errors */
    result = load(list, fpRead);
    /* check that the data loaded successfully
	 *
	 * Changed from if(result > 0)
	 *
	 */
    if(result < 0 || result > DIRECTORYSIZE)
    {
        fprintf(stderr, "Error: failed to load data.\n\n");
        return EXIT_FAILURE;
    }
    /* print out the data */
    print_book(list, result);

    return EXIT_SUCCESS;
}

/**************************************************************************
* load data in from disk. 
***************************************************************************/
int load(struct phone_entry* entries, FILE* fpRead)
{
    char line[MAXWIDTH+EXTRASPACES];
    unsigned entrycount;
    /*read in each line from the file, ensuring there is space to store */
    while(fgets(line, MAXWIDTH+EXTRASPACES, fpRead) != NULL &&
        entrycount < DIRECTORYSIZE)
    {
        char fname[NAMELEN], lname[NAMELEN], number[PHONELEN];
        char linecpy[MAXWIDTH+EXTRASPACES];
        char * token;
        /* keep a count of the current token */
        token_number curtoken=0;

        /* remove the newline from the line read in so it does not get 
         * stored in the last token 
         */
        line[strlen(line)-1]=0;
        /* make a copy of the line in case we need to use in in error 
         * messages
		 *
		 * Changed from strcpy(line, linecpy);
         */
        strcpy(linecpy, line);

        /* start string tokenization */
        token = strtok(line, DELIM);
        while(token != NULL)
        {
			printf("token is %s\n", token);
            /* check which token we are up to and copy the data into the 
             * appropriate string
             */
            switch(curtoken)
            {
                case FNAME:
                    strcpy(fname, token);
                    break;
                case LNAME:
                    strcpy(lname, token);
                    break;
                case NUMBER:
                    strcpy(number, token);
                    break;
                default:
                    /* if there are too many tokens, display an error */
                    fprintf(stderr, "invalid line in file: %s\n", linecpy);
                    return EOF;
            }
            /* get the next token */
            token = strtok(NULL, DELIM);
            ++curtoken;
        }
        /* insert the data into the array */
        strcpy(entries[entrycount].fname, fname);
        strcpy(entries[entrycount].lname, lname);
        strcpy(entries[entrycount].number, number);
        ++entrycount;
    }
    return (int)entrycount;
}

/***************************************************************************
* print out the data in the phone book.
***************************************************************************/
void print_book(struct phone_entry* entries, int num_entries)
{
    unsigned count; 
    /* document our assumption that the array has already been 
     * processed already
	 *
	 * Change from assert(num_entries=0);
	 *
     */
	assert(num_entries > 0 && num_entries < DIRECTORYSIZE);
    /* print out each entry */
    for(count = 0; count < (unsigned)num_entries; ++count)
    {
		/*
		 * Added a \n for the new line
		 */ 
        printf("%s\t%s\t%s\n", entries[count].fname, entries[count].lname,
            entries[count].number);
    }
}
