#include "Battleship.h"

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
void print_rules(void) {
	printf("1. Battleship is a two player game. You will be playing against another player or a computer.\n\
2. Your goal is to sink all of your opponents ships which consist of a carrier(5 spaces long),\n\
 a battleship(4 spaces long), a cruiser(3 spaces long), a submarine(3 spaces long), and a destroyer(2 spaces long)\n\
3. You will start the game by placing your ships.\n\
4. You can only place ships horizontally or vertically and they cannot overlapp or go off the board.\n\
5. You and your opponent will take turns firing at each other's ships.\n\
6. If your shot is the same as one of the coordinates of your enemies ship then your shot is a hit.\n\
7. If not your shot is a miss.\n\
8. Once a ship has been hit at each coordinate it has been placed over the ship sinks.\n\
9. If you're the first player to sink all of your opponent's ships, you win!\n");
}

/*
Function: print_welcome_screen()
Date Created: 11.12.21
Date Last Modified:
Description: prints a welcome screen
Input Parameters: none
Returns: nothing
Preconditions: none
Postconditions: prints a welcome screen to consol
*/
int print_welcome_screen(void) {

	char ans[50];
	char num = -1;
	printf("Welcome to Battleship!!\n");
	printf("1. Print Rules\n");
	printf("2. Player vs Player\n");
	printf("3. Player vs Computer\n");
	printf("4. Exit\n");
	do {
		gets(ans);
	} while (ans[0] == '\n' || !(strcmp(ans, "1") == 0 || strcmp(ans, "2") == 0 || strcmp(ans, "3") == 0 || strcmp(ans, "4") == 0));
	//printf("%s", ans);

	num = atoi(ans);
	return num;
}


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
void init_board(char board[][MAX_COLS], int num_rows, int num_cols) {
	int row_index = 0, col_index = 0;

	for (; row_index < num_rows; ++row_index)
	{
		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			board[row_index][col_index] = EMPTY_MARKER;
		}
	}
}

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
void randomly_place_ship(char board[][MAX_COLS], int num_rows, int num_cols, int ship_length, Ship_name ship_name) {

	char placement_direction = '\0';
	int row = -1, col = -1, rand_num = 0, is_empty = 1;

	//continue to loop untill an empty space is chosen
	do {
		//reset variables
		is_empty = 1;
		rand_num = rand() % 2;

		//choose placement direction
		if (rand_num){
			placement_direction = 'h';
		}
		else {
			placement_direction = 'v';
		}

		//randomly select an x and y pos and check if the space is empty
		if (placement_direction == 'v') {
			row = (rand() % (MAX_ROWS - ship_length + 1));
			col = rand() % (MAX_COLS - 1);

			for (int index = row; index < row + ship_length; index++){
				if (board[index][col] != EMPTY_MARKER){
					is_empty = 0;
				}
			}

		}
		else {
			row = rand() % (MAX_ROWS - 1);
			col = (rand() % (MAX_COLS - ship_length + 1));

			for (int index = col; index < col + ship_length; index++){
				if (board[row][index] != EMPTY_MARKER){
					is_empty = 0;
				}
			}
		}
	} while (is_empty == 0);

	//place the ship
	if (placement_direction == 'v') {
		for (int index = row; index < row + ship_length; index++)
		{
			board[index][col] = (char)ship_name;
		}
	}
	else {
		for (int index = col; index < col + ship_length; index++)
		{
			board[row][index] = (char)ship_name;
		}
	}
}

/*
Function: randomly_place_ships()
Date Created: 11.6.21
Date Last Modified:
Description: randomly places the ships on a board of characters
Input Parameters: a 2D array of characters for a game board, num rows, num columns, the active player
Returns: nothing
Preconditions: game board is initialized
Postconditions: the board has all ships randomly placed on it
*/
void randomly_place_all_ships(char board[][MAX_COLS], int num_rows, int num_cols) {

	//place carrier
	randomly_place_ship(board, MAX_ROWS, MAX_COLS, 5, CARRIER);

	//place battleship
	randomly_place_ship(board, MAX_ROWS, MAX_COLS, 4, BATTLESHIP);

	//place cusier
	randomly_place_ship(board, MAX_ROWS, MAX_COLS, 3, CRUISER);

	//place submarine
	randomly_place_ship(board, MAX_ROWS, MAX_COLS, 3, SUBMARINE);

	//place destroyer
	randomly_place_ship(board, MAX_ROWS, MAX_COLS, 2, DESTROYER);

}

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
void manually_place_ship(char board[][MAX_COLS], int num_rows, int num_cols, int ship_length, Ship_name ship_name) {

	char placement_direction = '\0';
	int row = -1, col = -1, rand_num = 0, is_empty = 1;

	//continue to loop untill an empty space is chosen
	do {
		//reset variables
		printf("\nEnter a valid placement.\n\n");
		is_empty = 1;

		//choose placement direction
		do {
			printf("Enter valid direction of the ship (h/v):");
			scanf(" %c", &placement_direction);
		} while (placement_direction != 'v' && placement_direction != 'h');

		//choose placement coordinates
		if (placement_direction == 'v') {
			do {
				printf("\nEnter valid coordinates.");
				printf("\nPlease enter the row number: ");
				scanf("%d", &row);
				printf("Please enter the column number: ");
				scanf("%d", &col);
			} while (row >= (MAX_ROWS - ship_length + 1) || col > 9);
		}
		else {
			do {
				printf("\nSet valid coordinates.");
				printf("\nPlease enter the row number: ");
				scanf("%d", &row);
				printf("Please enter the column number: ");
				scanf("%d", &col);
			} while (col >= (MAX_ROWS - ship_length + 1) || row > 9);
		}
		

		// check if space is empty
		if (placement_direction == 'v') {
			for (int index = row; index < row + ship_length; index++) {
				if (board[index][col] != EMPTY_MARKER) {
					is_empty = 0;
				}
			}

		}
		else {
			for (int index = col; index < col + ship_length; index++) {
				if (board[row][index] != EMPTY_MARKER) {
					is_empty = 0;
				}
			}
		}
	} while (is_empty == 0);

	//place the ship
	if (placement_direction == 'v') {
		for (int index = row; index < row + ship_length; index++)
		{
			board[index][col] = (char)ship_name;
		}
	}
	else {
		for (int index = col; index < col + ship_length; index++)
		{
			board[row][index] = (char)ship_name;
		}
	}
}

/*
Function: manually_place_all_ships(char board[][MAX_COLS], int num_rows, int num_cols)
Date Created: 11.6.21
Date Last Modified:
Description: a user manually places all ships on a game board
Input Parameters: a 2D array of characters for a game board, the number of rows, and the number of columns, the active player
Returns: nothing
Preconditions: game board is initialized
Postconditions: the board has all ships manually placed on it
*/
void manually_place_all_ships(char board[][MAX_COLS], int num_rows, int num_cols) {

	//place carrier
	print_player_board(board, MAX_ROWS, MAX_COLS);
	printf("\nPlease place your carrier...");
	manually_place_ship(board, MAX_ROWS, MAX_COLS, 5, 'c');
	system("cls");

	//place battleship
	print_player_board(board, MAX_ROWS, MAX_COLS);
	printf("\nPlease place your battleship...");
	manually_place_ship(board, MAX_ROWS, MAX_COLS, 4, 'b');
	system("cls");

	//place cusier
	print_player_board(board, MAX_ROWS, MAX_COLS);
	printf("\nPlease place your cuiser...");
	manually_place_ship(board, MAX_ROWS, MAX_COLS, 3, 'r');
	system("cls");

	//place submarine
	print_player_board(board, MAX_ROWS, MAX_COLS);
	printf("\nPlease place your submarine...");
	manually_place_ship(board, MAX_ROWS, MAX_COLS, 3, 's');
	system("cls");

	//place destroyer
	print_player_board(board, MAX_ROWS, MAX_COLS);
	printf("\nPlease place your destroyer...");
	manually_place_ship(board, MAX_ROWS, MAX_COLS, 2, 'd');
	system("cls");
	print_player_board(board, MAX_ROWS, MAX_COLS);
}

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
void print_player_board(char board[][MAX_COLS], int num_rows, int num_cols) {
	int row_index = 0, col_index = 0;
	
	printf("  0 1 2 3 4 5 6 7 8 9\n");
	for (; row_index < num_rows; ++row_index)
	{
		printf("%d ", row_index);
		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			printf("%c ", board[row_index][col_index]);
		}
		putchar('\n');
	}
}

/*
Function: print_enemy_board()
Date Created: 11.6.21
Date Last Modified:
Description: prints out the enemy's board, hiding the placement of ships
Input Parameters: a 2D array of characters for a player game board, number of rows, number of columns
Returns: nothing
Preconditions: enemy's board is initialized
Postconditions: the enemy's board is printed to the screen hiding the placement of their ships
*/
void print_enemy_board(char board[][MAX_COLS], int num_rows, int num_cols) {
	int row_index = 0, col_index = 0;

	printf("Your Opponent's Board\n");
	printf("  0 1 2 3 4 5 6 7 8 9\n");
	for (; row_index < num_rows; ++row_index)
	{
		printf("%d ", row_index);
		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			if ((board[row_index][col_index] == EMPTY_MARKER || board[row_index][col_index] == HIT_MARKER) || board[row_index][col_index] == MISS_MARKER) {
				printf("%c ", board[row_index][col_index]);
			}
			else {
				printf("%c ", EMPTY_MARKER);
			}
			
		}
		putchar('\n');
	}
}

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
Placement_style prompt_for_placement_style(void) {

	char answer = '\0';
	Placement_style placement = NONE;
	
	//prompts user
	do{
		printf("Would you like to manually place your ships? (y/n): ");
		scanf(" %c", &answer);
	} while (answer != 'y' && answer != 'n');
	

	switch (answer) {
	case 'y':
		placement = MANUAL;
		break;
	default:
		placement = RANDOM;
	}

	return placement;
}

/*
Function: select_first_player(void)
Date Created: 11.8.21
Date Last Modified:
Description: randomly selects the first player
Input Parameters: none
Returns: a Active_player data type which corresponds to the first player
Preconditions: none
Postconditions: none
*/
Active_player select_first_player(void) {

	Active_player start_player = NONE;
	int rand_num = 0;
	rand_num = rand() % 3;

	switch (rand_num) {
	case 1:
		start_player = PLAYER1;
	case 2:
		start_player = PLAYER2;
	}

	return start_player;
}

/*
Function: get_ship_status()
Date Created: 11.8.21
Date Last Modified:
Description: checks the board to see if the ship is still afloat
Input Parameters: a pointer to a 2d character array for the game baord, the number of rows and columns, and the ship to check for
Returns: the status of the ship (wheter it is sunk or afloat)
Preconditions: the board is initalized and the ships have been placed on it
Postconditions: none
*/

Ship_status get_ship_status(char board[MAX_ROWS][MAX_COLS], int rows, int cols, Ship_name ship) {
	Ship_status ship_status = SUNK;

	//runs through the board and checks if there is an instance of the ship
	for (int row_index = 0; row_index < MAX_ROWS; row_index++) {
		for (int col_index = 0; col_index < MAX_COLS; col_index++) {
			if (board[row_index][col_index] == (char)ship) {
				ship_status = AFLOAT;
			}
		}
	}

	return ship_status;
}

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
bool game_board_has_ships(char game_board[MAX_ROWS][MAX_COLS], int rows, int cols) {

	Ship_status fleet_status;

	if (get_ship_status(game_board, rows, cols, BATTLESHIP) == AFLOAT) {
		fleet_status = AFLOAT;
	}
	else if (get_ship_status(game_board, rows, cols, CARRIER) == AFLOAT) {
		fleet_status = AFLOAT;
	}
	else if (get_ship_status(game_board, rows, cols, SUBMARINE) == AFLOAT) {
		fleet_status = AFLOAT;
	}
	else if (get_ship_status(game_board, rows, cols, CRUISER) == AFLOAT) {
		fleet_status = AFLOAT;
	}
	else if (get_ship_status(game_board, rows, cols, DESTROYER) == AFLOAT) {
		fleet_status = AFLOAT;
	}
	else {
		fleet_status = SUNK;
	}

	if (fleet_status == AFLOAT) {
		return true;
	}
	else {
		return false;
	}
}

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
void prompt_for_shot(int board_rows, int board_cols, int* target_row_ptr, int* target_col_ptr) {
	
	int target_r = -1, target_c = -1;
	
	do {
		printf("Enter a valid location to shoot\n");
		printf("Enter row: ");
		scanf("%d", &target_r);
		printf("Enter column: ");
		scanf("%d", &target_c);
	} while ((target_r < 0 || target_r > board_rows)||(target_c < 0 || target_c > board_cols));

	*target_row_ptr = target_r;
	*target_col_ptr = target_c;
}

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
Shot_status can_take_shot(char game_board[MAX_ROWS][MAX_COLS], int num_rows, int num_cols, int target_row, int target_col) {
	Shot_status target_shot_status = EMPTY;
	char target_location_char = game_board[target_row][target_col];

	if (target_location_char == HIT_MARKER) {
		target_shot_status = HIT;
	}
	else if (target_location_char == MISS_MARKER) {
		target_shot_status = MISS;
	}

	return target_shot_status;
}

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
void take_and_check_shot(char game_board[MAX_ROWS][MAX_COLS], int target_row, int target_col, Shot_status* hit_or_miss_ptr, Ship_name* hit_ship_ptr) {

	char target_location_char = game_board[target_row][target_col];

	if (target_location_char == EMPTY_MARKER) {
		game_board[target_row][target_col] = MISS_MARKER;
		*hit_or_miss_ptr = MISS;
		*hit_ship_ptr = SHIP_NONE;
	}
	else {
		game_board[target_row][target_col] = HIT_MARKER;
		*hit_or_miss_ptr = HIT;
		*hit_ship_ptr = (Ship_name)target_location_char;
	}

}

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

void print_player_stats(Stats* player_ptr, FILE* outfile_ptr) {

	fprintf(outfile_ptr, "Number Hits: %d\n", player_ptr->total_hits);
	fprintf(outfile_ptr, "Number Misses: %d\n", player_ptr->total_misses);
	fprintf(outfile_ptr, "Total Shots: %d\n", player_ptr->total_shots);
	player_ptr->hit_to_misses_ratio = ((double)player_ptr->total_hits / player_ptr->total_misses) * 100;
	fprintf(outfile_ptr, "Hit/Miss Ratio: %%%d\n", (int)(player_ptr->hit_to_misses_ratio));


}

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
void print_winner_to_log(FILE* log, char game_board[MAX_ROWS][MAX_COLS]) {
	if (game_board_has_ships(game_board, MAX_ROWS, MAX_COLS)) {
		fprintf(log, "\n\nPlayer 1 wins! Player 2 loses.\n");
	}
	else {
		fprintf(log, "\n\nPlayer 1 wins! Player 2 loses.\n");
	}
}