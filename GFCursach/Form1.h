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
	/// Zusammenfassung f�r Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzuf�gen.
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
	private: System::Windows::Forms::Button^  ������������;
	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode f�r die Designerunterst�tzung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor ge�ndert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->������������ = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// ������������
			// 
			this->������������->Location = System::Drawing::Point(12, 12);
			this->������������->Name = L"������������";
			this->������������->Size = System::Drawing::Size(94, 23);
			this->������������->TabIndex = 0;
			this->������������->Text = L"������������";
			this->������������->UseVisualStyleBackColor = true;
			this->������������->Click += gcnew System::EventHandler(this, &Form1::������������_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(528, 286);
			this->Controls->Add(this->������������);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void ������������_Click(System::Object^  sender, System::EventArgs^  e) {
		string outFileName = "out.txt";
		TDormanPrinceIntegrator integr(1e-12);
		double T0 = 0.0;
		double T1 = 0.0;

		GeneralProcessModel model(T0,T1);

	}
	};
}
