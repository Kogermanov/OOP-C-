#pragma once
typedef int value_type;

class CircularBuffer {
private:
	int maxSize = 0;
	int start = 0;
	int end = -1;
	int size = 0;
	value_type* buffer;
public:
	~CircularBuffer();

	//������������ ����� �������� �������
	CircularBuffer(const int capacity);

	//������������ ����� �������� ������� � �������� ��������
	CircularBuffer(const int capacity, const value_type arr[]);

	//������������ ����� �������� �������, ������� ��������� ��� ��������� elem.
	CircularBuffer(int capacity, const value_type elem);

	//������ �� �������. �� �������� ������������ �������.
	value_type& operator[](int i);

	//�������� ������������.(start = 0, end = maxSize - 1)
	CircularBuffer& operator=(const CircularBuffer& cb);

	//�������� ���������.
	bool operator==(const CircularBuffer& cb);

	//����� �������� start � end
	int Module(int i);

	//������ �� �������. ����� �����e� ���������� � ������ ��������� �������.
	value_type& At(int i);

	//������ �� ������ �������.
	value_type& Front();

	//������ �� ��������� �������.
	value_type& Back();

	//���������� ���������, ���������� � ������.
	int Size() const;

	bool Empty() const;

	//true, ���� size() == capacity().
	bool Full() const;

	//���������� ��������� ����� � ������.
	int Reserve() const;

	//������� ������
	int Capacity() const;

	//��������� ������� � ����� ������. 
	//���� ������� ������ ������ ����� ��� �������, �� ��������������
	//������ ������� ������ (�.�., ����� �����������). 
	void Push_back(const value_type item);

	//������� �������� ������
	void Print();

	//��������� ����� ������� ����� ������ ��������� ������. 
	//���������� push_back, ����� ���������� ��������� ������� ������.
	void Push_front(const value_type item);

	//������� ��������� ������� ������.
	void Pop_back();

	//������� ������ ������� ������.
	void Pop_front();

	//�������� ������ ������
	void Set_capacity(int new_capacity);

	//�������� ������ ������ � ��������� ����� �������� item
	void Resize(int new_size, const value_type item);

	//������������ - �������� ��������� ����� ���, ��� ��� ������ �������
	//������������ � ������ �������������� ������.
	void Linearize();

	void Linearize2();

	//���������, �������� �� ����� ���������������.
	bool Is_linearized() const;

	//�������� ����� ���, ��� �� �������� ������� �������� ������� 
	//� �������� new_begin.
	void Rotate(int new_begin);

	//���������� ���������� ������ � ������� cb.
	void Swap(CircularBuffer& cb);

	//��������� ������� item �� ������� pos. ������� ������ �������� ����������.
	void Insert(int pos, const value_type item);

	//������� �������� �� ������ � ��������� [first, last).
	void Erase(int first, int last);

	//������� �����.
	void Clear();
};