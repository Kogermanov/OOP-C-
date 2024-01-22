#include "Board.h"
#include <iostream>
#include <string>
#include <vector>


int Module(int x, int mod) {
	if (x < 0) {
		return x + mod;
	}
	if (x > (mod - 1)) {
		return x - mod;
	}
	return x;
}

Board::Board() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			(*this).board[i][j] = 0;
		}
	}
}
void Board::Insert(int y, int x) {
	(*this).board[y][x] = 1;
}

void Board::Delete(int y, int x) {
	(*this).board[y][x] = 0;
}

void Board::PrintSurvival() {
	size_t size = survival.size();
	for (int i = 0; i < size; ++i) {
		std::cout << survival[i];
	}
}

int Board::GetNumbOfSurv() {
	return survival.size();
}
int Board::GetSurvival(int index) {
	return survival[index];
}

void Board::SetNeighbour(int new_neighbour) {
	neighbour = new_neighbour;
}

void Board::SetSurvival(std::vector<int>& sur) {
	survival.clear();
	int newSize = sur.size();
	survival.resize(newSize);
	for (int i{}; i < newSize; ++i) {
		survival[i] = sur[i];
	}
}

int Board::NumberOfNeighbors(int y, int x) {
	int res = 0;
	for (int i = y - 1; i < y + 2; ++i) {
		for (int j = x - 1; j < x + 2; ++j) {
			if (board[Module(i, height)][Module(j, width)] == 1) {
				++res;
			}
		}
	}
	res -= board[y][x];
	return res;
}

int Board::ÑellState(int y, int x) {
	return (*this).board[y][x];
}

int Board::GetNeighbour() {
	return neighbour;
}

int Board::NextGenerationCell(int y, int x) {
	if (((*this).ÑellState(y, x) == 1) && ((*this).NumberOfNeighbors(y, x) != survival[0] && (*this).NumberOfNeighbors(y, x) != survival[1])) {
		return 0;
	}
	if ((*this).ÑellState(y, x) == 0 && (*this).NumberOfNeighbors(y, x) == neighbour) {
		return 1;
	}
	return (*this).ÑellState(y, x);
}

void Board::Print() {
	std::cout << '\n';
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			std::cout << (*this).board[i][j];
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

