#include <iostream>
#include <conio.h>

using namespace std;

class Array
{
protected:
	unsigned char* data_; //��������� �� ������
	int length_; //�����

public:
	//����������� �� ���������
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

	//����������� �� ���������
	bit_string(): Array()
	{
	}

	//����������� � �����������
	bit_string(int number) : Array()
	{
		write_number(number);
	}

	//������� ������ ����� � �����
	virtual void write_number(int number)
	{
		int digits = 0;
		while (number > 0)
		{
			int digit = number % 2; //�������� �������� �����
			data_[digits] = digit; //���������� � � ������
			number /= 2; //����� ����� �� 2(����������� �������� �����)
			digits++; //����������� ���������� ����
		}
		length_ = digits;
	}

	//������� ����������� � �����
	virtual int as_int()
	{
		int sum = 0;
		for (int i = 0; i < length_; ++i)
		{
			int number = (int)data_[i];

			//�.�. number ���� 0 ���� 1, �� ����� �������� �� 2 ������� ���� 0 ���� 2, ����� ������� ������������ �������� �������� ������
			sum += pow(number * 2, i);
		}
		return sum;
	}

	//������� ������ � ����������� �����
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

//����������� ����� ������
class decimal : public Array
{
public:
	//����������� �� ���������
	decimal() : Array()
	{
	}

	//����������� � �����������
	decimal(int number) : Array()
	{
		write_number(number);
	}

	//���������� ������� ����������� � �����
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

	//���������� ������� ������ �����
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

	//���������� ������� ������
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
	bits->print_to_cout(); //����� ������
	cout << " = " << bits->as_int(); //����� ��� ������ ������
	cout << endl;

	decimal* m = new decimal(1973);
	m->print_to_cout(); //����� ���������� ������
	cout << " = " << m->as_int() << ""; //����� ���������� ��� ������ ������

	_getch();
}
