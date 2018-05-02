#pragma once
#include"TIntegrator.h"
#include"GeneralProcessModel.h"
#include <iostream>
#include<fstream>
using namespace std;
namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung fьr Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufьgen.
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
	private: System::Windows::Forms::Button^  Моделировать;
	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode fьr die Designerunterstьtzung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geдndert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Моделировать = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Моделировать
			// 
			this->Моделировать->Location = System::Drawing::Point(12, 12);
			this->Моделировать->Name = L"Моделировать";
			this->Моделировать->Size = System::Drawing::Size(94, 23);
			this->Моделировать->TabIndex = 0;
			this->Моделировать->Text = L"Моделировать";
			this->Моделировать->UseVisualStyleBackColor = true;
			this->Моделировать->Click += gcnew System::EventHandler(this, &Form1::Моделировать_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(528, 286);
			this->Controls->Add(this->Моделировать);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Моделировать_Click(System::Object^  sender, System::EventArgs^  e) {
		string outFileName = "out.txt";
		TDormanPrinceIntegrator integr(1e-12);
		double T0 = 0.0;
		double T1 = 0.0;

		GeneralProcessModel model(T0,T1);

	}
	};
}
