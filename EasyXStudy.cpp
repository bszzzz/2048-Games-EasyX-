#include <bits/stdc++.h>
#include <easyx.h>
#include <conio.h>
#define colorone RGB(66,133,244)
#define colortwo RGB(234,67,53)
#define colorthree RGB(251,188,5)
#define colorfour RGB(52,168,83)
#define colorfive RGB(232,80,155)
#define colorsix RGB(39,162,139)
#define colorseven RGB(246,124,95)
#define coloreight RGB(43,91,173)
#define colornine RGB(237,200,80)
#define colorten RGB(183,148,115)
#define coloreleven RGB(151,111,67)
#define colortwelve RGB(60,58,50)
#define colorframe RGB(187,173,160)
#define colorplaid RGB(205,193,180)

using namespace std;

int a[10][10], s;
const int AK = 75, SK = 80, DK = 77, WK = 72;
LPCTSTR number_to_string(int num) {
	switch (num) {
	case 0:return L"0";
	case 2:return L"2";
	case 4:return L"4";
	case 8:return L"8";
	case 16:return L"16";
	case 32:return L"32";
	case 64:return L"64";
	case 128:return L"128";
	case 256:return L"256";
	case 512:return L"512";
	case 1024:return L"1024";
	case 2048:return L"2048";
	case 4096:return L"4096";
	default: return 0;
	}
}
COLORREF GetNumberColor(int num) {
	switch (num) {
		case 0:return colorplaid;
		case 2:return colorone;
		case 4:return colortwo;
		case 8:return colorthree;
		case 16:return colorfour;
		case 32:return colorfive;
		case 64:return colorsix;
		case 128:return colorseven;
		case 256:return coloreight;
		case 512:return colornine;
		case 1024:return colorten;
		case 2048:return coloreleven;
		case 4096:return colortwelve;
		default: return colorplaid;
	}
}
int startx(int num) {
	if (num <= 9)return 107;
	if (num <= 99)return 90;
	if (num <= 999)return 80;
	return 60;
}
void startprogram() {
	initgraph(880, 880);
	setbkmode(TRANSPARENT);
	settextstyle(70, 0, L"Cascadia Code");
	HWND hnd = GetHWnd();
	SetWindowText(hnd, L"2048 Games");
}
void paint_rectangle(COLORREF clr, int x, int y)
{
	setfillcolor(clr);
	solidroundrect(x, y, x + 188, y + 188, 10, 10);
}
void paint_nrectangle(COLORREF clr, int xx, int xy, int yx, int yy)
{
	setfillcolor(clr);
	solidrectangle(xx, xy, yx, yy);
}
void print_line(int ln, int stx, int sty) {
	paint_rectangle(GetNumberColor(a[ln][1]), stx, sty);
	if (a[ln][1])
		outtextxy(startx(a[ln][1]), ln * 203 - 113, number_to_string(a[ln][1]));
	paint_rectangle(GetNumberColor(a[ln][2]), stx + 203, sty);
	if (a[ln][2])
		outtextxy(startx(a[ln][2]) + 203, ln * 203 - 113, number_to_string(a[ln][2]));
	paint_rectangle(GetNumberColor(a[ln][3]), stx + 406, sty);
	if (a[ln][3])
		outtextxy(startx(a[ln][3]) + 406, ln * 203 - 113, number_to_string(a[ln][3]));
	paint_rectangle(GetNumberColor(a[ln][4]), stx + 609, sty);
	if (a[ln][4])
		outtextxy(startx(a[ln][4]) + 609, ln * 203 - 113, number_to_string(a[ln][4]));
}
void draw_mainwindow() {
	paint_nrectangle(colorframe, 15, 15, 842, 842);
	print_line(1, 30, 30);
	print_line(2, 30, 233);
	print_line(3, 30, 436);
	print_line(4, 30, 639);
	system("cls");
	cout << "Stars:" << s << endl;
}
void newnum() {
	int x, y;
	do {
		x = rand() & 3, y = rand() & 3;
		x++; y++;
	} while (a[x][y]);
	a[x][y] = rand() & 1 ? 4 : 2;
	draw_mainwindow();
}
inline bool InRange(int x, int y) {
	return x > 0 && x <= 4 && y > 0 && y <= 4;
}
void moveleft() {
	for (int i = 1; i <= 4; ++i)
		for (int j = 4; j > 1; --j) {
			int x = i, y = j, ii = y;
			while (InRange(x, y - 1)) {
				if (a[x][y - 1] == 0)swap(a[x][y - 1], a[x][y]), ii--;
				y--;
			}
			y = ii;
			if (y > 1 && a[x][y - 1] == a[x][y]) {
				a[x][y - 1] += a[x][y];
				a[x][y] = 0;
				s += a[x][y - 1];
			}
		}
}
void movedown() {
	for (int i = 1; i < 4; ++i)
		for (int j = 1; j <= 4; ++j) {
			int x = i, y = j, ii = i;
			while (InRange(x + 1, y)) {
				if (a[x + 1][y] == 0)swap(a[x + 1][y], a[x][y]), ii++;
				x++;
			}
			x = ii;
			if (x <= 4 && a[x + 1][y] == a[x][y]) {
				a[x + 1][y] += a[x][y];
				a[x][y] = 0;
				s += a[x + 1][y];
			}
		}
}
void moveright() {
	for (int i = 1; i <= 4; ++i)
		for (int j = 1; j < 4; ++j) {
			int x = i, y = j, ii = j;
			while (InRange(x, y + 1)) {
				if (a[x][y + 1] == 0)swap(a[x][y + 1], a[x][y]), ii++;
				y++;
			}
			y = ii;
			if (y <= 4 && a[x][y + 1] == a[x][y]) {
				a[x][y + 1] += a[x][y];
				a[x][y] = 0;
				s += a[x][y + 1];
			}
		}
}
void moveup() {
	for (int i = 4; i > 1; --i)
		for (int j = 1; j <= 4; ++j) {
			int x = i, y = j, ii = i;
			while (InRange(x - 1, y)) {
				if (a[x - 1][y] == 0)swap(a[x - 1][y], a[x][y]), ii--;
				x--;
			}
			x = ii;
			if (x > 0 && a[x - 1][y] == a[x][y]) {
				a[x - 1][y] += a[x][y];
				a[x][y] = 0;
				s += a[x - 1][y];
			}
		}
}
bool chk() {
	for (int i = 1; i <= 4; ++i)
		for (int j = 1; j <= 4; ++j)
			if (a[i - 1][j] == a[i][j] || a[i + 1][j] == a[i][j] || a[i][j - 1] == a[i][j] || a[i][j + 1] == a[i][j] || a[i][j] == 0)
				return 1;
	MessageBox(0, L"Game Over!", L"overed", MB_OK);
	closegraph();
	return 0;
}
void Game() {
	while (chk()) {
		int cc = _getch();
		char opt;
		if (cc == 224)opt = _getch();
		else opt = cc;
		if (opt != 27 && opt != 'a' && opt != 's' && opt != 'd' && opt != 'w' && opt != 'A' && opt != 'W' && opt != 'S' && opt != 'D' && opt != 'q' && opt != 'Q' && opt != 72 && opt != 75 && opt != 77 && opt != 80)continue;
		if(opt == 'q' || opt == 'Q' || opt == 27) {
			MessageBox(0, L"Game Over!", L"overed", MB_OK);
			closegraph();
		}
		if (opt == 'a' || opt == 'A' || opt == AK) {
			moveleft();
			moveleft();
		}
		else if (opt == 's' || opt == 'S' || opt == SK) {
			movedown();
			movedown();
		}
		else if (opt == 'd' || opt == 'D' || opt == DK) {
			moveright();
			moveright();
		}
		else if (opt == 'w' || opt == 'W' || opt == WK) {
			moveup();
			moveup();
		}
		newnum();
	}
}
int main() {
	srand(time(0));
	startprogram();
	newnum();
	newnum();
	Game();
	closegraph();
	return 0;
}