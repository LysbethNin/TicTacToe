#include "tictactoe.h"
#include <iostream>
#include <string>

#define MAX_LINE 3
#define MAX_COLS 3


/**
* @brief Tableau à deux dimensions pour représenter le plateau
*/
static char board[MAX_LINE][MAX_COLS] = {
	{
		0,
	},
};
/**
* @brief Représentation des pions 
*/
static const char players[2] = { 'X', 'O'};

/**
* @brief Total de pions indifféremment pouvant etre posés
*/
static int maxPions = sizeof(board) / sizeof(board[0][0]);

/**
 * @brief Affiche le plateau de jeu 
 */
static void displayBoard() {

	std::cout << "     |     |      \n";
	for (int i = 0; i < MAX_LINE; i++) {
		for (int j = 0; j < MAX_COLS; j++) {
			if (j == MAX_COLS - 1) {
				std::cout << "   " << board[i][j] << "  ";
			}
			else {
				std::cout << "  " << board[i][j] << "  |";
			}
		}
		
		std::cout << "\n";
		if (i < MAX_LINE - 1)
			std::cout << "_____|_____|_____ \n";
		std::cout << "     |     |      \n";
		
	}
	std::cout << "\n";
	
}

/**
 * @brief Initialise le plateau avec un espace vide.
 */
static void initBoard() {
	for (int i = 0; i < MAX_LINE; i++) {
		for (int j = 0; j < MAX_COLS; j++) {
			board[i][j] = ' ';
		}
	}
}

/**
 * @brief Vérifie si winner
 *
 * @param ligne Indice de la ligne de départ.
 * @param colonne Indice de la colonne de départ.
 * @param pasLigne Direction en ligne.
 * @param pasColonne Direction en colonne.
 * @param pion Symbole du pion.
 * @return bool 
 */
static bool checkWin(char players, int row, int col, int rowDelta, int colDelta, int count) {
	if (count == 3)
		return true;

	if (row < 0 || row > 2 || col < 0 || col > 2) {
		return false;
	}

	if (board[row][col] != players) {
		return false;
	}

	return checkWin(players, row + rowDelta, col + colDelta, rowDelta, colDelta, count + 1);
}
/**
 * @brief Verifie si winner par colonne , ligne et diagonale
 *
 * @param players Joueur en cours
 * @return bool 
 */
static bool isWinner(char players) {
	// Check rows
	for (int i = 0; i < 3; i++) {
		if (checkWin(players, i, 0, 0, 1, 0)) {
			return true;
		}
	}
	// Check columns
	for (int i = 0; i < 3; i++) {
		if (checkWin(players, 0, i, 1, 0, 0)) {
			return true;
		}
	}
	// Check diagonals
	if (checkWin(players, 0, 0, 1, 1, 0)) {
		return true;
	}
	if (checkWin(players, 0, 2, 1, -1, 0)) {
		return true;
	}
	return false;
}

/**
 * @brief Choix d'une position par l'utilisateur
 *
 * @param players Joueurs en cours 
 * @param msg Affiche à l'utilisateur si on lui demande la ligne ou la colonne
 * @return int la position choisie
 */
static int pickPosition(char players, std::string msg) {

	int value = 0;
	do {
		std::cout << "Player " << players << ", enter a " << msg;
		std::cin >> value;
		if (std::cin.fail()) { // check if the input was invalid
			std::cin.clear(); // clear the input buffer
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any remaining characters
			std::cout << "Invalid input. Please enter a number between 0 and 2." << std::endl;
		}
	} while (value < 0 || value > 2);

	return value;
}

/**
 * @brief Représentation d'un tour de jeu pour un joueur
 * Choix d'une position, placage du pion, décrémentation du nombre de coups 
 *
 * @param players Joueur actuel
 * @return void
 */
static void takeTurn(char players) {
	int row, col;
	row = pickPosition(players, "row (0-2): ");
	col = pickPosition(players, "column (0-2): ");
	

	if (board[row][col] != ' ') {
		std::cout << "This position is already used. Try again.";
		takeTurn(players);
	}

	board[row][col] = players;
	maxPions--;
	
}

/**
 * @brief Vérifie si le jeu n'est pas terminé en checkant le nombre de coups total restant.
 * @return bool
 */
static bool isFinished() {

	return (0 == maxPions);
}

/**
 * @brief Engine du jeu 
 * @return void
 */
void playGame()
{
	int indicePion = 0;
	std::cout << "Welcome on Tic Tac Toe\n";
	std::cout << "Here the grid : \n\n";

	initBoard();
	displayBoard();

	while (!isFinished()) {
		
		takeTurn(players[indicePion]);
		displayBoard();
		if (isWinner(players[indicePion])) {
			std::cout << "Congratulations" << players[indicePion] << "! You win !";
			return;
		}
		if (++indicePion > 1)
			indicePion = 0;
	}
	std::cout << "Tie game :( You suck ";
}
