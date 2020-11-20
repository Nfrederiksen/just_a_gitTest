#include <iostream>
#include "hangman.h"

using namespace std;


void message2() {
	cout << "****************************************" << endl;
	cout << " Nice Job! (/^ ^)/ You Got it! You Win!" << endl;
	cout << "****************************************" << endl;
}

void message1() {
	cout << "-------------------" << endl;
	cout << " Getting closer..." << endl;
	cout << "-------------------" << endl;
}

void message3() {
	cout << "=========================================" << endl;
	cout << " Sorry Bro, One step closer to death :(" << endl;
	cout << "=========================================" << endl;
}

void init_game_state(char* gameState, int size);
void ask_for_input(char* g_letter);
bool player_guessed_this_before(char* g_arr, int* g_counter, char* g_letter);
void update_guessed_array(char* g_arr, char* g_letter, int* g_counter);
void update_game_state(char *gameState, char *theWord, char* g_letter, int size, int *rounds, bool* sheWon);
bool does_player_have_the_word(char* gameState, char* theWord, int size);
void printGameState(char* gameState, int size, int *rounds);


int main() {
	// ==============================
	// Declare and init. Variables!
	// ==============================
	// Start of with 10 rounds.
	bool* sheWon = new bool(false);
	int *rounds = new int(10);
	// Select the secret word.
	char* g_letter = new char(' ');
	int size = 8;
	char* theWord = new char[size] {'s', 'o', 'l', 'u','t','i','o','n'};
	// Guessed Letters Array.
	char *g_arr = new char[100];
	// Guess Counter.
	int *g_counter = new int(0);
	// Game State Array.
	char *gameState = new char[size];

	cout << " LET'S PLAY HANGMAN!" << endl;
	// Initialize empty g-state.
	init_game_state(gameState, size);
	// Print the Game State.
	printGameState(gameState, size, rounds);
	// =============================================
	// Loop until Game Over. This is the Main Game.
	// =============================================
	while (*rounds != 0) {
		// User Input Time.
		ask_for_input(g_letter);
		// Restart Loop and ask for input again if guess invalid.g
		if (player_guessed_this_before(g_arr, g_counter, g_letter))
			continue;
		// Update the Guessed Letters array.
		update_guessed_array(g_arr, g_letter, g_counter);
		// Update the board/Game State accordingly.
		update_game_state(gameState, theWord, g_letter, size, rounds, sheWon);
		// Print the Game State.
		printGameState(gameState, size, rounds);

		// The "End Screen".
		if (*rounds < 1 && *sheWon == false) {
			cout << ">> G A M E   O V E R <<\n\n\n\n";
		}
	}
	return 0;
}

// Function: Initialize starter game state.
void init_game_state(char *gameState, int size) {
	for (int i = 0; i < size; i++) {
		gameState[i] = '_';
	}
}


// Function: Asks for user to input a letter.
void ask_for_input(char* g_letter) {
	cout << "\n>> Guess a Letter man! <<" << endl;
	cin >> *g_letter;
}

// Funciton: check if already Guessed this.
bool player_guessed_this_before(char* g_arr, int* g_counter, char* g_letter) 
{
	for (int i = 0; i < *g_counter+1; i++) {
		if (g_arr[i] == *g_letter) {
			cout << "You already Guessed this Letter once! Try something else bro!" << endl;
			return true;
		}
	}
	cout << "Ok, let's see if it's any good..." << *g_counter << endl;
	*g_counter = *g_counter + 1;
	return false;
}

// Function: Update Guessed Letters Array.
void update_guessed_array(char* g_arr, char* g_letter, int* g_counter) {
	g_arr[*g_counter - 1] = *g_letter;
}

// Update game state.
void update_game_state(char *gameState, char *theWord, char* g_letter, int size, int *rounds, bool* sheWon) {
	bool got_one = false;
	for (int i = 0; i < size; i++) {
		// If correct!
		if (theWord[i] == *g_letter) {
			gameState[i] = *g_letter;
			got_one = true;
		}
	}
	if (got_one)
		if (does_player_have_the_word(gameState, theWord, size)) 
		{
			message2();
			*rounds = 0;
			*sheWon = true;
		}
		else
			message1();
	else {
		// ( Didn't get one! )
		*rounds = *rounds - 1;
		message3();
	}
}

bool does_player_have_the_word(char* gameState, char* theWord, int size) {
	bool got_all_right = true;
	for (int i = 0; i < size; i++) {
		if (gameState[i] != theWord[i]) {
			got_all_right = false;
			//cout << " HEY ONE CHAR DIDNT MATCH HERE:::::";
		}

	}
	return got_all_right;
}

void printGameState(char* gameState, int size, int *rounds) {
	for (int u = 0; u < size; u++) {
		cout << gameState[u] << " ";
	}
	cout << endl << "\n(You have " << *rounds << " rounds left boi (> v<)/)" << endl;
}