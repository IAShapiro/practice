#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

int main()
{
	std::multimap<int, int> A;

	std::ifstream in("1.txt");
	if (!in.is_open())
	{
		return 1;
	}

	std::string tmp;
	getline(in, tmp);

	char * next = nullptr, *p = strtok_s(&tmp[0], "\n EOF", &next);
	int n = atoi(p);
	p = strtok_s(nullptr, "\n EOF", &next);
	int m = atoi(p);

	for (auto j = 0; j < m; j++)
	{
		getline(in, tmp);

		next = nullptr, p = strtok_s(&tmp[0], "\n EOF", &next);
		int u = atoi(p);
		p = strtok_s(nullptr, "\n EOF", &next);
		int v = atoi(p);

		A.insert(std::pair<int, int>(u, v));
		A.insert(std::pair<int, int>(v, u));
	}

	for (auto j = 1; j < n + 1; j++)
	{
		std::cout << A.count(j);
		auto range = A.equal_range(j);
		for (auto k = range.first; k != range.second; ++k)
		{
			std::cout << " " << k->second;
		}
		std::cout << std::endl;
	}
	system("pause");
	in.close();
	return 0;
}
