#include <iostream>
#include <conio.h>

using namespace std;

class Array
{
protected:
	unsigned char* data_; //указатель на начало
	int length_; //длина

public:
	//конструктор по умолчанию
	Array()
	{
		data_ = new unsigned char[100];
		length_ = 0;
	}

	unsigned char& operator[](int index) const
	{
		if (index < 0 || index >= length_)
		{
			unsigned char res = (unsigned char)' ';
			return res;
		}
		return data_[index];
	}
};

class bit_string : public Array
{
public:

	//конструктор по умолчанию
	bit_string(): Array()
	{
	}

	//конструктор с параметрами
	bit_string(int number) : Array()
	{
		write_number(number);
	}

	//функци€ записи числа в класс
	virtual void write_number(int number)
	{
		int digits = 0;
		while (number > 0)
		{
			int digit = number % 2; //получаем двоичную цифру
			data_[digits] = digit; //записываем еЄ в массив
			number /= 2; //делим число на 2(отбрасываем двоичную цифру)
			digits++; //увеличиваем количество цифр
		}
		length_ = digits;
	}

	//функци€ конвертации в число
	virtual int as_int()
	{
		int sum = 0;
		for (int i = 0; i < length_; ++i)
		{
			int number = (int)data_[i];

			//т.к. number либо 0 либо 1, то после умножени§ на 2 получим либо 0 либо 2, таким образом удовлетвор€€ услови€м перевода систем
			sum += pow(number * 2, i);
		}
		return sum;
	}

	//функци€ вывода в стандартный поток
	virtual void print_to_cout()
	{
		cout << "BitString{ ";
		for (int i = length_ - 1; i > 0; i--)
		{
			cout << "'" << (int)data_[i] << "', ";
		}
		cout << "'" << (int)data_[0] << "' }";
	}
};

//наследуемый класс деньги
class decimal : public Array
{
public:
	//конструктор по умолчанию
	decimal() : Array()
	{
	}

	//конструктор с параметрами
	decimal(int number) : Array()
	{
		write_number(number);
	}

	//перегрузка функции конвертации в число
	int as_int()
	{
		int result = 0;
		int k = 1;
		for (int i = 0; i < length_; i++)
		{
			result += k * (int)data_[i];
			k *= 10;
		}
		return result;
	}

	//перегрузка функции записи числа
	void write_number(int number)
	{
		int k = 0;
		while (number != 0)
		{
			data_[k] = number % 10;
			number /= 10;
			k++;
		}
		length_ = k;
	}

	//перегрузка функции вывода
	void print_to_cout()
	{
		cout << "Decimal{ ";
		for (int i = length_ - 1; i > 0; i--)
		{
			cout << "'" << (int)data_[i] << "', ";
		}
		cout << "'" << (int)data_[0] << "' }";
	}
};

void main()
{
	system("chcp 1251");

	bit_string* bits = new bit_string(127);
	bits->print_to_cout(); //вызов метода
	cout << " = " << bits->as_int(); //вызов ещЄ одного метода
	cout << endl;

	decimal* m = new decimal(1973);
	m->print_to_cout(); //вызов перегрузки метода
	cout << " = " << m->as_int() << ""; //вызов перегрузки ещЄ одного метода

	_getch();
}
