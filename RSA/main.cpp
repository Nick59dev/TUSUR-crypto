// RSA, Zimin Nikita, p = 919, q = 571, e = 7

#include <iostream>
#include <map>
#include <string>
#include <cassert>
#include <fstream>

using namespace std;

const unsigned int p = 919;
const unsigned int q = 571;

const unsigned int n = p * q;
const unsigned int fn = (p - 1) * (q - 1);

short int e = 7;

const unsigned int d = ((fn * 2) + 1) / e;

string alphabet = "абвгдежзийклмнопрстуфхцчшщъыьэюяabcdefghijklmnopqrstuvwxyz ,.";


map<string, int> symToNum;
map<int, string> numToSym;


unsigned long long int fast_power(unsigned base, unsigned power)
{   // быстрое возведение в степень, схема справа-налево
	unsigned long long int z = base;
	unsigned long long int x = 1;
	unsigned long long power2 = power;
	short int iterations = 0;

	while (power2 != 0)
	{
		++iterations;
		power2 = (power2 >> 1);
	}

	for(short int i = 0; i < iterations; ++i)
	{
		if (power % 2)
		{
			x *= z;
			z *= z;
			power = (power >> 1);
		}
		else
		{
			z *= z;
			power = (power >> 1);
		}
	}

	return x;
}

unsigned long long fast_power_with_modulus(unsigned long long base, unsigned power, unsigned modulus)
{ // возведение в степень по модулю, схема справа-налево
	unsigned long long int x = 1;
	unsigned long long int iterations = 0;
	unsigned long long int power2 = power;
	unsigned long long int temp = base;

	while (power2 != 0)
	{
		power2 = (power2 >> 1);
		++iterations;
	}

	for (unsigned int i = 0; i < iterations; ++i)
	{
		if (power % 2)
		{
			x = (x * temp) % modulus;
			temp = (temp * temp) % modulus;
			power = (power >> 1);
		}
		else
		{
			temp = (temp * temp) % modulus;
			power = (power >> 1);
		}
	}

	return x;
}

void encryption(const string text, const string filename)
{ // шифрование, на выходе получаем набор чисел, который пишем в файл
	ofstream file(filename);
	string temporary = "";
	unsigned num;

	for (unsigned int i = 0; i < text.size(); ++i)
	{
		temporary += text[i];
		num = symToNum[temporary];
		temporary = "";
		file << fast_power(num, e) % n << " ";
	}

	file.close();
}

string decryption(string filename)
{ // считываем из файла числа, которые затем преобразуем в символы, чтобы добавить к строке
	string message = "";
	ifstream file(filename);
	unsigned long long int num;

	while (!(file.eof()))
	{
		file >> num;
		num = fast_power_with_modulus(num, d, n);

		message += numToSym[(int)num];
	}

	file.close();

	return message;
}

int main()
{
	setlocale(LC_ALL, "");

	short int offset = 10;

	const string test1 = "hello, my name is nick";
	const string test2 = "привет, меня зовут никита";

	for (unsigned int i = 0; i < alphabet.size(); ++i)
	{
		numToSym[i + offset] = alphabet[i];
	}

	for (unsigned int i = 0; i < alphabet.size(); ++i)
	{
		symToNum[numToSym[i + offset]] = i + offset;
	}

	assert(numToSym.size() == symToNum.size());

	encryption(test1, "encrypted.txt");
	cout << decryption("encrypted.txt") << endl;

	encryption(test2, "encrypted.txt");
	cout << decryption("encrypted.txt") << endl;

	system("pause");
	return 0;
}

