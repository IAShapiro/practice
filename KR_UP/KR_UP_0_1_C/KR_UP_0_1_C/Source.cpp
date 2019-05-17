#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

std::vector<int> decomposition(unsigned int x);

std::string line_of_div(std::vector<int>, unsigned int);

int main()
{
	std::ifstream in("1.txt");
	if (!in.is_open())
	{
		return 1;
	}

	std::map<int, std::string> h2;

	std::string tmp;
	while (getline(in, tmp))
	{
		char * next = nullptr, * p = strtok_s(&tmp[0], "\n EOF", &next);
		
		while (p != nullptr)
		{
			h2[atoi(p)] = line_of_div(decomposition(atoi(p)), atoi(p));

			p = strtok_s(nullptr, "\n EOF", &next);
		}
	}

	for (auto& it : h2)
	{
		std::cout << it.second << std::endl;
	}

	in.close();
	system("pause");
	return 0;
}

std::vector<int> decomposition(unsigned int x)
{
	std::vector<int> dividers;

	if (x == 1)
	{
		dividers.push_back(x);
		return dividers;
	}

	for (auto i = 2; i <= sqrt(x); i++)//sqrt(x) instead x - optimization
	{
		while (x % i == 0)
		{
			dividers.push_back(i);
			x /= i;
		}
	}

	if (x != 1)//for prime number
	{
		dividers.push_back(x);
	}
	
	return dividers;
}

std::string line_of_div(std::vector<int> A, unsigned int numb)
{
	std::string line = std::to_string(numb) + " = ";

	int degree = 1;

	for (auto i = 1; i < static_cast<int>(A.size()); i++)
	{
		if (A[i] == A[i - 1])
		{
			degree++;
		}
		else
		{
			line += std::to_string(A[i - 1]);
			if (degree != 1)
			{
				line += "^" + std::to_string(degree);
			}
			line += " * ";
			degree = 1;
		}
	}

	line += std::to_string(A[A.size() - 1]);
	if (degree != 1)
	{
		line += "^" + std::to_string(degree);
	}
	return line;
}