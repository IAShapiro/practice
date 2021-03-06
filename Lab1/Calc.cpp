#include "stdafx.h"//Предложения: перехват событий + типы данных доделать(int/double/и т.д.)
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdlib.h>
#include <Shlwapi.h>
#include "Calculated.h"
#include "BinCalc.h"
#include "Calc.h"

char buf[256];
HINSTANCE hInst;
bool choiceOfNormal = true;

//Создаём прототип функции окна
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASSEX w; //создаём экземпляр структуры WNDCLASSEX и начинаем её заполнять
	w.cbSize = sizeof(WNDCLASSEX);
	w.style = CS_HREDRAW | CS_VREDRAW; //стиль окна - перерисовываемое по х и по у
	w.lpfnWndProc = WndProc; //указатель на функцию окна
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;
	w.hInstance = hInstance; //идентификатор текущего приложения
	w.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	w.hCursor = LoadCursor(NULL, IDC_ARROW); //загружаем курсор в виде стрелки
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //цвет фона окна - белый
	w.lpszMenuName = 0; //и меню пока не будет
	w.lpszClassName = "win32app"; //имя программы
	w.hIconSm = LoadIcon(w.hInstance, IDI_APPLICATION);

	if(!RegisterClassEx(&w))
	{
		return 0;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindow("win32app", //Имя программы
		"Калькулятор", //Заголовок окна
		WS_OVERLAPPEDWINDOW&(~WS_MAXIMIZEBOX)&(~WS_THICKFRAME), //Стиль окна - перекрывающееся
		500, //положение окна на экране по х
		300, //по у
		265, //размеры по х
		340, //по у
		(HWND)NULL, //идентификатор родительского окна
		(HMENU)NULL, //идентификатор меню
		(HINSTANCE)hInstance, //идентификатор экземпляра программы
		(HINSTANCE)NULL); //отсутствие дополнительных параметров

	if (!hWnd)
	{
		return 0;
	}

	//Выводим окно из памяти на экран
	ShowWindow(hWnd, nCmdShow);
	//Обновим содержимое окна
	UpdateWindow(hWnd);

	//Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0)) { //Получаем сообщение из очереди
		TranslateMessage(&msg); //Преобразуем сообщения клавиш в символы
		DispatchMessage(&msg); //Передаём сообщение соответствующей функции окна
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton[26], hEdit, hBox, hBinEdit1, hBinEdit2, hBinBox;

	HDC hdc; //создаём контекст устройства
	PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода

	//Цикл обработки сообщений
	switch (messg)
	{
	case WM_CREATE:
		hEdit = CreateWindow("edit", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 10, 5, 230, 35, hWnd, (HMENU)ID_EDIT, hInst, 0);
		hButton[0] = CreateWindow("Button", "0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 150, 85, 30, hWnd, (HMENU)ID_BUTTON_0, hInst, 0);
		hButton[1] = CreateWindow("Button", "1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_1, hInst, 0);
		hButton[2] = CreateWindow("Button", "2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_2, hInst, 0);
		hButton[3] = CreateWindow("Button", "3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_3, hInst, 0);
		hButton[4] = CreateWindow("Button", "4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_4, hInst, 0);
		hButton[5] = CreateWindow("Button", "5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_5, hInst, 0);
		hButton[6] = CreateWindow("Button", "6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_6, hInst, 0);
		hButton[7] = CreateWindow("Button", "7", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_7, hInst, 0);
		hButton[8] = CreateWindow("Button", "8", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_8, hInst, 0);
		hButton[9] = CreateWindow("Button", "9", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_9, hInst, 0);
		hButton[10] = CreateWindow("Button", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 80, 43, 30, hWnd, (HMENU)ID_BUTTON_ADD, hInst, 0);
		hButton[11] = CreateWindow("Button", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 197, 80, 43, 30, hWnd, (HMENU)ID_BUTTON_SUB, hInst, 0);
		hButton[12] = CreateWindow("Button", "*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 115, 43, 30, hWnd, (HMENU)ID_BUTTON_MUL, hInst, 0);
		hButton[13] = CreateWindow("Button", "/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 197, 115, 43, 30, hWnd, (HMENU)ID_BUTTON_DIV, hInst, 0);
		hButton[14] = CreateWindow("Button", "=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 150, 90, 30, hWnd, (HMENU)ID_BUTTON_RES, hInst, 0);
		hButton[15] = CreateWindow("Button", "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 45, 43, 30, hWnd, (HMENU)ID_BUTTON_C, hInst, 0);
		hButton[16] = CreateWindow("Button", ".", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 150, 40, 30, hWnd, (HMENU)ID_BUTTON_DOT, hInst, 0);
		hButton[17] = CreateWindow("Button", "(", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 185, 43, 30, hWnd, (HMENU)ID_BUTTON_O_PAR, hInst, 0);
		hButton[18] = CreateWindow("Button", ")", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 197, 185, 43, 30, hWnd, (HMENU)ID_BUTTON_CL_PAR, hInst, 0);
		hButton[19] = CreateWindow("Button", "~", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 230, 40, 30, hWnd, (HMENU)ID_BUTTON_NEG, hInst, 0);
		hButton[20] = CreateWindow("Button", "&&", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 230, 40, 30, hWnd, (HMENU)ID_BUTTON_AND, hInst, 0);
		hButton[21] = CreateWindow("Button", "|", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 230, 40, 30, hWnd, (HMENU)ID_BUTTON_OR, hInst, 0);
		hButton[22] = CreateWindow("Button", "^", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 265, 40, 30, hWnd, (HMENU)ID_BUTTON_XOR, hInst, 0);
		hButton[23] = CreateWindow("Button", "<<", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 265, 40, 30, hWnd, (HMENU)ID_BUTTON_L_SHIFT, hInst, 0);
		hButton[24] = CreateWindow("Button", ">>", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 265, 40, 30, hWnd, (HMENU)ID_BUTTON_R_SHIFT, hInst, 0);
		hButton[25] = CreateWindow("Button", "<-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 197, 45, 43, 30, hWnd, (HMENU)ID_BUTTON_BACKSPACE, hInst, 0);

		hBox = CreateWindow("ComboBox", "", WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL | CBS_DROPDOWNLIST, 10, 185, 130, 140, hWnd, (HMENU)ID_BUTTON_BIN_OP, hInst, NULL);

		SendMessage(hBox, CB_ADDSTRING, 1,(LPARAM)"Обычный");
		SendMessage(hBox, CB_SETCURSEL, (WPARAM)0, 0L);
		SendMessage(hBox, CB_ADDSTRING, 1, (LPARAM)"Бинарный");

		for (int i = 19; i < 25; i++)
		{
			EnableWindow(hButton[i], false);
		}
		break;
		//сообщение рисования
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:

		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == ID_BUTTON_BIN_OP)
		{
			int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
			if (ItemIndex == 0)
			{
				choiceOfNormal = true;
				for (int i = 10; i < 14; i++)
				{
					EnableWindow(hButton[i], true);
				}
				for (int i = 16; i < 19; i++)
				{
					EnableWindow(hButton[i], true);
				}
				for (int i = 19; i < 25; i++)
				{
					EnableWindow(hButton[i], false);
				}
			}
			else
			{
				choiceOfNormal = false;
				for (int i = 10; i < 14; i++)
				{
					EnableWindow(hButton[i], false);
				}
				for (int i = 16; i < 19; i++)
				{
					EnableWindow(hButton[i], false);
				}
				for (int i = 19; i < 25; i++)
				{
					EnableWindow(hButton[i], true);
				}
			}
		}
		else if ((LOWORD(wParam) == ID_BUTTON_0) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, "0");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_1) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, "1");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_2) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, "2");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_3) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, "3");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_4) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, "4");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_5) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, "5");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_6) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, "6");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_7) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, "7");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_8) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, "8");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_9) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, "9");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_ADD) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, "+");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_SUB) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, "-");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_MUL) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, "*");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_DIV) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, "/");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_RES) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			if (choiceOfNormal == true)
			{
				Calculate(buf);
			}
			else
			{
				BinCalculate(buf);
			}
			SetWindowText(hEdit, buf);
			if (strcmp(buf ,"error") == 0)
			{
				MessageBox(hWnd, "Input error! Try again", "ERROR", MB_DEFBUTTON1);
			}
			else;
		}
		else if ((LOWORD(wParam) == ID_BUTTON_C) && (HIWORD(wParam) == BN_CLICKED))
		{
			SetWindowText(hEdit, "0");
			memset(buf, 0, sizeof buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_DOT) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, ".");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_O_PAR) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, "(");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_CL_PAR) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, ")");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_NEG) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, "~");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_AND) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, "&");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_OR) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, "|");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_XOR) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, "^");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_L_SHIFT) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, "<<");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_R_SHIFT) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, ">>");
			SetWindowText(hEdit, buf);
		}
		else if ((LOWORD(wParam) == ID_BUTTON_BACKSPACE) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (buf[0] != '\0' && buf[1] == '\0')
			{
				buf[0] = '0';
			}
			else if (!(*buf == '0' && 0 == buf[1]))
			{
				buf[strlen(buf) - 1] = '\0';
			}
			SetWindowText(hEdit, buf);
		}
		else ;
		break;
		//сообщение выхода - разрушение окна
	case WM_DESTROY:
		PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
		break;
	default:
		return DefWindowProc(hWnd, messg, wParam, lParam);
		//освобождаем очередь приложения от нераспознаных
	}
	return 0;
}