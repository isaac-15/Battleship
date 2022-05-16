#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROWS 10
#define MAX_COLS 10
#define EMPTY_MARKER '-'
#define HIT_MARKER '*'
#define MISS_MARKER 'm'

//enum types
typedef enum placement_style {
	NONE, RANDOM, MANUAL
}Placement_style;

typedef enum first_player {
	USER, COMPUTER
}First_player;

typedef enum ship_name {
	SHIP_NONE = '\0', CARRIER = 'c', BATTLESHIP = 'b', CRUISER = 'r', SUBMARINE = 's', DESTROYER = 'd'
}Ship_name;

typedef enum ship_status {
	SUNK, AFLOAT
}Ship_status;

typedef enum shot_status {
	EMPTY, HIT, MISS
}Shot_status;

typedef struct stats {
	int total_hits;
	int total_misses;
	int total_shots;
	double hit_to_misses_ratio;
}Stats;

/*
Function: print_rules()
Date Created: 11.12.21
Date Last Modified:
Description: prints the rules to battleship
Input Parameters: none
Returns: none
Preconditions: none
Postconditions: rules of battleship are printed to consol
*/
void print_rules(void);

/*
Function: print_welcome_screen()
Date Created: 11.12.21
Date Last Modified:
Description: prints a welcome screen
Input Parameters: none
Returns: the user selection
Preconditions: none
Postconditions: prints a welcome screen to consol and prompts for a selection
*/
int print_welcome_screen(void);

/*
Function: init_board()
Date Created: 11.6.21
Date Last Modified:
Description: initializes the player board to all ~
Input Parameters: a 2D array of characters for a game board, the number of rows, the number of columns
Returns: nothing
Preconditions: none
Postconditions: the board is initalized to all '~'
*/
void init_board(char board[][MAX_COLS], int num_rows, int num_cols);

/*
Function: randomly_place_ship()
Date Created: 11.6.21
Date Last Modified: 
Description: randomly places a ship of a specified length on a 2D array of characters
Input Parameters: 2D array of characters representing a game board, number of rows , number of columns, the ship length
Returns: nothing
Preconditions: the game board is initialzed
Postconditions: a ship of the specified length is placed on the game board
*/
void randomly_place_ship(char board[][MAX_COLS], int num_rows, int num_cols, int ship_length, Ship_name ship_name);

/*
Function: randomly_place_ships()
Date Created: 11.6.21
Date Last Modified:
Description: randomly places the ships on a board of characters
Input Parameters: a 2D array of characters for a game board, num rows, num columns
Returns: nothing
Preconditions: game board is initialized
Postconditions: the board has all ships randomly placed on it
*/
void randomly_place_all_ships(char board[][MAX_COLS], int num_rows, int num_cols);

/*
Function: manually_place_ship(char board[][MAX_COLS], int num_rows, int num_cols, int ship_length, int ship_char)
Date Created: 11.6.21
Date Last Modified:
Description: a user manually places a ship on a game board
Input Parameters: a 2D array of characters for a game board, the number of rows, and the number of columns
Returns: nothing
Preconditions: game board is initialized
Postconditions: the board has 1 ship manually placed on it
*/
void manually_place_ship(char board[][MAX_COLS], int num_rows, int num_cols, int ship_length, Ship_name ship_name);

/*
Function: manually_place_all_ships(char board[][MAX_COLS], int num_rows, int num_cols)
Date Created: 11.6.21
Date Last Modified:
Description: a user manually places all ships on a game board
Input Parameters: a 2D array of characters for a game board, the number of rows, and the number of columns
Returns: nothing
Preconditions: game board is initialized
Postconditions: the board has all ships manually placed on it
*/
void manually_place_all_ships(char board[][MAX_COLS], int num_rows, int num_cols);

/*
Function: print_player_board()
Date Created: 11.6.21
Date Last Modified:
Description: prints out the player board
Input Parameters: a 2D array of characters for a player game board, the number of rows and the number of columns
Returns: nothing
Preconditions: player board is initalized
Postconditions: player board is printed to the consol
*/
void print_player_board(char board[][MAX_COLS], int num_rows, int num_cols);

/*
Function: print_computer_board()
Date Created: 11.6.21
Date Last Modified:
Description: prints out the computer's board, hiding the placement of ships
Input Parameters: a 2D array of characters for a player game board, number of rows, number of columns
Returns: nothing
Preconditions: computer's board is initialized
Postconditions: the computer's board is printed to the screen hiding the placement of their ships
*/
void print_computer_board(char board[][MAX_COLS], int num_rows, int num_cols);

/*
Function: prompt_for_placement_style(void)
Date Created: 11.8.21
Date Last Modified:
Description: prompts for the placement style of ships and returns a Placement_style
Input Parameters: none
Returns: a placement style
Preconditions: none
Postconditions: user is prompted for placement style
*/
Placement_style prompt_for_placement_style(void);

/*
Function: select_first_player(void)
Date Created: 11.8.21
Date Last Modified:
Description: randomly selects the first player
Input Parameters: none
Returns: a First_player data type which corresponds to the first player
Preconditions: none
Postconditions: none
*/
First_player select_first_player(void);

/*
Function: get_ship_status(char board[MAX_ROWS][MAX_COLS], int rows, int cols, Ship_name ship)
Date Created: 11.8.21
Date Last Modified:
Description: checks the board to see if the ship is still afloat
Input Parameters: a pointer to a 2d character array for the game baord, the number of rows and columns, and the ship to check for
Returns: the status of the ship (wheter it is sunk or afloat)
Preconditions: the board is initalized and the ships have been placed on it
Postconditions: none
*/

Ship_status get_ship_status(char board[MAX_ROWS][MAX_COLS], int rows, int cols, Ship_name ship);

/*
Function: game_board_has_ships()
Date Created: 11.8.21
Date Last Modified:
Description: determines whether a given game_board still has ships
Input Parameters: the game_board (2d array of chars), the number of rows, the number of columns
Returns: a boolean value true/false
Preconditions: the game board is initalized
Postconditions: none
*/
bool game_board_has_ships(char game_board[MAX_ROWS][MAX_COLS], int rows, int cols);

/*
Function: prompt_for_shot()
Date Created: 11.9.21
Date Last Modified:
Description: prompts the user for a location to shoot and if the location is whithin the game board sets two variabels to the target row and the target col
Input Parameters: board rows, board cols and two pointers. One for target row and one for target col
Returns: nothing
Preconditions: none
Postconditions: the direct values of the pointer's passed in have been changed
*/
void prompt_for_shot(int board_rows, int board_cols, int* target_row_ptr, int* target_col_ptr);

/*
Function: check_shot()
Date Created: 11.9.21
Date Last Modified: 
Description: checks to see if the user can shoot in the space selected
Input Parameters: pointer to a 2d character array, number of rows, number of columns, row for the shot, col for the shot
Returns: a shot_status for the target location
Preconditions: the board is initalized and the ships are placed, the target row and target col are on the playing grid
Postconditions: none
*/
Shot_status can_take_shot(char game_board[MAX_ROWS][MAX_COLS], int num_rows, int num_cols, int target_row, int target_col);

/*
Function: take_and_check_shot()
Date Created: 11.9.21
Date Last Modified:
Description: shoots at a specified location and determines if the shot was a hit or a miss and what ship was hit
Input Parameters: the game board to be shot at, the target row and target column, a pointer to a shot status variable, a pointer to a ship name variable
Returns: nothing
Preconditions: the game board has been initialized, ships have been placed, the target row and target col are on the game board, the target has not been shot at b4
Postconditions: the target location is updated on the game_board to a hit or a miss
*/
void take_and_check_shot(char game_board[MAX_ROWS][MAX_COLS], int target_row, int target_col, Shot_status* hit_or_miss_ptr, Ship_name* hit_ship_ptr);

/*
Function: print_player_stats()
Date Created: 11.9.21
Date Last Modified:
Description: prints the player's stats
Input Parameters: a pointer to a stats struct for a player and a pointer to the file to print to
Returns: nothing
Preconditions: the instance of the stats struct is initalized, and the file the pointer references has been opened
Postconditions: the player stats are printed to the outfile
*/

void print_player_stats(Stats* player_ptr, FILE* outfile_ptr);

/*
Function: print_winner()
Date Created: 11.12.21
Date Last Modified:
Description: prints the winner of battleship
Input Parameters: a game board to check if it still has ships
Returns: nothing
Preconditions: one player has had all their ships sunk
Postconditions: prints the winner to the log file
*/
void print_winner_to_log(FILE* log, char game_board[MAX_ROWS][MAX_COLS]);

/*
Function:
Date Created:
Date Last Modified:
Description:
Input Parameters:
Returns:
Preconditions:
Postconditions:
*/


#endif