#include <stdio.h>
#include "Plex.h"
#pragma once

namespace PlexUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		int flag;
		int x, y;
		bool move;
		TPoint *p_move;
		TPoint *p_con1;
		TPoint *p_con2;
		TPoint *p1, *p2, *p3, *p4, *p5;
		ChartPoint *sp1, *sp2, *sp3, *sp4, *sp5;
		ChartLine *l1, *l2, *l3, *l4, *l5;

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	public:
		Chart *s;
		MyForm(void)
		{
			flag = 1;
			p1 = new TPoint(80, 50);
			p2 = new TPoint(150, 50);
			p3 = new TPoint(220, 50);
			p4 = new TPoint(220, 200);
			p5 = new TPoint(80, 200);
			sp1 = new ChartPoint(p1);
			sp2 = new ChartPoint(p2);
			sp3 = new ChartPoint(p3);
			sp4 = new ChartPoint(p4);
			sp5 = new ChartPoint(p5);
			l1 = new ChartLine(sp2, sp3);
			l2 = new ChartLine(l1, sp1);
			l3 = new ChartLine(sp5, sp2);
			l4 = new ChartLine(sp4, l3);
			l5 = new ChartLine(l2, l4);
			s = l5;
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(329, 277);
			this->panel1->TabIndex = 0;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint);
			this->panel1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::panel1_MouseDown);
			this->panel1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::panel1_MouseMove);
			this->panel1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::panel1_MouseUp);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(363, 12);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(94, 46);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Don\'t move";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button3_MouseClick);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(363, 64);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(94, 46);
			this->button4->TabIndex = 4;
			this->button4->Text = L"Move";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button4_MouseClick);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(363, 116);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(94, 46);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Добавить точку";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button1_MouseClick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(363, 169);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 6;
			this->label1->Text = L"label1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(483, 314);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->panel1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
		Graphics ^g = e->Graphics;
		Pen ^ p = gcnew Pen(Color::Red, 3);
		s->paint(g);
		if (p_move != NULL)
		{
			Pen ^ c = gcnew Pen(Color::Blue, 3);
			g->DrawEllipse(c, p_move->x - 5, p_move->y - 5, 10, 10);
		}
	}
	private: System::Void panel1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		move = false;
		p_move = NULL; //Не могу отпустить выбранную точку
		panel1->Refresh();
		if(flag == 0)
		{
			p_con2 = s->find(e->X, e->Y);
			label1->Text = "";
			if(p_con1 != NULL)
			{
				label1->Text += p_con1->get();
			}

			if(p_con2 != NULL)
			{
				label1->Text += "->"+ p_con2->get();
			}

		}
	}
	private: System::Void panel1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		x = e->X;
		y = e->Y;
		panel1->Refresh();
		move = ((e->X - 5 <= x) && (e->X + 5 >= x) && (e->Y - 5 <= y) && (e->Y + 5 >= y));
		p_move = s->find(e->X, e->Y);
		if(flag == 0)
		{
			p_con1 = s->find(e->X, e->Y);
		}
	}
	private: System::Void panel1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if(flag == 1)
		{
			if (move)
			{
				x = e->X;
				y = e->Y;
			}
			if ((move) || (p_move != NULL))
			{
				panel1->Refresh(); //Без этого условия есть только результат перемещения
			}
			if (p_move != NULL)
			{
				p_move->x = e->X;
				p_move->y = e->Y;
			}
		}
	}
	/*private: System::Void button1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		TPoint *tmp;
		ChartPoint *stmp;
		ChartLine *ltmp;
		tmp = new TPoint(150, 150);
		stmp = new ChartPoint(tmp);
		ltmp = new ChartLine(l5, stmp);
		s = ltmp;
		panel1->Refresh();
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
			s = l5;
			panel1->Refresh();
	}*/
	private: System::Void button3_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		   flag = 0;
	}
	private: System::Void button4_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		   flag = 1;
	}
	private: System::Void button1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
			TPoint *tmp;
			ChartPoint *stmp;
			ChartLine *ltmp;
			tmp = new TPoint(150, 150);
			stmp = new ChartPoint(tmp);
			ltmp = new ChartLine(l5, stmp);
			s = ltmp;
			panel1->Refresh();
	}
};
}
