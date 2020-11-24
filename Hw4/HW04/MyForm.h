/*
	HW02.cpp
	航太所碩一 P46091204 蔡承穎  Copyright (C) 2020
*/

#pragma once
#include <cstdlib>
#include <ctime>
#include <cstring>

namespace P46091204 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace P46091204;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
			arr = gcnew array<int>{0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5};		// Initialize
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::PictureBox^  pictureBox8;
	private: System::Windows::Forms::PictureBox^  pictureBox9;
	private: System::Windows::Forms::PictureBox^  pictureBox10;
	private: System::Windows::Forms::PictureBox^  pictureBox11;
	private: System::Windows::Forms::PictureBox^  pictureBox12;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ImageList^  imageList1;

	private: System::ComponentModel::IContainer^  components;





	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox12 = (gcnew System::Windows::Forms::PictureBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button1->Location = System::Drawing::Point(803, 379);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(182, 35);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(186, 144);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox2->Location = System::Drawing::Point(204, 12);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(186, 144);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 3;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
			this->pictureBox2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox2_MouseMove);
			// 
			// pictureBox3
			// 
			this->pictureBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox3->Location = System::Drawing::Point(396, 12);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(186, 144);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 4;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
			this->pictureBox3->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox3_MouseMove);
			// 
			// pictureBox4
			// 
			this->pictureBox4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox4->Location = System::Drawing::Point(588, 12);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(186, 144);
			this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox4->TabIndex = 5;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
			this->pictureBox4->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox4_MouseMove);
			// 
			// pictureBox5
			// 
			this->pictureBox5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox5->Location = System::Drawing::Point(12, 162);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(186, 144);
			this->pictureBox5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox5->TabIndex = 6;
			this->pictureBox5->TabStop = false;
			this->pictureBox5->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
			this->pictureBox5->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox5_MouseMove);
			// 
			// pictureBox6
			// 
			this->pictureBox6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox6->Location = System::Drawing::Point(204, 162);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(186, 144);
			this->pictureBox6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox6->TabIndex = 7;
			this->pictureBox6->TabStop = false;
			this->pictureBox6->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
			this->pictureBox6->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox6_MouseMove);
			// 
			// pictureBox7
			// 
			this->pictureBox7->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox7->Location = System::Drawing::Point(396, 162);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(186, 144);
			this->pictureBox7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox7->TabIndex = 8;
			this->pictureBox7->TabStop = false;
			this->pictureBox7->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
			this->pictureBox7->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox7_MouseMove);
			// 
			// pictureBox8
			// 
			this->pictureBox8->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox8->Location = System::Drawing::Point(588, 162);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(186, 144);
			this->pictureBox8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox8->TabIndex = 9;
			this->pictureBox8->TabStop = false;
			this->pictureBox8->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
			this->pictureBox8->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox8_MouseMove);
			// 
			// pictureBox9
			// 
			this->pictureBox9->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox9->Location = System::Drawing::Point(12, 312);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(186, 144);
			this->pictureBox9->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox9->TabIndex = 10;
			this->pictureBox9->TabStop = false;
			this->pictureBox9->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
			this->pictureBox9->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox9_MouseMove);
			// 
			// pictureBox10
			// 
			this->pictureBox10->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox10->Location = System::Drawing::Point(204, 312);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(186, 144);
			this->pictureBox10->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox10->TabIndex = 11;
			this->pictureBox10->TabStop = false;
			this->pictureBox10->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
			this->pictureBox10->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox10_MouseMove);
			// 
			// pictureBox11
			// 
			this->pictureBox11->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox11->Location = System::Drawing::Point(396, 312);
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->Size = System::Drawing::Size(186, 144);
			this->pictureBox11->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox11->TabIndex = 12;
			this->pictureBox11->TabStop = false;
			this->pictureBox11->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
			this->pictureBox11->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox11_MouseMove);
			// 
			// pictureBox12
			// 
			this->pictureBox12->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox12->Location = System::Drawing::Point(588, 312);
			this->pictureBox12->Name = L"pictureBox12";
			this->pictureBox12->Size = System::Drawing::Size(186, 144);
			this->pictureBox12->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox12->TabIndex = 13;
			this->pictureBox12->TabStop = false;
			this->pictureBox12->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
			this->pictureBox12->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox12_MouseMove);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->radioButton1->Location = System::Drawing::Point(6, 21);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(68, 24);
			this->radioButton1->TabIndex = 14;
			this->radioButton1->Text = L"玩家1";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->radioButton2->Location = System::Drawing::Point(6, 47);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(68, 24);
			this->radioButton2->TabIndex = 15;
			this->radioButton2->Text = L"玩家2";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->radioButton1);
			this->groupBox1->Controls->Add(this->radioButton2);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->groupBox1->Location = System::Drawing::Point(797, 26);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 78);
			this->groupBox1->TabIndex = 16;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"先手( O )";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 21.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(796, 427);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(206, 36);
			this->label1->TabIndex = 17;
			this->label1->Text = L"00:00:00.0000";
			// 
			// timer1
			// 
			this->timer1->Interval = 1;	// ms
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Location = System::Drawing::Point(0, 496);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(994, 22);
			this->statusStrip1->TabIndex = 18;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(8, 510);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 20);
			this->label2->TabIndex = 19;
			this->label2->Text = L"玩家";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label3->Location = System::Drawing::Point(83, 510);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(109, 20);
			this->label3->TabIndex = 20;
			this->label3->Text = L"滑鼠目前位置:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label4->Location = System::Drawing::Point(198, 509);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(31, 20);
			this->label4->TabIndex = 21;
			this->label4->Text = L"( , )";
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList1->Images->SetKeyName(0, L"Eevee.jpg");
			this->imageList1->Images->SetKeyName(1, L"Pyro.jpg");
			this->imageList1->Images->SetKeyName(2, L"Rainer.jpg");
			this->imageList1->Images->SetKeyName(3, L"Sakura.jpg");
			this->imageList1->Images->SetKeyName(4, L"Sparky.jpg");
			this->imageList1->Images->SetKeyName(5, L"Tamao.jpg");
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(994, 518);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->pictureBox12);
			this->Controls->Add(this->pictureBox11);
			this->Controls->Add(this->pictureBox10);
			this->Controls->Add(this->pictureBox9);
			this->Controls->Add(this->pictureBox8);
			this->Controls->Add(this->pictureBox7);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
// 參數設定
	private:
		PictureBox^ c1 = nullptr;
		PictureBox^ c2 = nullptr;

		bool start;
		int sum;						// 檢查1~6是否找到
		int score1, score2;				// 紀錄Player 1, 2分數
		int s1, s2;						// 紀錄數字
		array<int> ^arr;				// 存放卡片位置

		long long Start_Time;

	public:
		void Start();
		void Stop();
		void Shuffle(array<int> ^arr, size_t n);	// 洗牌函式
		void Display();								// 顯示圖片


private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {	
	if (timer1->Enabled == true) {
		Stop();
		button1->Text = "Start";
	}
	else {
		Start();
		button1->Text = "Stop";
	}
}

// 滑鼠指到的picture的index涵式 ( , )
private: System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	label4->Text = "(1,1)";
}
private: System::Void pictureBox2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	label4->Text = "(1,2)";
}
private: System::Void pictureBox3_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	label4->Text = "(1,3)";
}
private: System::Void pictureBox4_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	label4->Text = "(1,4)";
}
private: System::Void pictureBox5_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	label4->Text = "(2,1)";
}
private: System::Void pictureBox6_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	label4->Text = "(2,2)";
}
private: System::Void pictureBox7_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	label4->Text = "(2,3)";
}
private: System::Void pictureBox8_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	label4->Text = "(2,4)";
}
private: System::Void pictureBox9_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	label4->Text = "(3,1)";
}
private: System::Void pictureBox10_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	label4->Text = "(3,2)";
}
private: System::Void pictureBox11_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	label4->Text = "(3,3)";
}
private: System::Void pictureBox12_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	label4->Text = "(3,4)";
}
private: System::Void MyForm_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	label4->Text = "Nan";
}



private: System::Void pictureBox_Click(System::Object^  sender, System::EventArgs^  e) {
	if (start != false) {	// 判斷是否按下開始
		// 1~3行的過程是將pictureBox的字刪去，只取後面的index
		PictureBox^ pb = safe_cast<PictureBox^>(sender);
		String^ s = pb->Name->Replace("pictureBox", "");
		int index = System::Convert::ToInt32(s);

		pb->Image = imageList1->Images[arr[index - 1]];	// 根據打亂的arr顯示圖片

		if (c1 == nullptr) {		// 翻開第一張牌
			c1 = pb;
			pb->Enabled = false;	// 關掉，避免再按
			s1 = arr[index - 1];
		}
		else {						// 翻開第二張牌
			c2 = pb;
			pb->Enabled = false;	// 關掉，避免再按
			s2 = arr[index - 1];

			if (s1 != s2) {			// 如果不一樣
				c1->Enabled = true;
				c2->Enabled = true;
				Console::WriteLine(L"Not Match !");			// 不Match
				System::Threading::Thread::Sleep(500);		// 等待0.5秒後覆蓋牌
				c1->Image = nullptr;
				c2->Image = nullptr;

				// 交換Player
				if (radioButton1->Checked == true) {
					radioButton1->Checked = false;
					radioButton2->Checked = true;
					label2->Text = "玩家2";
				}
				else {
					radioButton1->Checked = true;
					radioButton2->Checked = false;
					label2->Text = "玩家1";
				}
			}
			else {					// 如果一樣
				Console::WriteLine(L"Match !");
				// 判斷是誰得分
				if (radioButton1->Checked == true) {
					score1++;
					Console::WriteLine(L"Player1 +1");
				}
				else {
					score2++;
					Console::WriteLine(L"Player2 +1");
				}
				sum++;				// 配對種類++
				if (sum == 6) {		// 配對種類最多6種
					if (score1 > score2)
						MessageBox::Show("Player 1 win!", "遊戲結束");
					else if (score1 < score2)
						MessageBox::Show("Player 2 win!", "遊戲結束");
					else
						MessageBox::Show("Tie !");
				}
			}
			c1 = nullptr;			// 指回空指標才會是下一回合
			c2 = nullptr;
		}
	}
}

private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	long long Interval = DateTime::Now.Ticks - Start_Time;	// 按下start會記錄一開始時間，timer每毫秒都會呼叫一次，並計算時間
	TimeSpan Interval_Span = TimeSpan(Interval);			// 轉換成timespan，處理方便
	label1->Text = Convert::ToString(Interval_Span);		// 最後顯示結果
}
};
}

void P46091204::MyForm::Start() {
	Shuffle(arr, 12);    // 打亂數列
	
	if (MessageBox::Show("是否亮牌", "遊戲開始", MessageBoxButtons::YesNo, MessageBoxIcon::Information) == System::Windows::Forms::DialogResult::Yes) {
		Display();
	}

	Start_Time = DateTime::Now.Ticks;
	start = true;
	sum = 0, score1 = 0, score2 = 0;

	if (radioButton1->Checked == true) {
		label2->Text = "玩家1";
	}
	else {
		label2->Text = "玩家2";
	}
	
	groupBox1->Enabled = false;
	timer1->Enabled = true;
	pictureBox1->Enabled = true;
	pictureBox2->Enabled = true;
	pictureBox3->Enabled = true;
	pictureBox4->Enabled = true;
	pictureBox5->Enabled = true;
	pictureBox6->Enabled = true;
	pictureBox7->Enabled = true;
	pictureBox8->Enabled = true;
	pictureBox9->Enabled = true;
	pictureBox10->Enabled = true;
	pictureBox11->Enabled = true;
	pictureBox12->Enabled = true;
}

void P46091204::MyForm::Stop() {
	label2->Text = "玩家";
	timer1->Enabled = false;
	groupBox1->Enabled = true;

	pictureBox1->Image = nullptr;
	pictureBox2->Image = nullptr;
	pictureBox3->Image = nullptr;
	pictureBox4->Image = nullptr;
	pictureBox5->Image = nullptr;
	pictureBox6->Image = nullptr;
	pictureBox7->Image = nullptr;
	pictureBox8->Image = nullptr;
	pictureBox9->Image = nullptr;
	pictureBox10->Image = nullptr;
	pictureBox11->Image = nullptr;
	pictureBox12->Image = nullptr;

	pictureBox1->Enabled = false;
	pictureBox2->Enabled = false;
	pictureBox3->Enabled = false;
	pictureBox4->Enabled = false;
	pictureBox5->Enabled = false;
	pictureBox6->Enabled = false;
	pictureBox7->Enabled = false;
	pictureBox8->Enabled = false;
	pictureBox9->Enabled = false;
	pictureBox10->Enabled = false;
	pictureBox11->Enabled = false;
	pictureBox12->Enabled = false;
}

void P46091204::MyForm::Shuffle(array<int> ^arr, size_t n) {	// 簡單手寫shuffle打亂
	srand(time(0));
	if (n > 1) {
		size_t i;
		for (i = 0; i<n; i++) {
			size_t j = rand() / (RAND_MAX / (n));
			int t = arr[j];
			arr[j] = arr[i];
			arr[i] = t;
		}
	}
}

// Bonus
void P46091204::MyForm::Display() {
	for (int i = 1; i <= 12; i++) {
		Console::WriteLine(Convert::ToString("顯示第" + i + "張牌"));
		String^ name = Convert::ToString("pictureBox" + i);
		PictureBox^ pb = (PictureBox^)this->Controls->Find(name, true)[0];
		pb->Image = imageList1->Images[arr[i - 1]];
		System::Threading::Thread::Sleep(500);
		Application::DoEvents();	// 這裡有個坑，最後才發現，否則無法處理在Queue裡的圖片
		pb->Image = nullptr;
	}
}