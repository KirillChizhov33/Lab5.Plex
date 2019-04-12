#pragma once

namespace ProjectUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	#pragma once
	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			int x, y;
			InitializeComponent();
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
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(384, 325);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);

		}
#pragma endregion
		private: System::Void panel1_paint(System::Object ^ sender, System::Windows::Forms::PaintEventArgs^  e)
	{
		Graphics ^g = e->Graphics;
		Pen ^ p = gcnew Pen(Color::Red, 3);
		Pen ^ c = gcnew Pen(Color::Blue, 3);
		Pen ^ k = gcnew Pen(Color::Red, 3);
		g->DrawLine(c, 50, 50, 120, 80);
		g->DrawEllipse(p, 45, 45, 10, 10);
		g->DrawEllipse(k, 115, 75, 10, 10);
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
	};

} // alt+enter 
