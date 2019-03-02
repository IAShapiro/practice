#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <cerrno>

bool isError = false;

void BinCalculate(char* buf)
{
	long int a, b;

	if (buf[0] == '~')
	{
		char * pEnd;
		b = strtol(buf + 1, &pEnd, 10);
		if (*pEnd != '\0' || (b == 0 && buf[1] != '0') || (errno == ERANGE && (b == LONG_MIN || b == LONG_MAX)))//а переполнение?..
		{
			isError = true;
		}
		else
		{
			a = ~b;
//_________________________________________//
		}
	}
	else if ('0' <= buf[0] && buf[0] <= '9')
	{
		char * pEnd;
		a = strtol(buf, &pEnd, 10);
		if (*pEnd == '\0' || (a == 0 && buf[0] != '0') || (errno == ERANGE && (a == LONG_MIN || a == LONG_MAX)))//а переполнение?..
		{
			isError = true;
		}
		else
		{
			if (*pEnd == '&')
			{
				pEnd++;
				if (!('0' <= *pEnd && *pEnd <= '9'))
				{
					isError = true;
				}
				else
				{
					b = strtol(pEnd, &pEnd, 10);
					if (*pEnd != '\0' || (errno == ERANGE && (b == LONG_MIN || b == LONG_MAX)))//а переполнение?..
					{
						isError = true;
					}
					else
					{
						a = a & b;
//_________________________________________//
					}
				}
			}
			else if (*pEnd == '|')
			{
				pEnd++;
				if (!('0' <= *pEnd && *pEnd <= '9'))
				{
					isError = true;
				}
				else
				{
					b = strtol(pEnd, &pEnd, 10);
					if (*pEnd != '\0' || (errno == ERANGE && (b == LONG_MIN || b == LONG_MAX)))//а переполнение?..
					{
						isError = true;
					}
					else
					{
						a = a | b;
						//_________________________________________//
					}
				}
			}
			else if (*pEnd == '^')
			{
				pEnd++;
				if (!('0' <= *pEnd && *pEnd <= '9'))
				{
					isError = true;
				}
				else
				{
					b = strtol(pEnd, &pEnd, 10);
					if (*pEnd != '\0' || (errno == ERANGE && (b == LONG_MIN || b == LONG_MAX)))//а переполнение?..
					{
						isError = true;
					}
					else
					{
						a = a ^ b;
						//_________________________________________//
					}
				}
			}
			else if (*pEnd == '<')
			{
				pEnd++;
				if (*pEnd != '<')
				{
					isError = true;
				}
				else
				{
					pEnd++;
					if (!('0' <= *pEnd && *pEnd <= '9'))
					{
						isError = true;
					}
					else
					{
						b = strtol(pEnd, &pEnd, 10);
						if (*pEnd != '\0' || (errno == ERANGE && (b == LONG_MIN || b == LONG_MAX)))//а переполнение?..
						{
							isError = true;
						}
						else
						{
							a = a << b;
							//_________________________________________//
						}
					}
				}
			}
			else if (*pEnd == '>')
			{
				pEnd++;
				if (*pEnd != '>')
				{
					isError = true;
				}
				else
				{
					pEnd++;
					if (!('0' <= *pEnd && *pEnd <= '9'))
					{
						isError = true;
					}
					else
					{
						b = strtol(pEnd, &pEnd, 10);
						if (*pEnd != '\0' || (errno == ERANGE && (b == LONG_MIN || b == LONG_MAX)))//а переполнение?..
						{
							isError = true;
						}
						else
						{
							a = a >> b;
							//_________________________________________//
						}
					}
				}
			}
			else
			{
				isError = true;
			}
		}
	}
	else
	{
		isError = true;
	}

	if (isError != true)
	{
		memset(buf, 0, sizeof buf);
		sprintf(buf, "%d", a);
	}
	else
	{
		memset(buf, 0, sizeof buf);
		strcpy(buf, "error");
	}
	isError = false;
}