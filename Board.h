#pragma once
#include <iostream>
#include <vector>

const int height = 15;
const int width = 25;

class Board {
private:
	//количество соседних клеток для рождения жизни
	int neighbour = 3;
	//количество соседних клеток для продолжения жизни
	std::vector<int>  survival{2,3};
	int board[height][width];
public:
	Board();
	~Board() {}
	//Зародить жизнь по координатам
	void Insert(int y, int x);
	//Убить по координатам
	void Delete(int y, int x);
	//Изменить количество соседних клеток для рождения жизни
	void SetNeighbour(int new_neighbour);
	//Изменить количество соседних клеток для продолжения жизни
	void SetSurvival(std::vector<int>& sur);
	//Количество соседей клетки по координатам
	int NumberOfNeighbors(int y, int x);
	//Состояние клетки(жива или мертва)
	int СellState(int y, int x);
	int GetNeighbour();
	int GetNumbOfSurv();
	int GetSurvival(int index);
	void PrintSurvival();
	int NextGenerationCell(int y, int x);
	void Print();
};
