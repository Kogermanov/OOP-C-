#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Board.h"

class GameOfLife {
private:
	Board board;
	Board cloud;
	int tick = 20;
	std::string name = "First example";
public:
	GameOfLife();
	GameOfLife(std::string input);
	~GameOfLife();
	void SetName(std::string newName);
	void SetTick(int newTick);
	void NextGeneration();
	void Print();
	void Offline();
	void PrintBoard();
	void GetInfo();
	void OutputToFile(std::string out1);
	void InputFromFile(std::string in);
};

void Help();
void Life(int argc, char* argv[]);