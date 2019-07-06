/******************************************************************************
 * Student Name    :  Dallas Hall
 * RMIT Student ID :  s3461243
 * COURSE CODE     :  CPT220 / OLA00
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2019.
 *****************************************************************************/
#include "game.h"

/*
 * The extern variable for this is inside shared.h
 * The controls debug message printing, 1 = on and 0 = off
 * https://stackoverflow.com/questions/1433204/how-do-i-use-extern-to-share-variables-between-source-files/1433387#1433387
 * 
 * Decided to use a dedicated variable per file, otherwise its just pages
 * and pages of [DEBUG] messages when turned on.
 * 
 * int DEBUGGING = 0;
 */

const int DEBUGGING_GAME = 0;

/*
 * Used to create a game object getter.
 * The * means we are using a pointer.
 */
struct game *theGamePointer;

/**
 * initialise the game structure passed in. For full details of the requirements
 * for this function, please see the assignment requirements.
 **/
BOOLEAN game_init(struct game *thegame)
{
	BOOLEAN gameInitialised = FALSE;

	if (DEBUGGING_GAME) {
		normal_print("%s\n", "[DEBUG] game.c - Trying to create the board.");
	}
	/*
	 * Need to use -> in here as we are going through a pointer.
	 */
	board_init(thegame->game_board);

	if (DEBUGGING_GAME) {
		printBoard(thegame->game_board);
		printBoardReverse(thegame->game_board);
		normal_print("%s\n", "[DEBUG] game.c - Trying to create the players.");
	}

	/*
	 * Setting these to empty so I can use later to determine which player
 	 * pointer was passed.
	 */
	thegame->players[0].name[0] = '\0';
	thegame->players[1].name[0] = '\0';

	/*
	 * Need don't need & here because we are using a pointer.
	 */
	gameInitialised = player_init(thegame->other_player, thegame);
	gameInitialised = player_init(thegame->current_player, thegame);

	if (DEBUGGING_GAME) {
		normal_print("%s\n",
					 "[DEBUG] game.c - Trying to print created the players.");
		/*
		 * Need to use -> since its a pointer.
		 */
		normal_print("The first player - thegame->current_player->name is %s\n",
					 thegame->current_player->name);
		normal_print("The first player - thegame.players[0].name is  %s\n",
					 thegame->players[0].name);
		normal_print("The second player - thegame.other_player->name is %s\n",
					 thegame->other_player->name);
		normal_print("The second player - thegame.players[1].name is  %s\n",
					 thegame->players[1].name);
	}

	/*
	 * Determine the player order.
	 * Need don't need & here because we are using a pointer.
	 * I based this off of the material in chapter 5 of C How To Program 6e
 	 * srand will make sure rand produces different number sequences.
	 * time() returns how many seconds since the Unix Epoch (1/1/1970).
	 * Was initially using NULL parameter, which for time means apply no
	 * formatting. But then I decided to use the supplied seed number.
	 * Needed the address operator to get the right data type,
 	 */
	srand(time(&thegame->seed));
	if (DEBUGGING_GAME) {
		printCurrentPlayer(thegame);
		printOtherPlayer(thegame);
	}

	determine_player_order(thegame);
	if (DEBUGGING_GAME) {
		printCurrentPlayer(thegame);
		printOtherPlayer(thegame);
	}

	gameInitialised = TRUE;

	return gameInitialised;
}

/**
 * you'll manage the game loop here and provide notification when a player has
 * won the game. Please see the assignment specifications for the full detail
 * on what is required here.
 **/
void play_game(struct falsible_long seed)
{
	/**
	 * declare and allocate memory for the main game struct
	 **/
	struct game thegame;
	BOOLEAN quit = FALSE;
	enum input_result gameStatus = IR_SUCCESS;
	char *heading = NULL;


	/**
	 * set the seed in the game struct - set to the current time if no
	 * seed was provided.
	 **/
	if (seed.success) {
		thegame.seed = seed.thelong;
	}
	else {
		thegame.seed = time(NULL);
	}

	/*
 	 * Used to pass around the game object when needed, like into io.c
     */
	theGamePointer = &thegame;

	/* print the heading */
	heading = "Welcome to Dallas` CPT220 Backgammon";
	PUTLINE('-', strlen(heading));
	normal_print("%s\n", heading);
	PUTLINE('-', strlen(heading));
	normal_print("The seed number being used is: %d\n", seed);
	PUTLINE('-', strlen(heading));

	/**
	 * if initialisation of the game failed, we should quit
	 **/
	if (!game_init(&thegame)) {
		return;
	}

	/* implement game loop logic here */
	while (!quit) {
		/*
		 * Print the board
		 */
		board_print(thegame.game_board, thegame.current_player->orientation);
		/*
		 * Current play takes their turn.
		 */
		gameStatus = player_take_turn(thegame.current_player);
		if (gameStatus == IR_SKIP_TURN) {
			/*
 			 * Swap current player with other player
 			 * Need to use & here so we get the address.
 			 */
			swap_players(&thegame.current_player, &thegame.other_player);
		}
		else if (gameStatus == IR_QUIT) {
			quit = TRUE;
		}
	}

	/* print the exit message */
	heading = "Thanks for playing Dallas` CPT220 Backgammon.";
	normal_print("\n");
	PUTLINE('-', strlen(heading));
	normal_print("%s\n", heading);
	PUTLINE('-', strlen(heading));
}

/**
 * swap the players by swapping the pointers. Please note this is an advanced
 * and optional requirement but should be straight forward if you have
 * understood pointers. This is an optional requirement as I don't expect
 * everyone will be able to do this.
 **/
void swap_players(struct player **first, struct player **second)
{
	/*
	 * Use * during declaration to signal this variable holds a pointer.
	 * Use * during assignment to dereference the pointer to a pointer.
	 */
	struct player *swap = *first;

	if (DEBUGGING_GAME) {
		normal_print("[DEBUG] - game.swap_players - BEFORE\n");
		printCurrentPlayer(theGamePointer);
		printOtherPlayer(theGamePointer);
		normal_print("\n");
	}

	*first = *second;
	*second = swap;

	if (DEBUGGING_GAME) {
		normal_print("[DEBUG] - game.swap_players - AFTER\n");
		printCurrentPlayer(theGamePointer);
		printOtherPlayer(theGamePointer);
		normal_print("\n");
	}
}

/*
 * Return the pointer (*) to the game object.
 * This is used to pass the game object around when needed. Such as into io.c
 */
struct game *getGame()
{
	return theGamePointer;
}