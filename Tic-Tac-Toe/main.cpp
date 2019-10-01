#include <iostream>
#include <string>

//Game board
std::string board[3][3];

//Will be 1 for single player or 2 for two player
int gameType;

//Current symbol being printed.
std::string currentPlayer;

//If this = 1 the game ends
int endcond;

//equals 1 if player goes first 2 if player goes second
int fOrs;

int cont;

/**
 * game initializer
 */
void initializegame(){
	for(int i=0; i<3; i++){
		board[i][0] = "   ";
		board[i][1] = "   ";
		board[i][2] = "   ";
	}
	currentPlayer = " X ";
	endcond = 0;
	cont = 0;
	gameType = 0;
}

/**
 * Method prints out the current state of the game board;
 */
void printboard(){

	for(int i=0; i<3; i++){

		std::cout << board[i][0] << '|' << board[i][1] << '|' << board[i][2] << std::endl;

	}
}


/**
 * Checks if player has an entire column secured
 * @return 1 if yes, 0 if no
 */
int columns(){

	for(int i=0; i<3; i++){

		if(board[0][i] != "   " &&
		   board[0][i] == board[1][i] &&
		   board[0][i] == board[2][i]){

			return 1;

		}

	}

	return 0;
}

/**
 * Checks if player has an entire row secured
 * @return 1 if yes, 0 if no
 */
int rows(){

	for(int i=0; i<3; i++){

		if(board[i][0] != "   " &&
			board[i][0] == board[i][1] &&
			board[i][0] == board[i][2]){

			return 1;

		}

	}

	return 0;
}

/**
 * Checks if player has an entire diagonal secured
 * @return 1 if yes, 0 if no
 */
int diagonals(){

	if(board[0][0] != "   " &&
	   board[0][0] == board[1][1] &&
	   board[0][0] == board[2][2]){

		return 1;

	}else if(board[0][2] != "   " &&
	         board[0][2]==board[1][1] &&
	         board[0][2] == board[2][0]){

		return 1;

	}

	return 0;
}

/**
 * Checks all win conditions
 *
 * @return 1 if a player achived a win condition, 0 otherwise
 */
int haswon(){

	if(columns() ||
		rows() ||
		diagonals()){

		endcond = 1;

	}

	return endcond;
}



/**
 * Checks to see if board is full with no winner;
 * @return 0 if not Cat's Game, 2 if Cat's Game
 */
int catsgame(){

	int cat(0);

	for(int i=0; i<3; i++){

		for(int j=0; j<3; j++){

			if(board[i][j]!="   "){

				cat++;

			}

		}

	}

	if(cat==9){

		endcond = 2;

	}

	return endcond;
}

/**
 * Swaps the icon to the current player
 */
void swapplayer(){

	if(currentPlayer == " X "){

		currentPlayer = " O ";

	}else{

		currentPlayer = " X ";

	}

}

/**
 * Checks to see if the current move is valid, if so the move is executed
 * @param x x-coordinate
 * @param y y-coordinate
 * @return 0 if move failed, 1 if move passed
 */
int makemove(int x, int y, int pOc){

	if(board[x][y] == "   "){

		board[x][y] = currentPlayer;
		return 1;

	}else if(pOc){

		std::cout << "Position Invalid. Enter Valid Position" <<std::endl;
		return 0;

	}
	return 0;

}

/**
 * Produces a random move.
 * Could be replaced with an algorithm but an algorithm is so predictable it makes for a boring game
 * With random numbers it spices it up
 */
void compmove(){

	int x, y, corner(0);

	do{

		if(corner < 2 && makemove(0,0,0)){
				x = 0;
				y = 0;
				++corner;
		}else if(corner < 2 && makemove(2,0,0)){
				x = 2;
				y = 0;
				++corner;
		}else if(corner < 2 && makemove(0,2,0)){
			x = 0;
			y = 2;
			++corner;
		}else if(corner < 2 && makemove(2,2,0)){
			x = 2;
			y = 2;
			++corner;
		}else{
			x = std::rand() % 3;
			y = std::rand() % 3;
		}


	}while(!makemove(x,y, 0));

	swapplayer();
}

/**
 * Single player logis
 */
void singleplayer(){

	int x,y;
	printboard();
	std::cout << "Would you like to go first (1) or second (2)?" << std::endl;
	std::cin >> fOrs;

	do{
		if(fOrs==1){

			printboard();
			std::cout << "Your Turn!\nEnter position 'x y'" << std::endl;

			do{

				std::cin >> x >> y;

			}while(!makemove(x,y, 1));

			swapplayer();
			fOrs = 2;

		}else{

			compmove();
			fOrs = 1;

		}

	}while(!haswon() && !catsgame() );

}

/**
 * Logic for a 2 player game
 */
void twoplayer(){

	int x, y;

	do {

		printboard();
		std::cout << currentPlayer << "turn.\nEnter position 'x y'" << std::endl;

		do {

			std::cin >> x >> y;

		} while (!makemove(x, y, 1));

		swapplayer();

	}while(!haswon() && !catsgame());

}



/**
 * main method
 * How to run:
 * 	Step 1:
 * 		make Tic-Tac-Toe-CL your current directory
 * 	Step 2:
 * 		g++ -std=c++14 main.cpp -o tictactoe
 * 	Step 3:
 * 		./tictactoe
 * @return 0 if ran correctly
 */
int main() {



	std::cout << "WELCOME TO TIC-TAC-TOE" << std::endl;
	std::cout << "This terminal game was made by Michael Spagna" << std::endl;
	do {
		while (gameType != 1 && gameType != 2) {

			std::cout << "Enter 1 for single player or 2 for two player" << std::endl;
			std::cin >> gameType;
		}
		initializegame();
		if (gameType == 1) {

			singleplayer();

		} else if (gameType == 2) {

			twoplayer();

		}

		if (endcond == 1) {

			swapplayer();
			printboard();
			std::cout << currentPlayer << "WINS!!!!" << std::endl;

		} else {

			printboard();
			std::cout << "CAT'S GAME." << std::endl;

		}
		std::cout << "Press 1 to play again or 0 to exit" << std::endl;
		std::cin >> cont;
	}while(cont!=0);

	return 0;
}