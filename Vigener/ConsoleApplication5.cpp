// ConsoleApplication5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>


bool Encryption(char * input, char alph_0, char alph_n, char alph_0_sm, char alph_n_sm, char * key, char * res);
bool Encryption2(char * input, char alph_0, char alph_n, char alph_0_sm, char alph_n_sm, char * key, char * res);
bool Encryption3(char * input, char alph_0, char alph_n, char alph_0_sm, char alph_n_sm, char * key, char * res);
int get_numb(char * alph, char a);

int main()
{
	char a[] = "AttACKATdaWN";//пропуск символов
	char b[] = "LeMON";
	char res[256] = "";
	Encryption(a, 'A', 'Z', 'a', 'z', b, res);
    std::cout << res << std::endl;

	char c[] = "Lab4";//шифрование всего
	char d[] = "she's not ready";
	Encryption3(d, 'A', 'Z', 'a', 'z', c, res);
	std::cout << res << std::endl;

	char a2[] = "Att  ACKA3453TdaWN";//удаление символов
	char b2[] = "LeM678 09ON";
	char res2[256] = "";
	Encryption2(a2, 'A', 'Z', 'a', 'z', b2, res2);
	std::cout << res2 << std::endl;
}

bool Encryption(char * input, char alph_0, char alph_n, char alph_0_sm, char alph_n_sm, char * key, char * res)
{
	const int len_of_alph = alph_n - alph_0 + 1;

	for (auto i = 0; i < static_cast<int>(strlen(key)); i++)
	{
		if (!(((key[i] <= alph_n) && (key[i] >= alph_0)) || ((key[i] <= alph_n_sm) && (key[i] >= alph_0_sm))))
		{
			return false;
		}
		else if ((key[i] <= alph_n_sm) && (key[i] >= alph_0_sm))
		{
			key[i] -= alph_0_sm - alph_0;
		}
	}

	if (alph_n < alph_0 || alph_n_sm < alph_0_sm || (alph_n - alph_0 != alph_n_sm - alph_0_sm))
	{
		return false;
	}

	char tmp1[256] = {NULL};
	strcpy(tmp1, "");
	for(int i = 0; i < static_cast<int>(strlen(input) / strlen(key)); i++)
	{
		strcat(tmp1, key);
	}
	for (int i = 0; i < static_cast<int>(strlen(input) % strlen(key)); i++)
	{
		tmp1[strlen(tmp1)] = key[i];
	}
	tmp1[strlen(tmp1)] = '\0';

	strcpy(res, "");
	for (auto i = 0; i < static_cast<int>(strlen(input)); i++)
	{
		if ((input[i] <= alph_n_sm) && (input[i] >= alph_0_sm))
		{
			res[i] = char((tmp1[i] + input[i] - (alph_0_sm - alph_0)) % len_of_alph + alph_0_sm);
		}
		else if ((input[i] <= alph_n) && (input[i] >= alph_0))
		{
			res[i] = char((tmp1[i] + input[i]) % len_of_alph + alph_0);
		}
		else
		{
			res[i] = input[i];
		}
	}
	return true;
}

bool Encryption3(char * input, char alph_0, char alph_n, char alph_0_sm, char alph_n_sm, char * key, char * res)
{
	const int len_of_alph = alph_n - alph_0 + 1;

	for (auto i = 0; i < static_cast<int>(strlen(key)); i++)
	{
		if ((key[i] <= alph_n_sm) && (key[i] >= alph_0_sm))
		{
			key[i] -= alph_0_sm - alph_0;
		}
	}

	char * alph = new char[43 + len_of_alph];
	for (auto i = 0; i < len_of_alph; i++)
	{
		alph[i] = alph_0 + i;
	}
	for (auto i = 32; i < 65; i++)
	{
		alph[i - 32 + len_of_alph] = i;
	}
	for (auto i = 91; i < 97; i++)
	{
		alph[i - 58 + len_of_alph] = i;
	}
	for (auto i = 123; i < 127; i++)
	{
		alph[i - 84 + len_of_alph] = i;
	}

	char tmp1[256] = { NULL };
	strcpy(tmp1, "");
	for (int i = 0; i < static_cast<int>(strlen(input) / strlen(key)); i++)
	{
		strcat(tmp1, key);
	}
	for (int i = 0; i < static_cast<int>(strlen(input) % strlen(key)); i++)
	{
		tmp1[strlen(tmp1)] = key[i];
	}
	tmp1[strlen(tmp1)] = '\0';

	strcpy_s(res, strlen(res), "");
	res[0] = '\0';

	for (auto i = 0; i < static_cast<int>(strlen(input)); i++)
	{
		if ((input[i] <= alph_n_sm) && (input[i] >= alph_0_sm))
		{
			res[i] = alph[(get_numb(alph, tmp1[i]) + get_numb(alph, input[i] - (alph_0_sm - alph_0))) % (44 + len_of_alph)];
		}
		else
		{
			res[i] = alph[(get_numb(alph, tmp1[i]) + get_numb(alph, input[i])) % (44 + len_of_alph)];
		}
	}

	return true;
}

int get_numb(char * alph, char a)
{
	for (auto i = 0; i < static_cast<int>(strlen(alph)); i++)
	{
		if (alph[i] == a)
		{
			return i;
		}
	}

	return -1;
}

bool Encryption2(char * input, char alph_0, char alph_n, char alph_0_sm, char alph_n_sm, char * key, char * res)
{
		
	char tmp2_in[256] = "";
	int l = 0;
	for (auto i = 0; i < static_cast<int>(strlen(input)); i++)
	{
		if ((((input[i] <= alph_n) && (input[i] >= alph_0)) || ((input[i] <= alph_n_sm) && (input[i] >= alph_0_sm))))
		{
			tmp2_in[l] = input[i];
			l++;
		}
	}
	char tmp2_key[256] = "";
	l = 0;
	for (auto i = 0; i < static_cast<int>(strlen(key)); i++)
	{
		if ((((key[i] <= alph_n) && (key[i] >= alph_0)) || ((key[i] <= alph_n_sm) && (key[i] >= alph_0_sm))))
		{
			tmp2_key[l] = key[i];
			l++;
		}
	}
	if (Encryption(tmp2_in, alph_0, alph_n, alph_0_sm, alph_n_sm, tmp2_key, res) == false)
	{
		return false;
	}
	return true;
}


