#include <iostream>
#include <string>
#include <fstream>

std::string encryption(std::string source, std::size_t cols, std::size_t rows)
{
	std::size_t iterations = 0;
	std::string result = "";
	const std::size_t size = rows * cols;

	for(std::size_t counter = 0; counter < source.size();)
	{
		std::string temporary = "";

		for(std::size_t i = 0; i < cols; ++i)
		{
			for(std::size_t j = 0; j < rows; ++j)
			{
				if(iterations * size + cols * j + i > source.size())
				{
					// std::cout << "counter: " << counter << std::endl;
					temporary += " ";
					++counter;
					continue;
				}

				char tmp = source[(cols * j) + i + (iterations * size)];

				if(tmp == '\0') temporary += " ";
				else temporary += tmp;

				++counter;
			}
		}

		result += temporary;
		++iterations;
	}

	return result;

}

std::string decryption(std::string source, std::size_t cols, std::size_t rows)
{
	std::string result = "";

	const std::size_t size = rows * cols;
	const std::size_t iterations = source.size() / size;

	for(std::size_t counter = 0; counter < iterations; ++counter)
	{
		std::string temporary = "";

		for(std::size_t i = 0; i < rows; ++i)
		{
			for(std::size_t j = 0; j < cols; ++j)
			{
				temporary += source[counter*size + i + rows*j];
			}
		}

		result += temporary;
	}

	return result;
}

int main()
{
	std::ofstream f("text.txt");

	const std::string str = "i will be back see him later";
	const std::string str2 = "another string";
	const std::string encrypted = encryption(str, 5, 3);
	const std::string encrypted2 = encryption(str2, 5, 3);
	const std::string decrypted = decryption(encrypted, 5, 3);
	const std::string decrypted2 = decryption(encrypted2, 5, 3);

	std::cout << encrypted << std::endl;
	std::cout << encrypted2 << std::endl;
	std::cout << decrypted << std::endl;
	std::cout << decrypted2 << std::endl;

	f << "example 1" << std::endl<<
		   "source string: " << str << std::endl<<
			 "encrypted string: " << encrypted << std::endl <<
			 "decrypted string: " << decrypted << std::endl <<
			 std::endl;

	f << "example 2" << std::endl<<
		   "source string: " << str2 << std::endl<<
			 "encrypted string: " << encrypted2 << std::endl <<
			 "decrypted string: " << decrypted2 << std::endl <<
			 std::endl;

	f.close();

	return 0;
}

