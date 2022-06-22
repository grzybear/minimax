#define _CRT_SECURE_NO_WARNINGS
#define MaxCommandLength 50
#include <iostream>
#include "Nmk.h"

bool CompareStrings(const char* string, const char* command) {
	int i = 0;
	while (string[i] != '\0' and command[i] != '\0') {
		if (string[i++] != command[i])return false;
	}
	return string[i] == '\0' and command[i] == '\0';
}

int main()
{	
	char command[MaxCommandLength];
	Nmk* nmk;
	//std::ofstream plik("plik.txt");
	while (std::cin >> command) {
		if (CompareStrings("GEN_ALL_POS_MOV", command)) {
			nmk = new Nmk();
			nmk->GenerateMoves(false);
			delete nmk;
		}
		else if (CompareStrings("GEN_ALL_POS_MOV_CUT_IF_GAME_OVER", command)) {
			nmk = new Nmk();
			nmk->GenerateMoves(true);
			delete nmk;
		}
		else if (CompareStrings("SOLVE_GAME_STATE", command)) {
			nmk = new Nmk();
			int winner = nmk->Value();
			if (winner == 1) {
				//plik << "FIRST_PLAYER_WINS\n";
				printf("FIRST_PLAYER_WINS\n");
			}
			else if (winner == 2) {
				//plik << "SECOND_PLAYER_WINS\n";
				printf("SECOND_PLAYER_WINS\n");
			}
			else {
				//plik << "BOTH_PLAYERS_TIE\n";
				printf("BOTH_PLAYERS_TIE\n");
			}
			delete nmk;
		}
		else if (CompareStrings("q", command)) {
			break;
		}
	}
	//plik.close();
    new Nmk();
    return 0;
}
