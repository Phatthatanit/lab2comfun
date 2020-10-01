#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
char ch = '.';
int go = 0, x = 38, y = 20, bullets[5] = { 0 }, a[5], b[5] = { 20,20,20,20,20 }, point = -1;

void gotoxy(int x, int y)
{

	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void draw_bullets(int x, int y)
{
	gotoxy(x += 2, --y); 
	setcolor(2, 4); 
	printf(" ");
}
void erase_bullets(int x, int y)
{
	gotoxy(x += 2, --y); 
	setcolor(0, 0); 
	printf(" ");
}

void erase_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(2, 0);
	printf("       ");
}

void draw_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 4);
	printf("<-0->");
}


void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

int main()
{


	setcursor(0);
	draw_ship(x, y);

	do {
		for (int i = 0; i <= 5; i++)
		{
			if (bullets[i] == 0)
			{
				a[i] = x;
			}
		}
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a'|| ch == 'A') {
				go = 1; 
			}
			if (ch == 's' || ch == 'S') {
				go = 0; 
			}
			if (ch == 'd' || ch == 'D') {
				go = 2; 
			}
			if (ch == ' ' && point < 4) {
				++point; 
				bullets[point] = 1; 
			}
		}
		if (go == 1 && x > 0) {
			erase_ship(x, y);
			draw_ship(--x, y); 
		}
		if (go == 2 && x < 75) {
			erase_ship(x, y); 
			draw_ship(++x, y);
		}
		for (int j = 0; j <= 4; j++)
		{
			if (bullets[j] == 1 && b[j] > 0)
			{
				erase_bullets(a[j], b[j]);
				draw_bullets(a[j], --b[j]);
			}
		}
		if (b[0] == 1) {
			erase_bullets(a[0], b[0]);
			bullets[0] = 0;
			b[0] = y;
			--point;
			for (int k = 1; k <= 4; k++)
			{
				bullets[k - 1] = bullets[k]; b[k - 1] = b[k]; a[k - 1] = a[k];
			}
			bullets[4] = 0; b[4] = y; a[4] = x;
		}
	fflush(stdin);
	Sleep(100);
     } while (ch != 'x');
	return 0;
}