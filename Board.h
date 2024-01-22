#pragma once
#include <iostream>
#include <vector>

const int height = 15;
const int width = 25;

class Board {
private:
	//���������� �������� ������ ��� �������� �����
	int neighbour = 3;
	//���������� �������� ������ ��� ����������� �����
	std::vector<int>  survival{2,3};
	int board[height][width];
public:
	Board();
	~Board() {}
	//�������� ����� �� �����������
	void Insert(int y, int x);
	//����� �� �����������
	void Delete(int y, int x);
	//�������� ���������� �������� ������ ��� �������� �����
	void SetNeighbour(int new_neighbour);
	//�������� ���������� �������� ������ ��� ����������� �����
	void SetSurvival(std::vector<int>& sur);
	//���������� ������� ������ �� �����������
	int NumberOfNeighbors(int y, int x);
	//��������� ������(���� ��� ������)
	int �ellState(int y, int x);
	int GetNeighbour();
	int GetNumbOfSurv();
	int GetSurvival(int index);
	void PrintSurvival();
	int NextGenerationCell(int y, int x);
	void Print();
};
