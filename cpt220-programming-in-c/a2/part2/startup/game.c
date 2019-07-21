/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2019.
 *****************************************************************************/
#include "game.h"
#include "main.h"
/**
 * initialise the game structure passed in. For full details of the requirements
 * for this function, please see the assignment requirements.
 **/
BOOLEAN game_init(struct game* thegame)
{
        int player_count;
        srand(thegame->seed);
        normal_print("Using seed %ld\n", thegame->seed);
        board_init(thegame->game_board);
        for (player_count = 0; player_count < NUM_PLAYERS; ++player_count)
        {
                if (!player_init(thegame->players + player_count, thegame))
                {
                        return FALSE;
                }
        }
        determine_player_order(thegame);
        return TRUE;
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
        char* heading = NULL;
        /**
         * set the seed in the game struct - set to the current time unless the
         * seed was provided.
         **/
        if (seed.success)
        {
                thegame.seed = seed.thelong;
        }
        else
        {
                thegame.seed = time(NULL);
        }
        /* print the heading */
        heading = "Welcome to CPT220 Backgammon";
        normal_print("%s\n", heading);
        PUTLINE('-', strlen(heading));

        /**
         * if initialisation of the game failed, we should quit
         **/
        if (!game_init(&thegame))
        {
                return;
        }
        /* implement game loop logic here */
        while (!quit)
        {
                /**
                 * this is a part 3 requirement so it should not be released to
                 * students until after they submit their final submission
                 **/

                /* let the player have their turn */
                enum input_result result =
                    player_take_turn(thegame.current_player);
                /**
                 * if the player quits during their turn, check whether either
                 * player has a higher score and if they do, declare them to be
                 * the winner
                 **/
                if (result == IR_QUIT)
                {
                        struct player* winner, *loser;
                        if (thegame.current_player->score >
                            thegame.other_player->score)
                        {
                                winner = thegame.current_player;
                                loser = thegame.other_player;
                        }
                        else if (thegame.current_player->score <
                                 thegame.other_player->score)
                        {
                                winner = thegame.other_player;
                                loser = thegame.current_player;
                        }
                        else
                        {
                                winner = loser = NULL;
                                normal_print("\nThe game was a draw!\n");
                                return;
                        }
                        normal_print(
                            "\nThe winner was %s who won by %d points.\n",
                            winner->name, winner->score - loser->score);

                        return;
                }
                /* otherwise, check if the game has actually been won and if so
                 * declare the winner of the game */
                if (has_won_game(thegame.current_player))
                {
                        normal_print("\nCongratulations! %s has won the game "
                                     "with a score of %d\n",
                                     thegame.current_player->name,
                                     thegame.current_player->score);
                        return;
                }
                /**
                 * otherwise the game is ongoing so we just swap the players to
                 * change whose turn it is.
                 **/
                if (result == IR_SUCCESS || result == IR_SKIP_TURN)
                {
                        swap_players(&thegame.current_player,
                                     &thegame.other_player);
                }
        }
}

/**
 * swap the players by swapping the pointers. Please note this is an advanced
 * and optional requirement but should be straight forward if you have
 * understood pointers. This is an optional requirement as I don't expect
 * everyone will be able to do this.
 **/
void swap_players(struct player** first, struct player** second)
{
        struct player* temp = *first;
        *first = *second;
        *second = temp;
}
