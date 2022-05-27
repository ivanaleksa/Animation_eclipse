#pragma once
#include "Graphics.h"

int heg = 720, wid = 1320;

class Grass {
private:
	COLORREF color_near, color_far; // цвет у ближней и дальней лужайки
	POINT coord_first[3] = { 0, 350, 0, heg, wid - 200, heg },
		coord_second[4] = { 450, 500,  wid - 200, heg, wid, heg, wid, 300 };
public:
	Grass(COLORREF col_, COLORREF col2_) :color_near(col_), color_far(col2_) {
		gr::InitGraphics(hWnd);
		gr::Set_pen(RGB(0, 0, 0), 3);
		gr::Set_brush(color_far, true);
		Polygon(gr::dc, coord_second, 4);
		gr::Set_pen(RGB(0, 0, 0), 3);
		gr::Set_brush(color_near, true);
		Polygon(gr::dc, coord_first, 3);
	}
};

class Sky {
private:
	COLORREF color;
	POINT coord[5] = { 0, 0, 0, 348, 450, 497, wid, 298, wid, 0 };
public:
	Sky(COLORREF col_) :color(col_) {}
	void VisSky(COLORREF new_col) {
		gr::InitGraphics(hWnd);
		gr::Set_pen(new_col, 1);
		gr::Set_brush(new_col, true);
		Polygon(gr::dc, coord, 5);
	}
};

class Sun {
private:
	COLORREF color;
	int x, y, r;
public:
	Sun(COLORREF col, int r_, int x_, int y_) :color(col), r(r_), x(x_), y(y_) {}
	void VisSun() {
		gr::InitGraphics(hWnd);
		gr::Set_pen(color, 0);
		gr::Set_brush(color, true);
		Ellipse(gr::dc, x - r, y - r, x + r, y + r);
	}
};

class Tree {
private:
	COLORREF col_stem, col_leaves;
	int x, y; // координаты середины низа стебля
public:
	Tree(COLORREF col_stem_, COLORREF col_leav, int x_, int y_) : col_stem(col_stem_), col_leaves(col_leav), x(x_), y(y_)
	{
		gr::InitGraphics(hWnd);

		// отрисовка стебля по уровням
		gr::Set_brush(col_stem, true);
		gr::Set_pen(RGB(0, 0, 0), 1);
		POINT first_step[4] = { x - 50 + 70, y - 10 + 70, x - 50 + 70, y + 70, x + 50 + 70, y + 70, x + 50 + 70, y - 10 + 70 };
		Polygon(gr::dc, first_step, 4);

		gr::Set_brush(col_stem + 30, true);
		gr::Set_pen(RGB(0, 0, 0), 1);
		POINT second_step[4] = { x + 5 - 30 + 70, y - 10 - 7 + 70, x + 5 - 30 + 70, y - 7 + 70, x + 5 + 30 + 70, y - 7 + 70, x + 5 + 30 + 70, y - 10 - 7 + 70 };
		Polygon(gr::dc, second_step, 4);

		gr::Set_brush(col_stem - 20, true);
		gr::Set_pen(RGB(0, 0, 0), 1);
		POINT third_step[4] = { x + 5 - 15 + 70, y - 17 - 40 + 70, x + 5 - 15 + 70, y - 15 + 70, x + 5 + 15 + 70, y - 15 + 70, x + 5 + 15 + 70, y - 17 - 40 + 70 };
		Polygon(gr::dc, third_step, 4);

		// отрисовка листвы
		int y_i = y - 57 + 70, k = 20, count = 0;
		x += 70;
		while (count < 5) { // нижняя часть (увеличение ширины)
			gr::Set_brush(col_leaves, true);
			gr::Set_pen(RGB(0, 0, 0), 1);
			POINT third_step[4] = { x - k, y_i - 8, x - k, y_i, x + k, y_i, x + k, y_i - 8 };
			Polygon(gr::dc, third_step, 4);
			k += 13;
			count++;
			y_i -= 8;
		}

		// верхняя часть (увеличение ширины)
		count = 0;
		while (count < 5) {
			gr::Set_brush(col_leaves, true);
			gr::Set_pen(RGB(0, 0, 0), 1);
			POINT third_step[4] = { x - k, y_i - 8, x - k, y_i, x + k, y_i, x + k, y_i - 8 };
			Polygon(gr::dc, third_step, 4);
			k -= 13;
			count++;
			y_i -= 8;
		}
	}
};

class Cloud {
private:
	int x, y; // кооринаты низа середины
	POINT a[4] = { x - 60, y - 30, x - 60, y, x + 60, y, x + 60, y - 30 };
public:
	Cloud(int x_, int y_) : x(x_), y(y_) {
		gr::InitGraphics(hWnd);
		gr::Set_pen(RGB(255, 255, 255), 1);
		gr::Set_brush(RGB(255, 255, 255), true);
		Polygon(gr::dc, a, 4);
		Ellipse(gr::dc, x - 70, y - 30, x - 50, y);
		Ellipse(gr::dc, x + 70, y - 30, x + 50, y);
		Ellipse(gr::dc, x - 65, y - 50, x, y);
		Ellipse(gr::dc, x - 5, y - 65, x + 65, y);
	}
};

class Moon {
private:
	int x, y, r;
	COLORREF col;
public:
	Moon(COLORREF col_, int r_, int x_, int y_) : col(col_), r(r_), x(x_), y(y_) {}
	void VisMoon(int new_x, COLORREF new_col) {
		gr::InitGraphics(hWnd);
		gr::Set_pen(new_col, 0);
		gr::Set_brush(new_col, true);
		Ellipse(gr::dc, new_x - r, y - r, new_x + r, y + r);
	}
};

class House {
private:
	COLORREF main, roof, windows_off, windows_on;
	int x, y; // координаты сереидны основания
	int size; // половина стороны основания
public:
	House(COLORREF main_, COLORREF roof_, COLORREF windows_off_, COLORREF windows_on_, int x_, int y_, int size_) :
		main(main_), roof(roof_), windows_off(windows_off_), windows_on(windows_on_), x(x_), y(y_), size(size_) {}
	// отрисовка здания
	void VisMain() {
		gr::InitGraphics(hWnd);
		gr::Set_pen(RGB(0, 0, 0), 4);
		gr::Set_brush(main, true);
		POINT a[4] = { x - size, y - size * 2, x - size, y, x + size, y, x + size, y - size * 2 };
		Polygon(gr::dc, a, 4);
	}
	// отрисовка крыши
	void VisRoof() {
		gr::InitGraphics(hWnd);
		gr::Set_pen(RGB(0, 0, 0), 4);
		gr::Set_brush(roof, true);
		POINT a[3] = { x, y - size * 2 - size / 1.2, x - size - 10, y - size * 2, x + size + 10, y - size * 2 };
		Polygon(gr::dc, a, 3);
	}
	// отрисовка окна
	void VisWindow(bool fl) {
		gr::InitGraphics(hWnd);
		gr::Set_pen(RGB(0, 0, 0), 4);
		// елсли флан, то отрисовка выключенного света, иначе включенный свет
		if (fl == false) {
			gr::InitGraphics(hWnd);
			gr::Set_pen(RGB(0, 0, 0), 4);
			gr::Set_brush(windows_off, true);
			POINT a[4] = { x - size + size / 3, y - size * 2 + size / 3, x - size + size / 3, y - size / 3, x + size - size / 3,  y - size / 3, x + size - size / 3,   y - size * 2 + size / 3 };
			Polygon(gr::dc, a, 4);
			gr::Set_pen(RGB(0, 0, 0), 4);
			gr::Set_brush(windows_off, false);
			gr::Line(x - size + size / 3, y - size, x + size - size / 3, y - size);
			gr::Line(x, y - size * 2 + size / 3, x, y - size / 3);
		}
		else {
			gr::InitGraphics(hWnd);
			gr::Set_pen(RGB(0, 0, 0), 4);
			gr::Set_brush(windows_on, true);
			POINT a[4] = { x - size + size / 3, y - size * 2 + size / 3, x - size + size / 3, y - size / 3, x + size - size / 3,  y - size / 3, x + size - size / 3,   y - size * 2 + size / 3 };
			Polygon(gr::dc, a, 4);
			gr::Set_pen(RGB(0, 0, 0), 4);
			gr::Set_brush(windows_on, false);
			gr::Line(x - size + size / 3, y - size, x + size - size / 3, y - size);
			gr::Line(x, y - size * 2 + size / 3, x, y - size / 3);
		}
	}
	// "сборка дома"
	void VisHouse(bool fl) {
		VisMain();
		VisRoof();
		VisWindow(fl);
	}
};

class Man {
	/* у человека четыре состояния: стоит, идёт, смотрит, бежит */
private:
	int x, y; // координаты центра головы
	int long_man, r_head;
public:
	Man(int x_, int y_, int long_man_, int r_head_) : x(x_), y(y_), long_man(long_man_), r_head(r_head_) {}
	void VisManStand() {
		gr::InitGraphics(hWnd);
		gr::Set_pen(RGB(0, 0, 0), 3);
		gr::Set_brush(RGB(0, 0, 0), false);
		Ellipse(gr::dc, x - r_head, y - r_head, x + r_head, y + r_head); // голова
		gr::Line(x, y + r_head, x, y + r_head + long_man); // тело
		gr::Line(x, y + r_head + long_man, x - long_man / 4, y + r_head + long_man + long_man * 0.60); // левая нога
		gr::Line(x, y + r_head + long_man, x + long_man / 4, y + r_head + long_man + long_man * 0.60); // правая нога
		gr::Line(x, y + r_head + long_man / 4, x - long_man / 3, y + r_head + long_man / 1.5); // левая рука
		gr::Line(x, y + r_head + long_man / 4, x + long_man / 3, y + r_head + long_man / 1.5);  // праовая рука
	}
	void VisManGo() {
		gr::InitGraphics(hWnd);
		gr::Set_pen(RGB(0, 0, 0), 3);
		gr::Set_brush(RGB(0, 0, 0), false);
		Ellipse(gr::dc, x - r_head, y - r_head, x + r_head, y + r_head); // голова
		gr::Line(x, y + r_head, x, y + r_head + long_man); // тело
		gr::Line(x, y + r_head + long_man, x - long_man / 3, y + r_head + long_man + long_man / 5); // левая нога
		gr::Line(x - long_man / 3, y + r_head + long_man + long_man / 5, x - long_man / 4, y + r_head + long_man + long_man / 2); // левая нога
		gr::Line(x, y + r_head + long_man, x + long_man / 4, y + r_head + long_man + long_man * 0.60); // правая нога
		gr::Line(x, y + r_head + long_man / 4, x - long_man / 3, y + r_head + long_man / 1.5); // левая рука
		gr::Line(x, y + r_head + long_man / 4, x + long_man / 3, y + r_head + long_man / 1.5);  // правая рука
	}
	void VisManBack() {
		gr::InitGraphics(hWnd);
		gr::Set_pen(RGB(0, 0, 0), 3);
		gr::Set_brush(RGB(0, 0, 0), false);
		Ellipse(gr::dc, x - r_head, y - r_head, x + r_head, y + r_head); // голова
		gr::Line(x, y + r_head, x, y + r_head + long_man); // тело
		gr::Line(x, y + r_head + long_man, x - long_man / 3, y + r_head + long_man + long_man / 5); // левая рука
		gr::Line(x - long_man / 3, y + r_head + long_man + long_man / 5, x - long_man / 3, y + long_man + r_head); // левая рука
		gr::Line(x, y + r_head + long_man, x + long_man / 4, y + r_head + long_man + long_man * 0.60); // правая рука
		gr::Line(x, y + r_head + long_man / 4, x - long_man / 3, y + r_head + long_man / 1.5); // левая нога
		gr::Line(x, y + r_head + long_man / 4, x + long_man / 3, y + r_head + long_man / 1.5);  // правая нога
	}
	void VisManWatch() {
		gr::InitGraphics(hWnd);
		gr::Set_pen(RGB(0, 0, 0), 3);
		gr::Set_brush(RGB(0, 0, 0), false);
		Ellipse(gr::dc, x - r_head, y - r_head, x + r_head, y + r_head); // голова
		gr::Line(x, y + r_head, x, y + r_head + long_man); // тело
		gr::Line(x, y + r_head + long_man, x - long_man / 4, y + r_head + long_man + long_man * 0.60); // првая рука
		gr::Line(x, y + r_head + long_man, x + long_man / 4, y + r_head + long_man + long_man * 0.60); // левая рука
		gr::Line(x, y + r_head + long_man / 4, x - long_man / 3, y + r_head); // левая нога
		gr::Line(x - long_man / 3, y + r_head, x, y); // левая нога
		gr::Line(x, y + r_head + long_man / 4, x + long_man / 3, y + r_head + long_man / 1.5);  // првая рука
	}
	void MoveMan(int x_, int y_) { x = x_; y = y_; }
};
