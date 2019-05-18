#pragma once
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

namespace CppCLR_WinformsProjekt {

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
			this->textBox1->Location = System::Drawing::Point(177, 51);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(330, 20);
			this->textBox1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(240, 89);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(202, 33);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Ñ÷èòàòü ôàéë";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(180, 149);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(326, 160);
			this->listBox1->TabIndex = 2;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(686, 358);
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
				std::multimap<int, int> A;
				
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
					std::string t = std::to_string(A.count(j));
					auto range = A.equal_range(j);
					for (auto k = range.first; k != range.second; ++k)
					{
						t += " " + std::to_string(k->second);
					}
					listBox1->Items->Add(gcnew System::String(t.c_str()));
				}

				in.close();
			}
		}
	}
	};
}
