#pragma once
#include"TIntegrator.h"
#include"GeneralProcessModel.h"
#include <iostream>
#include<fstream>
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
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
			AllocConsole();
			freopen("CON", "w", stdout);
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
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  XYChart;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  XChart;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  VChart;




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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint1 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(0,
				0));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->Моделировать = (gcnew System::Windows::Forms::Button());
			this->XYChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->XChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->VChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XYChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VChart))->BeginInit();
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
			// XYChart
			// 
			chartArea1->Name = L"ChartArea1";
			this->XYChart->ChartAreas->Add(chartArea1);
			this->XYChart->Location = System::Drawing::Point(112, 12);
			this->XYChart->Name = L"XYChart";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->Name = L"Series1";
			series1->Points->Add(dataPoint1);
			this->XYChart->Series->Add(series1);
			this->XYChart->Size = System::Drawing::Size(257, 210);
			this->XYChart->TabIndex = 1;
			this->XYChart->Text = L"chart1";
			// 
			// XChart
			// 
			chartArea2->Name = L"ChartArea1";
			this->XChart->ChartAreas->Add(chartArea2);
			this->XChart->Location = System::Drawing::Point(375, 12);
			this->XChart->Name = L"XChart";
			series2->ChartArea = L"ChartArea1";
			series2->Name = L"Series1";
			this->XChart->Series->Add(series2);
			this->XChart->Size = System::Drawing::Size(257, 210);
			this->XChart->TabIndex = 1;
			this->XChart->Text = L"chart1";
			// 
			// VChart
			// 
			chartArea3->Name = L"ChartArea1";
			this->VChart->ChartAreas->Add(chartArea3);
			this->VChart->Location = System::Drawing::Point(638, 12);
			this->VChart->Name = L"VChart";
			series3->ChartArea = L"ChartArea1";
			series3->Name = L"Series1";
			this->VChart->Series->Add(series3);
			this->VChart->Size = System::Drawing::Size(257, 210);
			this->VChart->TabIndex = 1;
			this->VChart->Text = L"chart1";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(955, 477);
			this->Controls->Add(this->VChart);
			this->Controls->Add(this->XChart);
			this->Controls->Add(this->XYChart);
			this->Controls->Add(this->Моделировать);
			this->Name = L"Form1";
			this->Text = L"Самая бесполезная программа";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XYChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VChart))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Моделировать_Click(System::Object^  sender, System::EventArgs^  e) {
		string outFileName = "out.txt";
		ofstream fout(outFileName, ios_base::out | ios_base::trunc);
		if (!fout) { cout << "Ошибка открытия файла\n";  system("pause"); }
		fout.setf(ios::fixed);

		TDormanPrinceIntegrator integr(1e-12);
		double T0 = 0.0;
		//double T1 = 11 * 60 * 60 + 15 * 60;
		double T1 = 150;

		GeneralProcessModel model(T0,T1);
		integr.Run(model);
		for (int i = 0; i < model.Result.size(); i++)
		{
			TVector str = model.Result.front();
			model.Result.pop_front();
			for (int j = 0; j < str.getSize(); j++)
			{
				fout << str[j] << " ";
			}
			fout << endl;
		}
		fout.close();
		
	}
	};
}
