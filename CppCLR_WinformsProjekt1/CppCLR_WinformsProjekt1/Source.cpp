// CppCLR_WinformsProjekt.cpp: Hauptprojektdatei.

// #include "stdafx.h"
// using namespace System;

//int main(array<System::String ^> ^args)
//{
//    Console::WriteLine(L"Hello World");
//    return 0;
//}
#include "stdafx.h"
#include "Form1.h"
#include "Concert.h"
#include <fstream>

using namespace System;
using namespace System::Windows::Forms;
using namespace Source;

[STAThread]
// int main(array<String^>^ args) { // Kann Fehler nach 'using namespace std;' verursachen
int main() {
	std::ifstream fin("1.txt");
	while (!fin.eof())
	{
		fin >> A;
	}

	A.sort_name();

	fin.close();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Source::Form1()); // "Source" noch anpassen

	return 0;
}