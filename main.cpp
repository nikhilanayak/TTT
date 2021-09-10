#include <iostream>
#include <limits>

// booleans for keeping track of which turn it is and the state of a cell in the board
#define X 0
#define O 1
#define EMPTY 2

#define O_WIN 2

#define B_SIZE 3
typedef char board[B_SIZE][B_SIZE];

typedef struct{ // keeps track of the game state
	board game_board;
	bool running;	
	int winner;
	bool current_player;
} game;

const int* win_conditions[] = { // all rows and columns in a 3x3 board
	(int[]){0, 1, 2},
	(int[]){3, 4, 5},
	(int[]){6, 7, 8},
	(int[]){0, 3, 6},
	(int[]){1, 4, 7},
	(int[]){2, 5, 8},
	(int[]){0, 4, 8},
	(int[]){2, 4, 6}
};

const int num_winconds = 8; // = len(win_conditions)

bool game_over(game* game, int* x_points, int* o_points){ // returns true, adds to x/o_points, and prints if game is over, otherwise just retuns false
	int full = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(game->game_board[i][j] != EMPTY){
				full += 1;
			}
		}
	}
	// checks if all 9 cells are filled

	if(full == 9){
		std::cout << "Tie\n";
		return true;
	}


	for(int i = 0; i < num_winconds; i++){ // iterates through all 8 win conditions and sees if any are done
		int first = win_conditions[i][0];
		int second = win_conditions[i][1];
		int third = win_conditions[i][2];
	
		if(game->game_board[first % 3][first / 3] == game->game_board[second % 3][second/3] && game->game_board[second % 3][second/3]== game->game_board[third % 3][third/3]){
			if(game->game_board[first % 3][first / 3] != EMPTY){
				const int winner = game->game_board[first % 3][first / 3];
//				std::cout << first << ", " << second << ", " << third << "\n";
				if(winner == O){
					std::cout << "\n\n\n";
					std::cout << "O Wins!\n";
					(*o_points)++;
				}
				else{
					std::cout << "\n\n\n";
					std::cout << "X Wins!\n";
					(*x_points)++;
				}
				return true;
			}
		}
	}
	return false;
}


void print_cell(char cell){ // prints the value of a cell in the game board
	if(cell == X){
		std::cout << "x";
	}
	else if(cell == O){
		std::cout << "o";
	}
	else{
		std::cout << "_";
	}
}
void print_board(game* game){ // formats and prints the board to the screen
	std::cout << "  1 2 3\n";
	for(int y = 0; y < B_SIZE; y++){
		std::cout << (char)('a' + y) << " ";
		for(int x = 0; x < B_SIZE; x++){
			print_cell(game->game_board[x][y]);
			std::cout << " ";
		}
		std::cout << "\n";
	}
}

void take_turn(game* game){ // gets input from the user, validates, and changes the board accordingly
	int pos = 0;
	if(game->current_player == X){
		std::cout << "X's turn, ";
	}
	else{
		std::cout << "O's turn, ";
	}
	std::cout << "Select a position(like 'a1')";
	
	char input[2048];
	std::cin.getline(input, 2048, '\n');
	if(input[0] < 'a' || input[0] > 'c'){
		return take_turn(game);
	}

	if(input[1] < '1' || input[1] > '3'){
		return take_turn(game);
	}
	int y = input[0] - 'a';
	int x = input[1] - '1';
	// std::cout << x << ", " << y << "\n";


	if(game->game_board[x][y] != EMPTY){
		std::cout << "This space is already taken.\n";
		return take_turn(game);
	}
	
	game->game_board[x][y] = game->current_player;

	game->current_player = !game->current_player; // next player's turn
}



int main(){
	// stores the game scores for x and o
	int x_points = 0;
	int o_points = 0;
	while(true){
		game g;
		g.current_player = X;
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				g.game_board[i][j] = EMPTY; // initializes the board (could also just memset EMPTY)


		print_board(&g);
		while(true){
			take_turn(&g);
			print_board(&g);
			if(game_over(&g, &x_points, &o_points)){
				std::cout << "Score -> X: " << x_points << ", Y: " << o_points << "\n";
				break;
			}
		}
	}

	
}
