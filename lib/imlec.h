/*
Ýmlecin Konumunu Deðiþtirir
*/

#ifndef IMLEC_H
#define IMLEC_H
#include <windows.h>

void gotoxy(int x, int y); // imleci (x, y) koordinatýna götürür.

void gotoxy(int x, int y) {
     COORD coord;
     coord.X = x;
     coord.Y = y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#endif
