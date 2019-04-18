#include <stdio.h>
#pragma once

namespace ProjectUI {

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
		int x, y;
		bool move;
		TPoint *p_move;
		TPoint *p1, *p2, *p3, *p4;
		ChartPoint *sp1, *sp2, *sp3, *sp4;
		ChartLine *l1, *l2, *l3;
		Chart *s;
		MyForm(void)
		{
			p1 = new TPoint(50, 50);
			p2 = new TPoint(150, 50);
			p3 = new TPoint(50, 150);
			p4 = new TPoint(150, 150);
			sp1 = new ChartPoint(p1);
			sp2 = new ChartPoint(p2);
			sp3 = new ChartPoint(p3);
			sp4 = new ChartPoint(p4);
			l1 = new ChartLine(sp1, sp2); 
			l2 = new ChartLine(l1, sp3);
			l3 = new ChartLine(l2, sp4);
			s = l3;
			InitializeComponent();
			//move = false;
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
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
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(27, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(332, 125);
			this->panel1->TabIndex = 0;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint);
			this->panel1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::panel1_MouseDown);
			this->panel1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::panel1_MouseMove);
			this->panel1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::panel1_MouseUp);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(394, 261);
			this->Controls->Add(this->panel1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);

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
	private: System::Void panel1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		x = e->X;
		y = e->Y;
		panel1->Refresh();
		move = ((e->X - 5 <= x) && (e->X + 5 >= x) && (e->Y - 5 <= y) && (e->Y + 5 >= y));
		p_move = s->find(e->X, e->Y);
	}
	private: System::Void panel1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
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
	private: System::Void panel1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		move = false;
		p_move = NULL; //Не могу отпустить выбранную точку
		panel1->Refresh(); 
	}
	private: System::Void button1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		TPoint *tmp;
		ChartPoint *stmp;
		tmp = new TPoint(100, 100);
		stmp = new ChartPoint(tmp);
		s = stmp;
	}
	};
	struct TPoint
	{
		int x, y;
		TPoint(int _x = 0, int _y = 0) :x(_x), y(_y){}
	};
	class Chart
	{
	public:
		virtual TPoint * paint(Graphics ^g) = 0;
		virtual TPoint * find(int _x, int _y) = 0;
	};
	class ChartPoint : public Chart
	{
		TPoint * p;
	public:
		ChartPoint(TPoint * _p) : p(_p){}
		virtual TPoint * paint(Graphics ^g)
		{
			Pen ^pn = gcnew Pen(Color::Red, 3);
			g->DrawEllipse(pn, p->x - 5, p->y - 5, 10, 10); // координаты, ширина, высота
			return p;
		}
		virtual TPoint * find(int _x, int _y)
		{
			if ((p->x - 5 <= _x) && (p->x + 5 >= _x) && (p->y - 5 <= _y) && (p->y + 5 >= _y))
			{
				return p;
			}
			else return NULL;
		}
	};
	class ChartLine : public Chart
	{
		Chart *l, *r;
	public:
		ChartLine(Chart *_l, Chart *_r) : r(_r), l(_l){}
		virtual TPoint * paint(Graphics ^g)
		{
			Pen ^pn = gcnew Pen(Color::Black, 3);
			TPoint *pl = l->paint(g);
			TPoint *pr = r->paint(g);
			g->DrawLine(pn, pl->x, pl->y, pr->x, pr->y); //координаты 2 точек
			return pl;
		}
		virtual TPoint * find(int _x, int _y)
		{
			TPoint *pl = l->find(_x, _y);
			TPoint *pr = r->find(_x, _y);
			if (pl != NULL)
			{
				return pl;
			}
			return pr;
		}
	};
}
