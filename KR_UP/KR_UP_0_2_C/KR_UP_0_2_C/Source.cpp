#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main()
{
	std::ifstream in("1.txt");
	if (!in.is_open())
	{
		return 1;
	}

	std::multimap<int, std::string> h2;
	std::string tmp;
	while (getline(in, tmp))
	{
		if (!tmp.empty())
		{
			auto weight = 0;
			for (auto& it : tmp)
			{
				if (((it <= 'Z') && (it >= 'A')) || ((it <= 'z') && (it >= 'a')))
				{
					weight += (tolower(it) - 'a' + 1);
				}
				else if (it <= '9' && it >= '0')
				{
					weight += it - '0';
				}
				else
				{
					weight++;
				}
			}
			tmp.insert(0, "\"");
			tmp += "\" = " + std::to_string(weight);
			h2.insert(std::pair<int, std::string>(-weight, tmp));
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
