/******************************************************************************
 * Student Name    :  Dallas Hall
 * RMIT Student ID :  s3461243
 * COURSE CODE     :  CPT220 / OLA00
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2019.
 *****************************************************************************/
#include "io.h"
#include "game.h"

const int DEBUGGING_IO = 0;

const char *color_strings[NUM_COLORS] = {"\x1b[31m", "\x1b[37m", "\x1b[0m"};

/**
 * function that does buffer clearing when there is a buffer overflow on
 * input - only call this function when there is an actual buffer overflow as
 * otherwise you will have additional problems
 **/
void clear_buffer(void)
{
	int ch;
	/* while there are still chars to read and we have not reached
	 * the newline char, keep reading */
	while (ch = getc(stdin), ch != EOF && ch != '\n');
	/* reset the error status on the stdin file pointer */
	clearerr(stdin);
}

/**
 * this function simply calls printf. It is implemented here so that if we
 * wish to change our output target (such as using a gui) we could change our
 * implementation here and it would not affect any other code in our project.
 **/
int normal_print(const char format[], ...)
{
	int char_count;
	va_list vlist;
	va_start(vlist, format);
	char_count = vprintf(format, vlist);
	va_end(vlist);
	return char_count;
}

/**
 * this function prints out error messages to the stderr file pointer. It is
 * standard practice to output all error messages to stderr rather than
 * stdout (where printf sends messages).
 **/
int error_print(const char format[], ...)
{
	int char_count = 0;
	va_list vlist;
	char_count += fprintf(stderr, "Error: ");
	va_start(vlist, format);
	char_count += vfprintf(stderr, format, vlist);

	return char_count;
}

/**
 * defines how to print the board given the orientation passed in. Pleas
 * see the asssignment specifications for further details.
 **/
void board_print(board theboard, enum orientation orient)
{
	int row, column, topNumber, bottomNumber, rowOffset, columnOffset, currentPiece;

	if (DEBUGGING_IO) {
		printf("%s\n", "[DEBUG] io.c - Entering board_print.");
	}

	printBoardHeaderMessage();
	/*
	 * Use for printing the board numbers.
 	 * These need to be decremented
 	 */

	if (orient == OR_CLOCKWISE) {
		topNumber = 12;
		bottomNumber = 13;
	}
	else if (orient == OR_ANTICLOCKWISE) {
		topNumber = 13;
		bottomNumber = 12;
	}
	/*
	 * Used for printing tokens.
	  * These need to be incremented.
	  */
	rowOffset = 0;
	columnOffset = 0;
	for (row = 0; row < PRINT_HEIGHT; row++) {
		for (column = 0; column < PRINT_WIDTH; column++) {
			/*
			 * Only print the - for the top, bottom, and every even row.
			 */
			if (row == 0 || row % 2 == 0 || row == PRINT_HEIGHT - 1) {
				printf("-");
			}
				/*
				 * Only print the board numbers on the second and second last row.
				 */
			else if (row == 1 || row == PRINT_HEIGHT - 2) {
				if (column == 0 || column % 6 == 0 ||
					column == PRINT_WIDTH - 1) {
					printf("|");
				}
				/*
				 * Print topNumber only on row 1.
				 * Print bottomNumber only on row 32
				 * Print each number in the first space of each column.
				 */
				switch (column) {
					case 1:
					case 7:
					case 13:
					case 19:
					case 25:
					case 31:
					case 37:
					case 43:
					case 49:
					case 55:
					case 61:
					case 66:
						if (orient == OR_CLOCKWISE) {
							if (row == 1) {
								printf("  %2d ", topNumber);
								--topNumber;
							}
							else if (row == PRINT_HEIGHT - 2) {
								printf("  %2d ", bottomNumber);
								++bottomNumber;
							}
							break;
						}
						else if (orient == OR_ANTICLOCKWISE) {
							if (row == 1) {
								printf("  %2d ", topNumber);
								++topNumber;
							}
							else if (row == PRINT_HEIGHT - 2) {
								printf("  %2d ", bottomNumber);
								--bottomNumber;
							}
						}
				}
			}
				/*
				 * Only print the '|', ' ', and tokens on every odd row.
				 */
			else if (row % 2 == 1) {
				if (column == 0 || column % 6 == 0 ||
					column == PRINT_WIDTH - 1) {
					printf("|");
				}
					/*
					 * Skip every 3rd spot as this might have a player token.
					 */
				else if (column % 3 != 0) {
					printf(" ");
				}
				else {
					if (DEBUGGING_IO) {
						printf("x: %d y: %d", rowOffset, columnOffset);
					}
					/*currentPiece = getStartPiece(rowOffset, columnOffset);*/
					/*currentPiece = getStartPieceArray(rowOffset, columnOffset);*/
					currentPiece = getPieceFromBoardState(rowOffset,
														  columnOffset,
														  theboard);
					if (currentPiece == 0) {
						printf(" ");
					}
					else if (currentPiece == 1) {
						printf("%s%c%s", color_strings[COLOR_RED],
							   RED_TOKEN,
							   color_strings[COLOR_RESET]);

					}
					else if (currentPiece == 2) {
						printf("%s%c%s", color_strings[COLOR_WHITE],
							   WHITE_TOKEN, color_strings[COLOR_RESET]);

					}
					++columnOffset;
				}

			}
		}
		/*
		 * Increment the row offset so we have the correct row next run
		 * Reset the column offset so we have the current column next run
		 */
		if (row >= 3 && row % 2 != 0) {
			++rowOffset;
			columnOffset = 0;
		}

		printf("\n");
	}

	printBoardFooterMessage();
}

/*
 * Basic board printing for debugging.
 */
void printBoard(board the_board)
{
	int row, column;
	if (DEBUGGING_IO) {
		printf("%s\n", "[DEBUG] board.c - Entering printBoard.");
	}
	for (row = 0; row < BOARD_HEIGHT; row++) {
		for (column = 0; column < BOARD_WIDTH; column++) {
			printf("[%d][%d] %d\t", row, column, the_board[row][column]);
			if (column == BOARD_WIDTH - 1) {
				printf("\n");
			}
		}
	}
}

void printBoardReverse(board the_board)
{
	int row, column;
	if (DEBUGGING_IO) {
		printf("%s\n", "[DEBUG] board.c - Entering printBoardReverse.");
	}
	for (row = BOARD_HEIGHT - 1; row >= 0; row--) {
		for (column = 0; column < BOARD_WIDTH; column++) {
			printf("[%d][%d] %d\t", row, column, the_board[row][column]);
			if (column == BOARD_WIDTH - 1) {
			}
		}
	}
}

void printBoardHeaderMessage()
{
	printf("\nCPT220 Backgammon - Current Board State\n");
}

void printBoardFooterMessage()
{
	/*
	 * Store the pointer to the game object.
	 */
	struct game *theGame = getGame();
	char *name = theGame->current_player->name;
	int score = theGame->current_player->score;
	char *colour;
	char *direction;
	char token;
	char barCount[6]; /* including the '\0' */

	if (theGame->current_player->orientation == OR_CLOCKWISE) {
		colour = "white";
		direction = "clockwise";
		token = 'X';
	}
	else {
		colour = "red";
		direction = "anticlockwise";
		token = 'O';
	}

	/*
	 * TODO - check what happens with a number, and fold output to 80
	 */
	if (theGame->current_player->bar_list.token_count == 0) {
		strcpy(barCount, "empty");
	}
	else {
		sprintf(barCount, "%d", theGame->current_player->bar_list.token_count);
	}

	printf("It is your turn %s. Your score is %d, your colour is %s", name,
		   score, colour);
	printf(", your token is %c, your direction is %s, and your bar list is %s.\n",
		   token, direction, barCount);
}

BOOLEAN getPlayerName(struct player * currentPlayer)
{
	char input[MAXPROMPTLEN];
	struct game gamePointer = *getGame();

	int i;

	if (DEBUGGING_IO) {
		printf("%s\n", "[DEBUG] player.c - Entering getName.");
	}

	if (strlen(gamePointer.players[0].name) == 0) {
		normal_print("Player 1, enter your name (max 20 characters): ", input);
	}
	else if (strlen(gamePointer.players[1].name) == 0) {
		normal_print("Player 2, enter your name (max 20 characters): ", input);
	}

	/*
 * Need to account for the '\n' and '\0' that fgets adds.
 * If the char last isn't '\n' then we know we didn't receive all the input.
 * We need to remove the '\n' as well.
 */

	if (fgets(input, MAXPROMPTLEN + FGETS_EXTRA_CHARS, stdin) == NULL) {
		return FALSE;
	}

	/*
	 * Remember that strlen doesn't include the \0 in its count
	 */

	if (input[strlen(input) - 1] != '\n') {
		error_print("Buffer overflow.\n");
		clear_buffer();
		return getPlayerName(currentPlayer);
	}

	if (strlen(input) > NAME_LEN + 1) {
		error_print("Input too long, less than 20 only.\n");
		return getPlayerName(currentPlayer);
	}

	if (strlen(input) < MIN_NAME_LEN) {
		error_print("Input too short, greater than 1 only.\n");
		return getPlayerName(currentPlayer);
	}

	if (DEBUGGING_IO) {
		printf("[DEBUG] player.c - strlen(s) before removing \\n is %ld\n",
			   strlen(input));
		printf("[DEBUG] player.c - s is %s\n", input);
	}

	/*
 * Replace \n with \0
 */

	input[strlen(input) - 1] = '\0';

	if (DEBUGGING_IO) {
		printf("[DEBUG] player.c - strlen(s) after removing \\n is %ld\n",
			   strlen(input));
		printf("[DEBUG] player.c - s is %s\n", input);

		printf("%s\n", "[DEBUG] player.c - Printing s with for loop.");
		for (i = 0; i < strlen(input); i++) {
			printf("%c", input[i]);
		}
		printf("\n");
	}

	/*
	 * Copy the input string into the player
	 */
	strcpy(currentPlayer->name, input);


	if (DEBUGGING_IO) {
		printf("[DEBUG] player.c - aplayer -> name is %s\n", currentPlayer->name);
		printf("%s\n",
			   "[DEBUG] player.c - Printing aplayer -> name with for loop.");
		for (i = 0; i < strlen(input); i++) {
			printf("%c", currentPlayer->name[i]);
		}
		printf("\n");
	}

	return TRUE;
}

/*
 * The next 2 functions are used during debugging, so we can see which pointer
 * is currently inside of current_player or other_player.
 */
void printCurrentPlayer(struct game *thegame)
{
	printf("[DEBUG] player.c - printCurrentPlayer\n");
	printf("thegame->current_player.name is %s\n",
		   thegame->current_player->name);
	printf("thegame->current_player.score is %d\n",
		   thegame->current_player->score);
	printf("thegame->current_player.token is %d\n",
		   thegame->current_player->token);
	printf("thegame->current_player.orientation is %d\n",
		   thegame->current_player->orientation);
	printf("thegame->current_player.bar_list.token_count is %d\n",
		   thegame->current_player->bar_list.token_count);
}

void printOtherPlayer(struct game *thegame)
{
	printf("[DEBUG] player.c - printOtherPlayer\n");
	printf("thegame->other_player.name is %s\n", thegame->other_player->name);
	printf("thegame->other_player.score is %d\n", thegame->other_player->score);
	printf("thegame->other_player.token is %d\n", thegame->other_player->token);
	printf("thegame->other_player.orientation is %d\n",
		   thegame->other_player->orientation);
	printf("thegame->current_player.bar_list.token_count is %d\n",
		   thegame->current_player->bar_list.token_count);
}
