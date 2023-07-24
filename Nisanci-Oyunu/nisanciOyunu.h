/*
Niþancý (Shooter) Türünde Basit Bir Oyun
*/

#ifndef NISANCIOYUNU_H
#define NISANCIOYUNU_H
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "../lib/imlec.h" // https://github.com/seymenkonuk/Imlec-Kontrol-C commit 1
#include "../lib/rastgele.h" // https://github.com/seymenkonuk/Rastgele-C commit 1

int oynaNisanciOyunu(int genislik, int yukseklik);

int oynaNisanciOyunu(int genislik, int yukseklik) {
    int yonler[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    system("cls"); int i, j;
    for (i=0; i<genislik+2; i++) printf("%c ", 254);
    for (i=0; i<yukseklik+1; i++) printf("\n%c", 254);
    for (i=0; i<genislik+1; i++) printf(" %c", 254);
    for (i=1; i<yukseklik+1; i++) { gotoxy((genislik+1)*2, i); printf("%c", 254);}
    printf("\n\n");
    int konum_i = yukseklik-1, konum_j = genislik/2+genislik%2;
    int hiz = 60; int dusmanGelmeSuresi = yukseklik; 
    gotoxy(konum_j*2, konum_i); printf("%c", 254);
    int dusmanlar[2*genislik][2]; int dusmanSayisi = 0; int dusmanHiz = 3; // Ters Orantýlý
    int sayacSure = dusmanGelmeSuresi; int sayacHiz = 0; int sayacBoss = 0; int puan = 0;
    int tahta[yukseklik+2][genislik+2]; 
    for (i=0; i<yukseklik+2; i++) for (j=0; j<genislik+2; j++) tahta[i][j] = 0; 
    while (1) {
        gotoxy(0, yukseklik+2);
        printf("Puan: %d", puan);
        sayacHiz = (sayacHiz % dusmanHiz) + 1;
        if (sayacHiz >= dusmanHiz) {
            puan++;
            // Yeni Düþman
            if (sayacSure >= dusmanGelmeSuresi) {
                if (dusmanSayisi < 2*genislik) {
                    dusmanlar[dusmanSayisi][0] = 1;
                    dusmanlar[dusmanSayisi][1] = rastgeleAralik(1, genislik);
                    gotoxy(dusmanlar[dusmanSayisi][1]*2, dusmanlar[dusmanSayisi][0]); printf("O");
                    tahta[dusmanlar[dusmanSayisi][0]][dusmanlar[dusmanSayisi][1]] = 1;
                    if (konum_i == dusmanlar[i][0] && konum_j == dusmanlar[i][1]) {
                        // printf("\nKaybettin!");
                        return puan;
                    }
                    dusmanSayisi++;
                    sayacSure = 1;
                }
            } else sayacSure++;
            // Varolan Düþmanlarýn Düþmesi
            for (i=0; i<dusmanSayisi; i++) {
                if (dusmanlar[i][0] < yukseklik) {
                    if (konum_i == dusmanlar[i][0]+1 && konum_j == dusmanlar[i][1]) {
                        // printf("\nKaybettin!");
                        return puan;
                    }
                    tahta[dusmanlar[i][0]][dusmanlar[i][1]] = 0;
                    gotoxy(dusmanlar[i][1]*2, dusmanlar[i][0]); printf(" ");
                    dusmanlar[i][0]++;
                    tahta[dusmanlar[i][0]][dusmanlar[i][1]] = 1;
                    gotoxy(dusmanlar[i][1]*2, dusmanlar[i][0]); printf("O");
                } else {
                    tahta[dusmanlar[i][0]][dusmanlar[i][1]] = 0;
                    gotoxy(dusmanlar[i][1]*2, dusmanlar[i][0]); printf(" ");
                    for (j=i+1; j<dusmanSayisi; j++) {
                        dusmanlar[j-1][0] = dusmanlar[j][0];
                        dusmanlar[j-1][1] = dusmanlar[j][1];
                    }
                    i--;
                    dusmanSayisi--;
                    if (dusmanGelmeSuresi > 2) dusmanGelmeSuresi--;
                    else if (sayacBoss == 10) { dusmanHiz = 2; sayacBoss = 11;}
                    else if (sayacBoss == 100) dusmanHiz = 1;
                    else sayacBoss++;
                }
            }
        }
        // Karakterin Kontrolü
        if (kbhit()) {
            char tus = getch();
            int yon = -1;
            if (tus == 'd' || tus == 'D')
                yon = 0;
            else if (tus == 's' || tus == 'S')
                yon = 1;
            else if (tus == 'a' || tus == 'A')
                yon = 2;
            else if (tus == 'w' || tus == 'W')
                yon = 3;
            
            if (yon != -1) {
                int yeni_i = konum_i + yonler[yon][0];
                int yeni_j = konum_j + yonler[yon][1];
                
                if (yeni_i >= 1 && yeni_i <= yukseklik)
                    if (yeni_j >= 1 && yeni_j <= genislik) {
                        if (tahta[yeni_i][yeni_j] == 1) {
                            // printf("\nKaybettin!");
                            return puan;
                        }
                        gotoxy(konum_j*2, konum_i); printf(" ");
                        konum_i = yeni_i; konum_j = yeni_j;
                        gotoxy(konum_j*2, konum_i); printf("%c", 254);
                    }
            }
        }
        gotoxy(0, yukseklik+2);
        sleep(1000/hiz);
    }
}
#endif
