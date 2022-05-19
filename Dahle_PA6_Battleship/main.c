#include "Battleship.h"

/*
Dev Notes:

//! Have to debug to make sure the stats prints out properly

11.6.21
	Added the functions Andy showed us in class
		init_board()
		print_player_board()

	Also added and debbuged
		print_enemy_board()
		randomly_place_ship()
		randomly_place_all_ships()

	Also added, may need more debugging
		manually_place_ship()
		manually_place_all_ships()

11.8.21
	Added and lightly debugged
		prompt_for_placement_style()
		select_first_player()

		//likely need more debugging
		get_ship_status()
		game_board_has_ships()


	Also added the following enumerated types
		Placement_style
		Active_player
		Ship_name
		Ship_status

11.9.21
	Added and debugged
		prompt_for_shot()
		can_take_shot()
		take_and_check_shot()
	Player can now take shots at opponent's ships and sink them. The player's turn should be completely set up except for printing to log.
	Also, still need to check if game ends when all ships are sunk

	Added log for player shots

	Set up computer's turn
	Played through a game to make sure everyting worked and it ran properly

	Still need
	- Printing Rules
	- Declaring a winner
	- player stats (added but needs to be checked)

11.12.21
	Added
	- Declaring a winner
	- checked stats
	- fixed randomly choosing a player to start
	- added printing rules
*/

int main(void){

	//prints welcome screen
	int user_choice = -1;
	
	while (user_choice != EXIT) {
		
		user_choice = -1;
		
		do {
			user_choice = print_welcome_screen();
			if (user_choice == RULES) {
				print_rules();
				system("pause");
				system("cls");
			}			
		} while (user_choice == RULES);

		if (user_choice == EXIT) {
			break;
		}

		srand((unsigned int)time(NULL));

		//player stats
		Stats player1 = { 0,0,0,0.0 };
		Stats player2 = { 0,0,0,0.0 };

		Placement_style player_one_placement;
		Placement_style player_two_placement;
		Active_player current_player = NONE;

		//set up player boards
		char player_one_game_board[MAX_ROWS][MAX_COLS];
		char player_two_game_board[MAX_ROWS][MAX_COLS];

		//initalize boards
		init_board(player_one_game_board, MAX_ROWS, MAX_COLS);
		init_board(player_two_game_board, MAX_ROWS, MAX_COLS);

		//variables for targeting
		int target_row = -1, target_col = -1;
		Shot_status target_status;
		Ship_name hit_ship = SHIP_NONE;

		current_player = PLAYER1;
		printf("Player 1\n");

		//Player1 can choose to manually/randomly place board
		player_one_placement = prompt_for_placement_style();

		
		//places user ships the requested way
		switch (player_one_placement) {
		case MANUAL:
			manually_place_all_ships(player_one_game_board, MAX_ROWS, MAX_COLS);
			break;
		case RANDOM:
			randomly_place_all_ships(player_one_game_board, MAX_ROWS, MAX_COLS);
			printf("\nYour ships have been placed.\n");
			print_player_board(player_one_game_board, MAX_ROWS, MAX_COLS);
			break;
		}



		if (user_choice == PLAYERvPLAYER) {
			current_player = PLAYER2;
			
			//clear the screen
			printf("Time for the other player to place their ships.\n");
			system("pause");
			system("cls");

			printf("Player 2\n");

			//Player1 can choose to manually/randomly place board
			player_two_placement = prompt_for_placement_style();

			//places user ships the requested way
			switch (player_two_placement) {
			case MANUAL:
				manually_place_all_ships(player_two_game_board, MAX_ROWS, MAX_COLS);
				break;
			case RANDOM:
				randomly_place_all_ships(player_two_game_board, MAX_ROWS, MAX_COLS);
				printf("\nYour ships have been placed.\n");
				print_player_board(player_two_game_board, MAX_ROWS, MAX_COLS);
				break;
			}
		}

		system("pause");
		system("cls");

		if (user_choice == PLAYERvCOMPUTER) {
			//randomly place computer's ships
			printf("Generating the Computer's Board...\n");
			randomly_place_all_ships(player_two_game_board, MAX_ROWS, MAX_COLS);
			system("pause");
			system("cls");
		}

		//clear the screen
		system("pause");
		system("cls");

		char (*current_player_board)[MAX_COLS] = player_one_game_board;
		char (*enemy_board)[MAX_COLS] = player_two_game_board;

		current_player = PLAYER1;

		while (game_board_has_ships(player_one_game_board, MAX_ROWS, MAX_COLS) && game_board_has_ships(player_two_game_board, MAX_ROWS, MAX_COLS)) {	
			
			
			//print current player to battleship.log
			if (current_player == PLAYER1) {
				printf("Player 1's Turn\n");
			}
			else if (user_choice == PLAYERvPLAYER) {
				printf("Player 2's Turn\n");
			}
			else {
				printf("Computer's Turn\n");
				printf("Your Board\n");
			}
			
			if (user_choice == PLAYERvPLAYER || (user_choice == PLAYERvCOMPUTER && current_player == PLAYER1)) {

				if (user_choice == PLAYERvPLAYER) {

					//prints out the player's board
					printf("Your board\n");
					print_player_board(*current_player_board, MAX_ROWS, MAX_COLS);
					printf("\n");
				}

				//print enemy board
				print_enemy_board(*enemy_board, MAX_ROWS, MAX_COLS);

				//prompt for shot and make sure the spot has not been targeted before
				do {
					prompt_for_shot(MAX_ROWS, MAX_COLS, &target_row, &target_col);
					target_status = can_take_shot(*enemy_board, MAX_ROWS, MAX_COLS, target_row, target_col);
				} while (target_status != EMPTY);

				//check if hit or miss, update game board, and what ship was hit
				take_and_check_shot(*enemy_board, target_row, target_col, &target_status, &hit_ship);


				//clear screen
				system("pause");
				system("cls");

				//print out computer board
				print_enemy_board(*enemy_board, MAX_ROWS, MAX_COLS);

				//print the location of the shot
				printf("You shot at row %d, col %d\n", target_row, target_col);
			}			
			else if (current_player == PLAYER2 && user_choice == PLAYERvCOMPUTER) {
				//randomize shot and make sure the spot has not been targeted before
				do {
					target_row = rand() % 10;
					target_col = rand() % 10;
					target_status = can_take_shot(*enemy_board, MAX_ROWS, MAX_COLS, target_row, target_col);
				} while (target_status != EMPTY);

				//check if hit or miss, update game board, and what ship was hit
				take_and_check_shot(*enemy_board, target_row, target_col, &target_status, &hit_ship);

				//print out player's board
				print_player_board(*enemy_board, MAX_ROWS, MAX_COLS);

				//print the location of the shot
				printf("Enemy shot at row %d, col %d\n", target_row, target_col);
			}

			//print text indicating if you hit or missed the target
			switch (target_status) {
			case HIT:
				printf("Hit one of you opponent's ships!\n");

				if (current_player == PLAYER1) {
					player1.total_hits++;
					player1.total_shots++;
				}
				else {
					player2.total_hits++;
					player2.total_shots++;
				}
				
				break;
			case MISS:
				printf("Missed\n");

				if (current_player == PLAYER1) {
					player1.total_misses++;
					player1.total_shots++;
				}
				else {
					player2.total_misses++;
					player2.total_shots++;
				}
				
			}

			// check if ship is sunk
			if (SUNK == get_ship_status(*enemy_board, MAX_ROWS, MAX_COLS, hit_ship)) {
				switch (hit_ship) {
				case BATTLESHIP:
					printf("Sunk your opponents battleship!\n");
					break;
				case CRUISER:
					printf("Sunk your opponents cruiser!\n");
					break;
				case CARRIER:
					printf("Sunk your opponents carrier!\n");
					break;
				case SUBMARINE:
					printf("Sunk your opponents submarine!\n");
					break;
				case DESTROYER:
					printf("Sunk your opponents destroyer!\n");
					break;
				}

			}

			//switch player
			system("pause");
			system("cls");
			printf("Changing Players\n");
			system("pause");
			system("cls");

			if (current_player == PLAYER1) {
				current_player = PLAYER2;
				current_player_board = player_two_game_board;
				enemy_board = player_one_game_board;
			}
			else {
				current_player = PLAYER1;
				current_player_board = player_one_game_board;
				enemy_board = player_two_game_board;
			}			
		}		

		//declaring the winner

		printf("THE WINNER IS... ");

		if (game_board_has_ships(player_one_game_board, MAX_ROWS, MAX_COLS)) {
			printf("PLAYER 1!!!!\n");
		}
		else if(user_choice == PLAYERvPLAYER) {
			printf("PLAYER 2!!!\n");
		}
		else {
			printf("THE COMPUTER!!!\n");
		}

		printf("\n*** Player1 Stats***\n");
		print_player_stats(&player1);
		printf("\n*** Player2 Stats***\n");
		print_player_stats(&player2);
	}

	return 0;
}