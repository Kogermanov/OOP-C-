#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "GameOfLife.h"
#include "Board.h"
#include "windows.h"

GameOfLife::GameOfLife() {
	board.Insert(10, 10);
	board.Insert(10, 11);
	board.Insert(10, 9);
	board.Insert(9, 9);
	board.Insert(8, 10);
	
}

GameOfLife::GameOfLife(std::string input) {
	(*this).InputFromFile(input);
}

GameOfLife::~GameOfLife() {}

void GameOfLife::NextGeneration() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (board.NextGenerationCell(i, j) == 1) {
				cloud.Insert(i,j);
			}
			else {
				cloud.Delete(i,j);
			}
		}
	}
	std::swap(board, cloud);
}

void GameOfLife::Print() {
	for (int i = 0; i < tick; ++i) {
		system("cls");
		board.Print();
		(*this).NextGeneration();
		Sleep(1000);
	}
}

void GameOfLife::Offline() {
	for (int i = 0; i < tick; ++i) {
		(*this).NextGeneration();
	}
}

void GameOfLife::PrintBoard() {
	board.Print();
}

void GameOfLife::GetInfo() {
	std::cout << "name: " << name << ' ' << "tick: " << tick << ' ' << "B" << board.GetNeighbour() << "/S";
	for (int k = 0; k < board.GetNumbOfSurv(); ++k) {
		std::cout << board.GetSurvival(k);
	}
}

void GameOfLife::SetName(std::string newName) {
	std::swap(name, newName);
}

void GameOfLife::SetTick(int newTick) {
	tick = newTick;
}

void  GameOfLife::OutputToFile(std::string out1) {
	std::ofstream out;

	out.open(out1);
	if (!out.is_open()) {
		std::cout << "Error opening file";
		out.close();
	}
	else {
		out << "#" << this->name << ' ' << "B" << board.GetNeighbour() << "/S";
		for (int k = 0; k < board.GetNumbOfSurv(); ++k) {
			out << board.GetSurvival(k);
		}
		out << '\n';
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				if (board.ÑellState(i, j) == 1) {
					out << j << ' ' << i;
					out << '\n';
				}
			}
		}
	}

	out.close();
}

void  GameOfLife::InputFromFile(std::string in) {
	std::ifstream input;
	input.open(in);

	std::string a;

	if (!input.is_open()) {
		std::cout << "Error opening input file";
		input.close();
	}
	else {
		getline(input, a);
		int y, x;
		while (input >> x >> y) {
			board.Insert(y, x);
		}
	}
	input.close();
	int i = 0;
	int wall = 0;
	int len = 0;
	int endOfname = 0;

	while (a[i]) {
		++i;
		if (a[i] == '/') {
			wall = i;
		}
		if (a[i] == ' ') {
			endOfname = i;
		}
		++len;
	}
	std::string newName;
	for (int k = 1; k < endOfname; ++k) {
		newName.push_back(a[k]);
	}
	std::swap(name, newName);

	int index = wall - 1;
	int new_neighbours = a[index] - '0';
	board.SetNeighbour(new_neighbours);

	std::vector<int> sur;
	for (int j = wall + 2; j < len; ++j) {
		sur.push_back((a[j] - '0'));
	}
	board.SetSurvival(sur);

	input.close();
}

void Help() {
	std::cout << "dump< the path to the file> - save the universe to a file\n"
		"tick<n>  - calculate n iterations and print the result.\n"
		"exit - end the game\n"
		"help - print help about commands" << std::endl;
}


void Life(int argc, char* argv[]) {
	if (argc == 1) {
		std::string key;
		std::cout << "Do you want to work with the file? Yes -> 1, No -> 2" << std::endl;
		std::cin >> key;
		system("cls");
		if (key == "1") {
			std::string path;
			std::cout << "Please, write down the path to the input file" << std::endl;
			std::cin >> path;
			GameOfLife game(path);
			std::string command;
			game.GetInfo();
			game.PrintBoard();
			while (std::cin >> command) {
				if (command == "help") {
					Help();
				}
				if (command[0] == 't') {
					system("cls");
					std::string a;
					for (int i = 5; i < command.length() - 1; ++i) {
						a.push_back(command[i]);
					}
					int tick = stoi(a);
					game.SetTick(tick);
					game.Print();
					system("cls");
					game.GetInfo();
					game.PrintBoard();
				}
				if (command[0] == 'd') {
					std::string fileName;
					for (int i = 5; i < command.length() - 1; ++i) {
						fileName.push_back(command[i]);
					}
					game.OutputToFile(fileName);
					std::cout << "done" << std::endl;
				}
				if (command == "exit") {
					break;
				}
			}
		}
		else {
			GameOfLife game;
			std::string command;
			game.GetInfo();
			game.PrintBoard();
			while (std::cin >> command) {
				if (command == "help") {
					Help();
				}
				if (command[0] == 't') {
					system("cls");
					std::string a;
					for (int i = 5; i < command.length() - 1; ++i) {
						a.push_back(command[i]);
					}
					int tick = stoi(a);
					game.SetTick(tick);
					game.Print();
					system("cls");
					game.GetInfo();
					game.PrintBoard();
				}
				if (command[0] == 'd') {
					std::string fileName; 
					for (int i = 5; i < command.length() - 1; ++i) {
						fileName.push_back(command[i]);
					}
					game.OutputToFile(fileName);
					std::cout << "done" << std::endl;
				}
				if (command == "exit") {
					break;
				}
			}
		}
	}
	else {
		if (argc != 7) {
			std::cout << "Error argc";
		}
		else {
			std::string newTick;
			std::string out;
			std::string in;
			for (int i = 1; i < 7; i++) {
				if (std::string(argv[i]) == "-i") {
					newTick = std::string(argv[i + 1]);
					std::cout << "tick: " << newTick << std::endl;
				}
				if (std::string(argv[i]) == "-o") {
					out = std::string(argv[i + 1]);
					std::cout << "Output file: " << out << std::endl;
				}
				if (std::string(argv[i]) == "-in") {
					in = std::string(argv[i + 1]);
					std::cout << "Input file: " << in << std::endl;
				}
			}
			GameOfLife game(in);
			int tick = stoi(newTick);
			game.SetTick(tick);
			game.Offline();
			game.OutputToFile(out);
		}
	}
}
