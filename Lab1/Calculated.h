#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string.h>

struct Stack1 {
	double data;
	Stack1 *next;
};

Stack1 *head1 = nullptr;

struct Stack2 {
	char sgn;
	Stack2 *next;
};

Stack2 *head2 = nullptr;

bool isErr = false;

void Push1(double value)
{
	Stack1 *p = new Stack1;
	p->data = value;
	p->next = head1;
	head1 = p;
}

double Pop1(void)
{
	double n = head1->data;
	Stack1 *p = head1;
	head1 = head1->next;
	delete p;
	return n;
}

void Push2(char value)
{
	Stack2 *p = new Stack2;
	p->sgn = value;
	p->next = head2;
	head2 = p;
}

char Pop2(void)
{
	char n = head2->sgn;
	Stack2 *p = head2;
	head2 = head2->next;
	delete p;
	return n;
}

void Clear1(void)
{
	while (head1 != nullptr)
	{
		Stack1 *temp = head1->next;
		delete head1;
		head1 = temp;
	}
}

void Clear2(void)
{
	while (head2 != nullptr)
	{
		Stack2 *temp = head2->next;
		delete head2;
		head2 = temp;
	}
}

int Priority(char c)
{
	switch (c)
	{
	case '(':
		return -1;
	case '*': case '/':
		return 1;
	case '+': case '-':
		return 2;
	default:
		isErr = true;
		return -100;
	}
}

bool canPop(char c)
{
	if (head2 == nullptr)
		return false;
	int p1 = Priority(c);
	int p2 = Priority(head2->sgn);

	return p1 >= 0 && p2 >= 0 && p1 >= p2;
}

void Calculate(char* buf)
{
	int i = 1, k = 0;
	char a[258] = "(", temp[256] = { NULL };

	strcat(a, buf);
	strcat(a, ")");

	Push2('(');

	do {
		if (('0' <= a[i] && '9' >= a[i]) || ('.' == a[i] && k != 0))
		{
			temp[k] = a[i];
			k++;
		}
		else
		{
			if (a[i - 1] == '(' && (a[i] == '+' || a[i] == '-'))
				Push1(0);

			if (k != 0) {
				char * ptrEnd;
				Push1(strtod(temp, &ptrEnd));
				if (*ptrEnd != '\0' || (errno == ERANGE && (head1->data == HUGE_VAL)))
				{
					isErr = true;
				}
				memset(temp, 0, sizeof temp);
				k = 0;
			}
			else;

			if (a[i] == ')')
			{
				while (head2 != nullptr && head2->sgn != '(' && isErr != true)
				{
					if (head1->next != nullptr)
					{
						double B = Pop1();
						double A = Pop1();
						switch (Pop2())
						{
						case '+':
							Push1(A + B);
							break;
						case '-':
							Push1(A - B);
							break;
						case '*':
							Push1(A * B);
							break;
						case '/':
							if (B != 0)
							{
								Push1(A / B);
							}
							else
							{
								isErr = true;
							}
							break;
						default:
							isErr = true;
							break;
						}
					}
					else
					{
						isErr = true;
					}
				}
				if (head2 != nullptr)
				{
					a[0] = Pop2();
				}
				else
				{
					isErr = true;
				}
			}
			else
			{
				while (canPop(a[i]) && isErr != true)//а если head2 == nullptr?.. Нужна ли обработка?
				{
					if (head1->next != nullptr)
					{
						double B = Pop1();
						double A = Pop1();
						switch (Pop2())
						{
						case '+':
							Push1(A + B);
							break;
						case '-':
							Push1(A - B);
							break;
						case '*':
							Push1(A * B);
							break;
						case '/':
							if (B != 0)
							{
								Push1(A / B);
							}
							else
							{
								isErr = true;
							}
							break;
						default:
							isErr = true;
							break;
						}
					}
					else
					{
						isErr = true;
					}
				}
				Push2(a[i]);
			}

		}
		i++;
	} while (a[i] != '\0' && isErr != true);

	if (head2 != nullptr || head1 == nullptr)
	{
		isErr = true;
	}
	else if (head1->next != nullptr)
	{
		isErr = true;
	}
	else;

	if (isErr != true)
	{
		memset(buf, 0, sizeof buf);
		sprintf(buf, "%f", Pop1());

	}
	else
	{
		memset(buf, 0, sizeof buf);
		strcpy(buf, "error");
	}

	Clear1();
	Clear2();
	isErr = false;
}