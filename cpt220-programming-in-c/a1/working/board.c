/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2019.
 *****************************************************************************/
#include "board.h"

/**
 * init_board() - provide the logic to initialise the board to the same data as
 * shown in the assignment specification. Please note that a naive
 * implementation (eg: one without loops) will not get full marks. For full
 * details of the requirement of this function, please see the assignment
 * requirements
 **/
void
board_init(board the_board)
{
        int row, column;
        if(DEBUGGING) {
          printf("%s\n", "[DEBUG] board.c - Entering board_init.");
        }

        for(row = 0; row < BOARD_HEIGHT; row++) {
          for(column = 0; column < BOARD_WIDTH; column++) {
            if(DEBUGGING) {
              printf("[DEBUG] board.c - Creating piece at row[%d]column[%d]\n", row, column);
              /*
              White's 5 pieces at 13
              */
              if(row == 0 && column == 0) {
                the_board[row][column] = P_WHITE;
              }
              else if(row == 1 && column == 0) {
                the_board[row][column] = P_WHITE;
              }
              else if(row == 2 && column == 0) {
                the_board[row][column] = P_WHITE;
              }
              else if(row == 3 && column == 0) {
                the_board[row][column] = P_WHITE;
              }
              else if(row == 4 && column == 0) {
                the_board[row][column] = P_WHITE;
              }

              /*
              Reds's 3 pieces at 8
              */
              else if(row == 0 && column == 4) {
                the_board[row][column] = P_RED;
              }
              else if(row == 1 && column == 4) {
                the_board[row][column] = P_RED;
              }
              else if(row == 2 && column == 4) {
                the_board[row][column] = P_RED;
              }

              /*
              Reds's 5 pieces at 6
              */
              else if(row == 0 && column == 6) {
                the_board[row][column] = P_RED;
              }
              else if(row == 1 && column == 6) {
                the_board[row][column] = P_RED;
              }
              else if(row == 2 && column == 6) {
                the_board[row][column] = P_RED;
              }
              else if(row == 3 && column == 6) {
                the_board[row][column] = P_RED;
              }
              else if(row == 4 && column == 6) {
                the_board[row][column] = P_RED;
              }

              /*
              White's 2 pieces at 24
              */
              else if(row == 0 && column == 11) {
                the_board[row][column] = P_WHITE;
              }
              else if(row == 1 && column == 11) {
                the_board[row][column] = P_WHITE;
              }

              /*
              Reds's 5 pieces at 12
              */
              else if(row == 9 && column == 0) {
                the_board[row][column] = P_RED;
              }
              else if(row == 10 && column == 0) {
                the_board[row][column] = P_RED;
              }
              else if(row == 11 && column == 0) {
                the_board[row][column] = P_RED;
              }
              else if(row == 12 && column == 0) {
                the_board[row][column] = P_RED;
              }
              else if(row == 13 && column == 0) {
                the_board[row][column] = P_RED;
              }

              /*
              White's 3 pieces at 8
              */
              else if(row == 11 && column == 4) {
                the_board[row][column] = P_WHITE;
              }
              else if(row == 12 && column == 4) {
                the_board[row][column] = P_WHITE;
              }
              else if(row == 13 && column == 4) {
                the_board[row][column] = P_WHITE;
              }

              /*
              White's 5 pieces at 6
              */
              else if(row == 9 && column == 6) {
                the_board[row][column] = P_WHITE;
              }
              else if(row == 10 && column == 6) {
                the_board[row][column] = P_WHITE;
              }
              else if(row == 11 && column == 6) {
                the_board[row][column] = P_WHITE;
              }
              else if(row == 12 && column == 6) {
                the_board[row][column] = P_WHITE;
              }
              else if(row == 13 && column == 6) {
                the_board[row][column] = P_WHITE;
              }

              /*
              Reds's 2 pieces at 24
              */
              else if(row == 12 && column == 11) {
                the_board[row][column] = P_RED;
              }
              else if(row == 13 && column == 11) {
                the_board[row][column] = P_RED;
              }

              /*
                Everything else is blank
              */
              else {
                the_board[row][column] = P_EMPTY;
              }

              printf("[DEBUG] board.c - The value of piece at row[%d]column[%d] is %d\n", row, column, the_board[row][column]);
            }
          }
        }


}

/**
 * You may provide your own function definitions here for this module
 **/
