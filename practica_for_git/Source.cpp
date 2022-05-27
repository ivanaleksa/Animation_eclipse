#include "Classes.h"

void AnimPicture();

int main() {
	srand((unsigned)time(NULL));
	setlocale(LC_CTYPE, "rus");
	hWnd = GetConsoleWindow();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO sci;
	GetConsoleCursorInfo(handle, &sci);
	sci.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &sci);
	Sleep(15);

	// запуск отрисоки объектов и анимаций
	AnimPicture();

	cin.get();
	return 0;
}


void AnimPicture() {
	// отрисовка статических объектов

	Grass my_grass(RGB(15, 224, 0), RGB(14, 159, 4));

	Tree tree_1(RGB(77, 33, 0), RGB(0, 82, 4), 100, 530), tree_2(RGB(107, 71, 0), RGB(11, 69, 0), 470, 640),
		tree_3(RGB(115, 103, 0), RGB(67, 138, 0), 10, 630), tree_4(RGB(150, 103, 8), RGB(45, 150, 8), 340, 570);

	int x_moon = 350, x_1 = 500; // начальные координаты луны и облака
	int man_x = 1200; // начальные координаты человека
	int r = 0, g = 255, b = 221; // начальный цвет неба
	bool fl_for_man = false;

	// инициализация объектов
	Sky my_sky(RGB(r, g, b));
	Sun my_sun(RGB(255, 191, 0), 153, 650, 200);
	Moon my_moon(RGB(r, g, b), 150, x_moon, 200);
	Man man(man_x, 450, 40, 10);
	House my_house1(RGB(122, 62, 0), RGB(77, 39, 0), RGB(0, 151, 214), RGB(235, 213, 0), 920, 600, 70),
		my_house2(RGB(122, 62, 0), RGB(77, 39, 0), RGB(0, 151, 214), RGB(235, 213, 0), 1200, 550, 70);

	// отрисовка объектов
	man.VisManStand();
	my_house1.VisHouse(false);
	my_house2.VisHouse(false);
	my_sky.VisSky(RGB(r, g, b));
	my_sun.VisSun();
	my_moon.VisMoon(x_moon, RGB(r, g, b));
	Cloud cloud_1(x_1, 100);
	cin.get();

	// цикл для анимаций
	while (!_kbhit()) {
		// изменение координат луны и облака 
		x_moon += 2;
		x_1 -= 1;

		my_sky.VisSky(RGB(r, g, b)); // очередная отрисовка неба

		my_sun.VisSun();
		my_moon.VisMoon(x_moon, RGB(r, g, b)); // отрисовка обновлённой луны
		Cloud cloud_1(x_1, 100); // отрисовка обновленного облака

		// условие на изменение цвета неба в зависимости от положения луны
		if (500 <= x_moon && x_moon <= 790) {
			if (x_moon >= 650) {
				g += 3;
				b += 2;
			}
			else {
				g -= 3;
				b -= 2;
			}
		}

		// условие на изменение цвета окон у домов
		if (x_moon == 570) {
			my_house1.VisWindow(true);
			my_house2.VisWindow(true);

		}
		else if (x_moon == 730) {
			my_house1.VisWindow(false);
			my_house2.VisWindow(false);

		}

		// условие на изменение состояния человека
		if (x_moon >= 570 && x_moon <= 630 && x_moon % 2 == 0) { // идёт смотреть на затмение
			man_x -= 5;
			man.MoveMan(man_x, 450);
			gr::InitGraphics(hWnd);
			gr::Set_brush(RGB(14, 159, 4), true);
			gr::Set_pen(RGB(14, 159, 4), 1);
			POINT a[4] = { man_x - 20, 450 - 10, man_x - 20, 450 + 80, man_x + 20, 450 + 80, man_x + 20, 450 - 10 };
			Polygon(gr::dc, a, 4);
			if (!fl_for_man) {
				man.VisManStand();
				fl_for_man = true;
			}
			else {
				man.VisManGo();
				fl_for_man = false;
			}
			my_house1.VisHouse(true);
			my_house2.VisHouse(true);
		}
		else if (x_moon == 632) { // смотрит на затмение
			gr::InitGraphics(hWnd);
			gr::Set_brush(RGB(14, 159, 4), true);
			gr::Set_pen(RGB(14, 159, 4), 1);
			POINT a[4] = { man_x - 20, 450 - 10, man_x - 20, 450 + 80, man_x + 20, 450 + 80, man_x + 20, 450 - 10 };
			Polygon(gr::dc, a, 4);
			man.VisManWatch();
		}
		else if (x_moon > 690 && x_moon < 740) { // идёт обратно
			man_x += 5;
			man.MoveMan(man_x, 450);
			gr::InitGraphics(hWnd);
			gr::Set_brush(RGB(14, 159, 4), true);
			gr::Set_pen(RGB(14, 159, 4), 1);
			POINT a[4] = { man_x - 20, 450 - 10, man_x - 20, 450 + 80, man_x + 20, 450 + 80, man_x + 20, 450 - 10 };
			Polygon(gr::dc, a, 4);
			if (!fl_for_man) {
				man.VisManStand();
				fl_for_man = true;
			}
			else {
				man.VisManBack();
				fl_for_man = false;
			}
			my_house1.VisHouse(false);
			my_house2.VisHouse(false);
		}

		if (x_moon > 955) break; // луна полностью прошла через солнца, остановка анимаций
		Sleep(30);
	}
}