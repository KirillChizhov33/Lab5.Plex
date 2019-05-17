#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

struct TPoint
{
	int x, y;
	TPoint(int _x = 0, int _y = 0) :x(_x), y(_y){}

	String^ get(){
		String^ s = gcnew String("");
		s += "(";
		s += x;
		s += ",";
		s += y;
		s += ")";
		return s;
	}
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
		Pen ^pn = gcnew Pen(Color::Green, 3);
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
