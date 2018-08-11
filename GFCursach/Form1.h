#pragma once
#include"TIntegrator.h"
#include"GeneralProcessModel.h"
#include <iostream>
#include<fstream>
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>

#include"GaussianDistribution.h"
#include"WhiteNoiseGenerator.h"
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
		int FormIncreaseProgressBar(int step)
		{
			// Increment the value of the ProgressBar a value of one each time.
			progressBar1->Increment(step);

			// Display the textual value of the ProgressBar in the StatusBar control's first panel.
			this->progressBar1->Text = String::Concat(progressBar1->Value, "% Completed");

			if (progressBar1->Value == progressBar1->Maximum)
				progressBar1->Value = progressBar1->Maximum;
			return 0;
		}
	System::Windows::Forms::ProgressBar^  progressBar1;

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
	//private: System::Windows::Forms::ProgressBar^  progressBar1;




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
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
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
			// progressBar1
			// 
			this->progressBar1->ForeColor = System::Drawing::Color::Lime;
			this->progressBar1->Location = System::Drawing::Point(489, 442);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(454, 23);
			this->progressBar1->TabIndex = 2;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(955, 477);
			this->Controls->Add(this->progressBar1);
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
		this->progressBar1->Value = 0;
		string outFileName = "out.txt";
		ofstream fout(outFileName, ios_base::out | ios_base::trunc);
		if (!fout) { cout << "Ошибка открытия файла\n";  system("pause"); }
		fout.setf(ios::fixed);

		TDormanPrinceIntegrator integr(1e-5);
		double T0 = 0.0;
		double T1 = 11 * 60 * 60 + 15 * 60;
		//T1 = 100.0;
		double smpl_inc = 60.0;

		this->progressBar1->Minimum = T0;
		this->progressBar1->Maximum= T1;
		this->progressBar1->Step = smpl_inc;

		vector<double> m = { 1,3,3 };
		vector<double> sig = { 0.5,1,3 };
		GaussianDistribution distrib(m, sig);
		vector<double> cur;
		TVector vec;
		for (size_t i = 0; i < 6; i++)
		{
			cur = distrib.getRndByDefaultParameters();
			vec = distrib.getRndVectByDefaultParameters();
			vec.print();
			cur = cur;
			vec = vec;
		}

		WhiteNoiseGenerator wng (0, 2.6, 0.1, m, sig);
		double t = .0;
		while (t < 2.6)
		{
			cur = wng.getStdVectVal(t);
			t += 0.04;
		}


		GeneralProcessModel model(T0,T1,smpl_inc);

		
		integr.Run(model);

		//печать заголовков для глонаса
		for (int i = 0; i < model.GLONASS.getSatNumber(); i++)
			fout << "Xglon_" <<i<< " " << "Yglon_" << i << " " << "Zglon_" << i << " " << "Vxglon_" << i << " " << "Vyglon_" << i << " " << "Vzglon_" << i << " ";
		//печать заголовков для GPS
		for (int i = 0; i < model.GPS.getSatNumber(); i++)
			fout << "Xgps_" << i << " " << "Ygps_" << i << " " << "Zgps_" << i << " " << "Vxgps_" << i << " " << "Vygps_" << i << " " << "Vzgps_" << i << " ";
		//печать заголовка для ФФ
		fout << "FF_ro FF_dro";

		//печать заголовков для спутника-потребителя
		fout << "Xcon" << " " << "Ycon" << " " << "Zcon" << " " << "Vxcon" << " " << "Vycon" << " " << "Vzcon" << " " << "t"<<endl;



		while (!model.Result.empty())
		{
			FormIncreaseProgressBar(smpl_inc);
			TVector str = model.Result.front();
			for (int j = 0; j < str.getSize(); j++)
			{
				fout << str[j] << " ";
			}
			fout << endl;
			model.Result.pop_front();

		}
		//for (int i = 0; i < model.Result.size(); i++)
		//{

		//}
		fout.close();
		this->progressBar1->Text = "DONE.";
		
	}
	};


}
