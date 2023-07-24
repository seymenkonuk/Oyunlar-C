/*
Yýlan Oyunu
*/
#ifndef YILANOYUNU_H
#define YILANOYUNU_H
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "../lib/imlec.h" // https://github.com/seymenkonuk/Imlec-Kontrol-C commit 1
#include "../lib/rastgele.h" // https://github.com/seymenkonuk/Rastgele-C commit 1

int oynaYilanOyunu(int genislik, int yukseklik, int elmaSayisi);

int oynaYilanOyunu(int genislik, int yukseklik, int elmaSayisi) {
    int yonler[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    system("cls"); int i, j;
    for (i=0; i<genislik+2; i++) printf("%c ", 254);
    for (i=0; i<yukseklik+1; i++) printf("\n%c", 254);
    for (i=0; i<genislik+1; i++) printf(" %c", 254);
    for (i=1; i<yukseklik+1; i++) { gotoxy((genislik+1)*2, i); printf("%c", 254);}
    
    int yilan[yukseklik*genislik][2], yilanuzunluk = 1;
    int tahta[yukseklik][genislik]; for (i=0; i<yukseklik; i++) for (j=0; j<genislik; j++) tahta[i][j] = 0;
    int hiz = genislik, yon = 0; if (yukseklik < hiz) hiz = yukseklik;
    yilan[0][0] = genislik/2+genislik%2; yilan[0][1] = yukseklik/2+yukseklik%2;
    gotoxy(yilan[0][0]*2, yilan[0][1]); printf("%c", 254);
    gotoxy(0, yukseklik+2);
    tahta[yilan[0][1]-1][yilan[0][0]-1] = 1;
    
    for (i=1; i<=elmaSayisi; i++) {
        if (yilanuzunluk+i>yukseklik*genislik) break;
        int elma_x, elma_y;
        do {
            elma_x = rastgeleAralik(0, genislik-1);
            elma_y = rastgeleAralik(0, yukseklik-1);
        } while (tahta[elma_y][elma_x] != 0);
        tahta[elma_y][elma_x] = 2;
        gotoxy((elma_x+1)*2, elma_y+1); printf("O");
    }
    
    while (1) {
        // Hareket Etme
        if (kbhit()) {
            char tus = getch();
            int yeni_yon = yon;
            if (tus == 'd' || tus == 'D')
                yeni_yon = 0;
            else if (tus == 's' || tus == 'S')
                yeni_yon = 1;
            else if (tus == 'a' || tus == 'A')
                yeni_yon = 2;
            else if (tus == 'w' || tus == 'W')
                yeni_yon = 3;
            if (yon % 2 != yeni_yon % 2) yon = yeni_yon;
        }
        
        // Duvara Çarpma Kontrol
        int yeni_x = yilan[0][0] + yonler[yon][0];
        int yeni_y = yilan[0][1] + yonler[yon][1];
        if (yeni_x < 1 || yeni_x > genislik) break;
        if (yeni_y < 1 || yeni_y > yukseklik) break;
        
        // Yýlaný Kaydýr
        if (tahta[yeni_y-1][yeni_x-1] == 1) break; // Kendine Çarptý
        if (tahta[yeni_y-1][yeni_x-1] == 2) {
            yilanuzunluk++; /*if (yilanuzunluk % 10 == 0) hiz++;*/
            if (yilanuzunluk+elmaSayisi<=yukseklik*genislik) {
                int elma_x, elma_y;
                do {
                    elma_x = rastgeleAralik(0, genislik-1);
                    elma_y = rastgeleAralik(0, yukseklik-1);
                } while (tahta[elma_y][elma_x] != 0);
                tahta[elma_y][elma_x] = 2;
                gotoxy((elma_x+1)*2, elma_y+1); printf("O");
            } else elmaSayisi--;
        } else {
            gotoxy(yilan[yilanuzunluk-1][0]*2, yilan[yilanuzunluk-1][1]); printf(" ");
            tahta[yilan[yilanuzunluk-1][1]-1][yilan[yilanuzunluk-1][0]-1] = 0;
        }
        for (i=yilanuzunluk-1; i>0; i--) {
            yilan[i][0] = yilan[i-1][0];
            yilan[i][1] = yilan[i-1][1];
        }
        yilan[0][0] = yeni_x;
        yilan[0][1] = yeni_y;
        tahta[yilan[0][1]-1][yilan[0][0]-1] = 1;
        gotoxy(yilan[0][0]*2, yilan[0][1]); printf("%c", 254);
        if (yilanuzunluk == yukseklik*genislik) break;
        gotoxy(0, yukseklik+2);
        sleep(1000/hiz);
    }
    gotoxy(0, yukseklik+2);
    if (yilanuzunluk == yukseklik*genislik) 
        printf("Kazandin!");
    else 
        printf("Kaybettin!");
    return yilanuzunluk;
}
#endif
