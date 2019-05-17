#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <msclr\marshal_cppstd.h>

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
			this->textBox1->Location = System::Drawing::Point(134, 59);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(366, 20);
			this->textBox1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F, System::Drawing::FontStyle::Bold));
			this->button1->Location = System::Drawing::Point(188, 95);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(252, 44);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Ïðî÷åñòü ôàéë";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(134, 167);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(365, 199);
			this->listBox1->TabIndex = 2;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(633, 418);
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
					listBox1->Items->Add(gcnew System::String(it.second.c_str()));
				}

				in.close();
			}
		}
	}
	};
}
