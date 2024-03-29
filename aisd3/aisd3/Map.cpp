#include "Map.h"

Map::Map(int x, int y) : x(x), y(y) {
	tiles = (char**)malloc(sizeof(char*) * x);
	if (tiles == nullptr) return;
	for (int i = 0; i < x; i++) {
		tiles[i] = (char*)malloc(sizeof(char) * y * 2);
		if (tiles[i] == nullptr) return;
		for (int j = 0; j < y * 2 - 1; j++) {
			char c;
			scanf("%c", &c);
			if ((c < '0' and c != ' ') or c > '2')j--;
			else tiles[i][j] = c;
		}
		tiles[i][y * 2 - 1] = '\0';
	}
}
Map::Map(Map* map) : x(map->x), y(map->y) {
	tiles = (char**)malloc(sizeof(char*) * x);
	if (tiles == nullptr) return;
	for (int i = 0; i < x; i++) {
		tiles[i] = (char*)malloc(sizeof(char) * y * 2);
		if (tiles[i] == nullptr) return;
		for (int j = 0; j < y * 2; j++) {
			tiles[i][j] = map->tiles[i][j];
		}
	}
}
Map::~Map() {
	for (int i = 0; i < x; i++) {
		free(tiles[i]);
	}
	free(tiles);
}
char& Map::Get(int i, int j) {
	return tiles[i][j * 2];
}
void Map::Print() {
	for (int i = 0; i < x; i++) {
		printf("%s\n", tiles[i]);
	}
}
char Map::Ended(int i, int j, int k) {
	if (k == 1)return true;
	for (int l = 0; l < DirectionNumber; l++) {
		Vector v;
		switch ((Directions)l)
		{
		case Directions::N:
			v.x = -1;
			v.y = 0;
			break;
		case Directions::NE:
			v.x = -1;
			v.y = 1;
			break;
		case Directions::E:
			v.x = 0;
			v.y = 1;
			break;
		case Directions::SE:
			v.x = 1;
			v.y = 1;
			break;
		case Directions::S:
			v.x = 1;
			v.y = 0;
			break;
		case Directions::SW:
			v.x = 1;
			v.y = -1;
			break;
		case Directions::W:
			v.x = 0;
			v.y = -1;
			break;
		case Directions::NW:
			v.x = -1;
			v.y = -1;
			break;
		default:
			break;
		}
		if (LineCheck(i, j, k, v))return tiles[i][j * 2];
	}
	return false;
}
bool Map::LineCheck(int i, int j, int k, Vector v) {
	if (!OnMap(i + (k - 1) * v.x, j + (k - 1) * v.y))return false;
	for (int l = 1; l < k; l++) {
		if (tiles[i + l * v.x][(j + l * v.y) * 2] != tiles[i][j * 2])return false;
	}
	return true;
}
bool Map::OnMap(int i, int j) {
	return i >= 0 and i < x and j >= 0 and j < y;
}
bool Map::IsEmpty(int i, int j) {
	if (OnMap(i, j)) return tiles[i][j * 2] == '0';
	else return false;
}
int Map::Value(char activePlayer, int k) {
	char desactivePlayer;
	if (activePlayer == '1')	desactivePlayer = '2';
	else						desactivePlayer = '1';
	int possibleWins = 0;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (tiles[i][j * 2] == '0') {
				tiles[i][j * 2] = desactivePlayer;
				if (Ended(i,j,k,desactivePlayer)) {
					if (possibleWins == 1)return 2;
					possibleWins++;
					tiles[i][j * 2] = activePlayer;
				}
				else tiles[i][j * 2] = '0';
			}
		}
	}
	return possibleWins;
}
bool Map::IsFull() {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (tiles[i][j * 2] == '0') {
				return false;
			}
		}
	}
	return true;
}
void Map::Set(int i, int j, char a) {
	tiles[i][j * 2] = a;
}

bool Map::Ended(int i, int j, int k, char player) {
	int a, b;
	Vector v;
	SetHorizontal(a, b, v, i, j, k);
	if (LineCheck(a, b, k, player, v))return true;
	SetVertical(a, b, v, i, j, k);
	if (LineCheck(a, b, k, player, v))return true;
	SetLeftDiag(a, b, v, i, j, k);
	if (LineCheck(a, b, k, player, v))return true;
	SetRightDiag(a, b, v, i, j, k);
	if (LineCheck(a, b, k, player, v))return true;
	return false;
}

bool Map::LineCheck(int i, int j, int k, char player, Vector v) {
	int l = 0;
	int cur = 0;
	while (OnMap(i + v.x * l, j + v.y * l) and l < k * 2) {
		if (tiles[i + v.x * l][(j + v.y * l) * 2] == player) {
			cur++;
			if (cur >= k)return true;
		}
		else cur = 0;
		l++;
	}
	return false;
}

void Map::SetVertical(int& a, int& b, Vector& v, int i, int j, int k) {
	a = i;
	b = j - k;
	v.x = 0;
	v.y = 1;
	if (b < 0)b = 0;
}

void Map::SetHorizontal(int& a, int& b, Vector& v, int i, int j, int k) {
	a = i - k;
	b = j;
	v.x = 1;
	v.y = 0;
	if (a < 0)a = 0;
}

void Map::SetRightDiag(int& a, int& b, Vector& v, int i, int j, int k) {
	a = i;
	b = j;
	while (OnMap(a - 1, b - 1) and k>0) {
		a--;b--;k--;
	}
	v.x = 1;
	v.y = 1;
}

void Map::SetLeftDiag(int& a, int& b, Vector& v, int i, int j, int k) {
	a = i;
	b = j;
	while (OnMap(a - 1, b + 1) and k > 0) {
		a--;b++;k--;
	}
	v.x = 1;
	v.y = -1;
}
bool Map::Ended(int k) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (Ended(i, j, k))return true;
		}
	}
	return false;
}
