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

	//Конструирует буфер заданной ёмкости
	CircularBuffer(const int capacity);

	//Конструирует буфер заданной ёмкости и заданным массивом
	CircularBuffer(const int capacity, const value_type arr[]);

	//Конструирует буфер заданной ёмкости, целиком заполняет его элементом elem.
	CircularBuffer(int capacity, const value_type elem);

	//Доступ по индексу. Не проверяя правильность индекса.
	value_type& operator[](int i);

	//Оператор присваивания.(start = 0, end = maxSize - 1)
	CircularBuffer& operator=(const CircularBuffer& cb);

	//Оператор сравнения.
	bool operator==(const CircularBuffer& cb);

	//сдвиг индексов start и end
	int Module(int i);

	//Доступ по индексу. Метод бросаeт исключение в случае неверного индекса.
	value_type& At(int i);

	//Ссылка на первый элемент.
	value_type& Front();

	//Ссылка на последний элемент.
	value_type& Back();

	//Количество элементов, хранящихся в буфере.
	int Size() const;

	bool Empty() const;

	//true, если size() == capacity().
	bool Full() const;

	//Количество свободных ячеек в буфере.
	int Reserve() const;

	//ёмкость буфера
	int Capacity() const;

	//Добавляет элемент в конец буфера. 
	//Если текущий размер буфера равен его ёмкости, то переписывается
	//первый элемент буфера (т.е., буфер закольцован). 
	void Push_back(const value_type item);

	//выводит элементы буфера
	void Print();

	//Добавляет новый элемент перед первым элементом буфера. 
	//Аналогично push_back, может переписать последний элемент буфера.
	void Push_front(const value_type item);

	//удаляет последний элемент буфера.
	void Pop_back();

	//удаляет первый элемент буфера.
	void Pop_front();

	//Изменяет размер буфера
	void Set_capacity(int new_capacity);

	//Изменяет размер буфера и заполняет новые элементы item
	void Resize(int new_size, const value_type item);

	//Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
	//переместится в начало аллоцированной памяти.
	void Linearize();

	void Linearize2();

	//Проверяет, является ли буфер линеаризованным.
	bool Is_linearized() const;

	//Сдвигает буфер так, что по нулевому индексу окажется элемент 
	//с индексом new_begin.
	void Rotate(int new_begin);

	//Обменивает содержимое буфера с буфером cb.
	void Swap(CircularBuffer& cb);

	//Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
	void Insert(int pos, const value_type item);

	//Удаляет элементы из буфера в интервале [first, last).
	void Erase(int first, int last);

	//Очищает буфер.
	void Clear();
};