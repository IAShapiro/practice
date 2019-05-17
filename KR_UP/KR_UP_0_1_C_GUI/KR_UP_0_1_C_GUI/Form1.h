#pragma once
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

namespace CppCLR_WinformsProjekt {

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

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ListBox^  listBox1;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(130, 30);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(325, 20);
			this->textBox1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F, System::Drawing::FontStyle::Bold));
			this->button1->Location = System::Drawing::Point(200, 57);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(178, 40);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Ïðî÷åñòü ôàéë";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(131, 119);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(323, 264);
			this->listBox1->TabIndex = 2;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(600, 435);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		listBox1->Items->Clear();
		if (textBox1->Text != "")
		{
			System::String^ Line = textBox1->Lines[0];
			msclr::interop::marshal_context context;
			std::ifstream in(context.marshal_as<std::string>(Line));
			if (in.is_open())
			{
				std::map<int, std::string> h2;

				std::string tmp;
				while (getline(in, tmp))
				{
					char * next = nullptr, *p = strtok_s(&tmp[0], "\n EOF", &next);

					while (p != nullptr)
					{
						h2[atoi(p)] = line_of_div(decomposition(atoi(p)), atoi(p));

						p = strtok_s(nullptr, "\n EOF", &next);
					}
				}

				for (auto& it : h2)
				{
					listBox1->Items->Add(gcnew System::String(it.second.c_str()));
				}

				in.close();
			}
		}
		
	}
	};
}
