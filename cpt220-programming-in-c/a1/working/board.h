/******************************************************************************
 * Student Name    :  Dallas Hall
 * RMIT Student ID :  s3461243
 * COURSE CODE     :  CPT220 / OLA00
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2019.
 *****************************************************************************/
#include "shared.h"
#include <string.h>

#ifndef BOARD_H
#define BOARD_H
#define BOARD_WIDTH 12
#define BOARD_HEIGHT 14

/**
 * a piece on the board is just an integer on the board with the value specified
 * by thos enumeration. It has specifically been constructured so that empty is
 * 0, red is 1 and white is 2 with the invalid token being -1. Please don't use
 * the integer values - use the values for the constants as your code will be
 * much more readable.
 **/
enum piece
{
	P_EMPTY,
	P_RED,
	P_WHITE,
	P_INVALID = -1
};

/**
 * a board is simply an array of pieces being 14 high and 12 wide. Please note
 * that we normally represent the height dimension as coming first in our
 * programs as that's more efficient in terms of speed to access the memory.
 **/
typedef enum piece board[BOARD_HEIGHT][BOARD_WIDTH];
/**
 * You may add your own data structures here to manage this module
 **/
#define PRINT_HEIGHT 33
#define PRINT_WIDTH 73
#include "io.h"
/**
 * end of the declarations added by the student for this module
 **/

/**
 * I have only provided one global function declaration here but you should feel
 * free to add more of your own.
 **/
void board_init(board);

void printBoard(board the_board);

void printBoardReverse(board the_board);

void prettyPrintBoard(board the_board);

void prettyPrintBoardReverse(board the_board);

/*
 * Uses nested if statements for starting positions.
 */

enum piece getStartPiece(int row, int column);

void setStartPiece(int x, int y, board the_board);

/*
 * Uses a 2d array of starting pieces.
 */
enum piece getStartPieceArray(int row, int column);

void setStartPieceArray(int row, int column, board the_board);

/*
 * Read the current state of the board
 */
enum piece getPieceFromBoardState(int x, int y, board the_board);


#endif
