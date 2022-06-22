#include "Nmk.h"

Nmk::Nmk() {
	scanf("%d %d %d %d", &n, &m, &k, &ActivePlayer);

	//ActivePlayer = (ActivePlayer + 1) % 2 + 1; //always 1 or 2 (just for safety)

	map = new Map(n, m);
	queue = new Queue();
	//PrintMap();
}
Nmk::~Nmk() {
	delete map;
	delete queue;
}

void Nmk::GenerateMoves(bool cut) {
	if (Ended()) {
		printf("0\n");
		return;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map->Get(i, j) == '0') {
				map->Get(i, j) += ActivePlayer;
				if (cut) {
					if (Ended()) {
						printf("1\n");
						map->Print();
						return;
					}
				}
				queue->Add(map);
				map->Get(i, j) = '0';
			}
		}
	}
	queue->Print();
}
char Nmk::Ended() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map->Get(i, j) != '0') {
				char winner = map->Ended(i, j, k);
				if (winner)return winner;
			}
		}
	}
	return false;
}
int Nmk::Value() {
	int i, j;
	char winner = Ended();
	if (winner == '1') return 1;
	else if (winner == '2') return 2;
	else {
		int winner = FirstTurn();
		if (winner == 1)return 1;
		else if (winner == -1)return 2;
		else return 0;
	}
}
int Nmk::FirstTurn() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map->Get(i, j) == '0') {
				map->Get(i, j) += ActivePlayer;
				if (Ended()) {
					if (ActivePlayer == 2)return -1;
					else return 1;
				}
				map->Get(i, j) = '0';
			}
		}
	}
	return CalculateTurn(map, ActivePlayer + '0');
}
int Nmk::CalculateTurn(Map* currentMap, char player) {
	if (currentMap->IsFull())return 0;
	/*else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map->Get(i, j) == '0') {
					map->Get(i, j) = player;
					if (Ended()) {
						if (player == '2')return -1;
						else return 1;
					}
					map->Get(i, j) = '0';
				}
			}
		}
	}*/
	int v = currentMap->Value(player, k);
	if (v == 2) {
		if (player == '1')return -1;
		else return 1;
	}
	else if (v == 1) {
		return CalculateTurn(currentMap, NextPlayer(player));
	}
	else {
		bool draw = false;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (currentMap->Get(i, j) == '0') {
					Map* newMap = new Map(currentMap);
					newMap->Set(i, j, player);
					v = CalculateTurn(newMap, NextPlayer(player));
					delete newMap;
					if (v == 1 and player == '1')return 1;
					else if (v == -1 and player == '2')return -1;
					else if (v == 0)draw = true;
				}
			}
		}
		if (draw)return 0;
		else if (player == '1')return -1;
		else return 1;
	}
}
char Nmk::NextPlayer(char player) {
	if (player == '1')return '2';
	else return '1';
}