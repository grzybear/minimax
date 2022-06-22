#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Queue.h"
#include <fstream>

class Nmk
{
private:
	int n, m, k, ActivePlayer;
	Map* map;
	Queue* queue;
public:
	Nmk();
	~Nmk();
	void GenerateMoves(bool cut);
	char Ended();
	int Value();
	int FirstTurn();
	int CalculateTurn(Map* currentMap, char player);
	char NextPlayer(char player);
};