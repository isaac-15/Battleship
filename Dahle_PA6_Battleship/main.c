#include "Battleship.h"

/*
Dev Notes:

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
	
	//open the battleship.log file
	FILE* battleship_log = fopen("battleship.log", "w");

	//prints welcome screen
	int user_choice = -1;
	user_choice = print_welcome_screen();
	while (user_choice != EXIT) {

		if (user_choice == RULES) {
			print_rules();
			system("pause");
			system("cls");
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

		if (user_choice == PLAYERvCOMPUTER) {
			//randomly place computer's ships
			printf("Generating the Computer's Board...\n");
			randomly_place_all_ships(player_two_game_board, MAX_ROWS, MAX_COLS);
		}

		//randomly select the player to go first
		current_player = select_first_player();
		if (current_player == PLAYER1) {
			printf("Player 1 is going first.\n");
		}
		else {
			printf("Player 2 is going first.\n");
		}

		//clear the screen
		system("pause");
		system("cls");

		while (game_board_has_ships(player_one_game_board, MAX_ROWS, MAX_COLS) && game_board_has_ships(player_two_game_board, MAX_ROWS, MAX_COLS)) {
			if (current_player == PLAYER1) {
				
				//print current player to battleship.log
				fprintf(battleship_log, "\nPlayer 1's Turn: ");
				printf("Player 1's Turn\n");

				//print enemy board
				print_enemy_board(player_two_game_board, MAX_ROWS, MAX_COLS);

				//prompt for shot and make sure the spot has not been targeted before
				do {
					prompt_for_shot(MAX_ROWS, MAX_COLS, &target_row, &target_col);
					target_status = can_take_shot(player_two_game_board, MAX_ROWS, MAX_COLS, target_row, target_col);
				} while (target_status != EMPTY);

				//check if hit or miss, update game board, and what ship was hit
				take_and_check_shot(player_two_game_board, target_row, target_col, &target_status, &hit_ship);

				//clear screen
				system("pause");
				system("cls");

				//print out computer board
				print_enemy_board(player_two_game_board, MAX_ROWS, MAX_COLS);

				//print the location of the shot
				printf("You shot at row %d, col %d\n", target_row, target_col);
				fprintf(battleship_log, " %d, %d ", target_row, target_col);

				//print text indicating if you hit or missed the target
				switch (target_status) {
				case HIT:
					printf("You hit one of you opponent's ships!\n");
					fprintf(battleship_log, "\"hit\" ");
					player1.total_hits++;
					player1.total_shots++;
					break;
				case MISS:
					printf("You missed\n");
					fprintf(battleship_log, "\"miss\"");
					player1.total_misses++;
					player1.total_shots++;
				}

				// check if ship is sunk
				if (SUNK == get_ship_status(player_two_game_board, MAX_ROWS, MAX_COLS, hit_ship)) {
					switch (hit_ship) {
					case BATTLESHIP:
						printf("You sunk your opponents battleship!\n");
						fprintf(battleship_log, "Sunk Battleship!");
						break;
					case CRUISER:
						printf("You sunk your opponents cruiser!\n");
						fprintf(battleship_log, "Sunk Cruiser!");
						break;
					case CARRIER:
						printf("You sunk your opponents carrier!\n");
						fprintf(battleship_log, "Sunk Carrier!");
						break;
					case SUBMARINE:
						printf("You sunk your opponents submarine!\n");
						fprintf(battleship_log, "Sunk Submarine!");
						break;
					case DESTROYER:
						printf("You sunk your opponents destroyer!\n");
						fprintf(battleship_log, "Sunk Destroyer!");
						break;
					}

				}

				//switch player
				system("pause");
				system("cls");
				printf("Changing Players\n");
				system("pause");
				system("cls");

				current_player = PLAYER2; //commented out for testing the player's turn
			}
			else if (current_player == PLAYER2 && user_choice == PLAYERvPLAYER) {
				//print current player to battleship.log
				fprintf(battleship_log, "\nPlayer 2's Turn: ");
				printf("Player 2's Turn\n");

				//print enemy board
				print_enemy_board(player_one_game_board, MAX_ROWS, MAX_COLS);

				//prompt for shot and make sure the spot has not been targeted before
				do {
					prompt_for_shot(MAX_ROWS, MAX_COLS, &target_row, &target_col);
					target_status = can_take_shot(player_one_game_board, MAX_ROWS, MAX_COLS, target_row, target_col);
				} while (target_status != EMPTY);

				//check if hit or miss, update game board, and what ship was hit
				take_and_check_shot(player_one_game_board, target_row, target_col, &target_status, &hit_ship);

				//clear screen
				system("pause");
				system("cls");

				//print out computer board
				print_enemy_board(player_one_game_board, MAX_ROWS, MAX_COLS);

				//print the location of the shot
				printf("You shot at row %d, col %d\n", target_row, target_col);
				fprintf(battleship_log, " %d, %d ", target_row, target_col);

				//print text indicating if you hit or missed the target
				switch (target_status) {
				case HIT:
					printf("You hit one of you opponent's ships!\n");
					fprintf(battleship_log, "\"hit\" ");
					player1.total_hits++;
					player1.total_shots++;
					break;
				case MISS:
					printf("You missed\n");
					fprintf(battleship_log, "\"miss\"");
					player1.total_misses++;
					player1.total_shots++;
				}

				// check if ship is sunk
				if (SUNK == get_ship_status(player_one_game_board, MAX_ROWS, MAX_COLS, hit_ship)) {
					switch (hit_ship) {
					case BATTLESHIP:
						printf("You sunk your opponents battleship!\n");
						fprintf(battleship_log, "Sunk Battleship!");
						break;
					case CRUISER:
						printf("You sunk your opponents cruiser!\n");
						fprintf(battleship_log, "Sunk Cruiser!");
						break;
					case CARRIER:
						printf("You sunk your opponents carrier!\n");
						fprintf(battleship_log, "Sunk Carrier!");
						break;
					case SUBMARINE:
						printf("You sunk your opponents submarine!\n");
						fprintf(battleship_log, "Sunk Submarine!");
						break;
					case DESTROYER:
						printf("You sunk your opponents destroyer!\n");
						fprintf(battleship_log, "Sunk Destroyer!");
						break;
					}

				}

				//switch player
				system("pause");
				system("cls");
				printf("Changing Players\n");
				system("pause");
				system("cls");

				current_player = PLAYER1; //commented out for testing the player's turn
			}
			else {
				//print current player to battleship.log
				fprintf(battleship_log, "\nComputer's Turn:\n");
				printf("Computer's Turn");

				//randomize shot and make sure the spot has not been targeted before
				do {
					target_row = rand() % 10;
					target_col = rand() % 10;
					target_status = can_take_shot(player_one_game_board, MAX_ROWS, MAX_COLS, target_row, target_col);
				} while (target_status != EMPTY);

				//check if hit or miss, update game board, and what ship was hit
				take_and_check_shot(player_one_game_board, target_row, target_col, &target_status, &hit_ship);

				//print out computer board
				print_player_board(player_one_game_board, MAX_ROWS, MAX_COLS);

				//print the location of the shot
				printf("Enemy shot at row %d, col %d\n", target_row, target_col);
				fprintf(battleship_log, " %d, %d ", target_row, target_col);

				//print text indicating if you hit or missed the target
				switch (target_status) {
				case HIT:
					printf("Enemy hit one of your ships!\n");
					fprintf(battleship_log, "\"hit\" ");
					player2.total_hits++;
					player2.total_shots++;
					break;
				case MISS:
					printf("Enemy missed\n");
					fprintf(battleship_log, "\"miss\"");
					player2.total_misses++;
					player2.total_shots++;
				}

				// check if ship is sunk
				if (SUNK == get_ship_status(player_one_game_board, MAX_ROWS, MAX_COLS, hit_ship)) {
					switch (hit_ship) {
					case BATTLESHIP:
						printf("The enemy sunk your battleship!\n");
						fprintf(battleship_log, "Sunk Battleship!");
						break;
					case CRUISER:
						printf("The enemy sunk your cruiser!\n");
						fprintf(battleship_log, "Sunk Cruiser!");
						break;
					case CARRIER:
						printf("The enemy sunk your carrier!\n");
						fprintf(battleship_log, "Sunk Carrier!");
						break;
					case SUBMARINE:
						printf("The enemy sunk your submarine!\n");
						fprintf(battleship_log, "Sunk Submarine!");
						break;
					case DESTROYER:
						printf("The enemy sunk your destroyer!\n");
						fprintf(battleship_log, "Sunk Destroyer!");
						break;
					}

				}


				//switch player

				printf("Changing Players\n");
				system("pause");
				system("cls");

				current_player = PLAYER1;
			}
		}

		print_winner_to_log(battleship_log, player_one_game_board);

		fprintf(battleship_log, "\n*** Player1 Stats***\n");
		print_player_stats(&player1, battleship_log);
		fprintf(battleship_log, "\n*** Player2 Stats***\n");
		print_player_stats(&player2, battleship_log);

		printf("\nStats successfuly printed to log file!\n");

	}

	
	



	fclose(battleship_log);
	return 0;
}