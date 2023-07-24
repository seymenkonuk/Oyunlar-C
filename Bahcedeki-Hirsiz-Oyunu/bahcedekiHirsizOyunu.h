/*
Yýllar Öncesinde Tipeez.com Adlý Bir Web Sitede Yer Alan Bahçedeki Hýrsýz Benzeri Bir Oyun
*/
#ifndef BAHCEDEKIHIRSIZOYUNU_H
#define BAHCEDEKIHIRSIZOYUNU_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "../lib/imlec.h" // https://github.com/seymenkonuk/Imlec-Kontrol-C commit 1
#include "../lib/rastgele.h" // https://github.com/seymenkonuk/Rastgele-C commit 1

bool oynaBahcedekiHirsizOyunu(int genislik, int yukseklik, int uzayliSayisi);

bool oynaBahcedekiHirsizOyunu(int genislik, int yukseklik, int uzayliSayisi) {
    int yonler[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    int tahta[yukseklik+2][genislik+2];
    int boyaliAlan = 0, kazanmaAlani = genislik*yukseklik/2;
    // Oyuncunun Arkasýndaki Çizgi / Oyuncunun Rotasý
    int cizgi[yukseklik*genislik][2]; int cizgiuzunluk = 0;
    // Uzaylýlarýn Konumlarý
    if (genislik*yukseklik - kazanmaAlani < uzayliSayisi) uzayliSayisi = genislik*yukseklik - kazanmaAlani;
    int uzayliKonum[uzayliSayisi][2]; int uzayliHiz = 2; // ters orantýlý
    int uzayliEskiYon[uzayliSayisi];
    // Oyuncunun Konumu
    int konum_i = 0, konum_j = 1, hiz = 60;
    int bosluk = -1, uzayliYurume = -2;
    
    void hucreYaz(int i, int j) {
        gotoxy(j*2, i);
        if (konum_i == i && konum_j == j)
            printf("+");
        else if (tahta[i][j] == bosluk)
            printf(" ");
        else if (tahta[i][j] == 2)
            printf("%c", 254);
        else if (tahta[i][j] == 1)
            printf("-");
        else if (tahta[i][j] == 0)
            printf("O");
        gotoxy(0, yukseklik+2);
    }
    
    void yay(int i, int j, int boya, bool deger, bool goster) {
        if (deger) tahta[i][j] = boya;
        if (goster) hucreYaz(i, j);
        if (boya == 2) boyaliAlan++;
        int k;
        for (k=0; k<4; k++) {
            int yeni_i = i + yonler[k][0];
            int yeni_j = j + yonler[k][1];
            
            if (yeni_i >= 0 && yeni_i < yukseklik+2)
                if (yeni_j >= 0 && yeni_j < genislik+2)
                    if (tahta[yeni_i][yeni_j] == bosluk)
                        yay(yeni_i, yeni_j, boya, true, goster);
        }
    }
    
    void cizgiyiYay() {
        int i, j;
        // Uzaylý Yürümeyi Yay
        for (i=0; i<uzayliSayisi; i++) yay(uzayliKonum[i][0], uzayliKonum[i][1], uzayliYurume, false, false);
        // Boþluk Kalanlarý Duvar Yap
        for (i=1; i<=yukseklik; i++) {
            for (j=1; j<=genislik; j++) {
                if (tahta[i][j] == bosluk)
                    yay(i, j, 2, true, true);
            }
        }
        // Boþluk ve Uzaylý Yürümeyi Deðiþtir
        int depo = uzayliYurume;
        uzayliYurume = bosluk;
        bosluk = depo;
    }
    int i, j;
    system("cls");
    // Tahtayý Oluþturma Ýþlemi
    for (i=0; i<yukseklik+2; i++) 
        for (j=0; j<genislik+2; j++)
            if (i==0 || i==yukseklik+1 || j==0 || j==genislik+1) {
                tahta[i][j] = 2;
                hucreYaz(i, j);
            } else {
                tahta[i][j] = bosluk;
            }
    // Uzaylýlarý Oluþturma Ýþlemi
    for (i=0; i<uzayliSayisi; i++) {
        int r_i, r_j;
        do {
            r_i = rastgeleAralik(1, yukseklik);
            r_j = rastgeleAralik(1, genislik);
        } while (tahta[r_i][r_j] != bosluk);
        uzayliKonum[i][0] = r_i; uzayliKonum[i][1] = r_j;
        uzayliEskiYon[i] = 4;
        tahta[r_i][r_j] = 0;
        hucreYaz(r_i, r_j);
    }
    // Oyuncuyu Konumlandýr
    hucreYaz(konum_i, konum_j);
    
    int sayac = 0;
    // Oyun Mekanikleri
    while (1) {
        sayac = (sayac%uzayliHiz) + 1;
        // Oyuncu Hareket
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
                if (yeni_i >= 0 && yeni_i < yukseklik+2)
                    if (yeni_j >= 0 && yeni_j < genislik+2) {
                        int eski_i = konum_i, eski_j = konum_j;
                        konum_i = yeni_i;
                        konum_j = yeni_j;
                        
                        if (tahta[eski_i][eski_j] != 2 && tahta[konum_i][konum_j] == 2) { // Eðer Ulaþtýysa Çizgiyi Kopar
                            boyaliAlan += cizgiuzunluk+1;
                            for (i=0; i<cizgiuzunluk; i++) {
                                tahta[cizgi[i][0]][cizgi[i][1]] = 2;
                                hucreYaz(cizgi[i][0], cizgi[i][1]);
                            }
                            tahta[eski_i][eski_j] = 2;
                            hucreYaz(eski_i, eski_j);
                            cizgiuzunluk = 0;
                            cizgiyiYay();
                        } else if (tahta[konum_i][konum_j] == 1) {
                            printf("Kaybettin!\n");
                            return false;
                        } else if (tahta[konum_i][konum_j] == 0) {
                            printf("Kaybettin!\n");
                            return false;
                        } else if (tahta[eski_i][eski_j] == bosluk) { // Karakter Boþluktaysa Arkasýndan Çizgi Uzasýn
                            tahta[eski_i][eski_j] = 1;
                            cizgi[cizgiuzunluk][0] = eski_i;
                            cizgi[cizgiuzunluk][1] = eski_j;
                            cizgiuzunluk++;
                        }
                        
                        hucreYaz(konum_i, konum_j);
                        hucreYaz(eski_i, eski_j);
                        
                        if (boyaliAlan >= kazanmaAlani) {
                            // printf("Kazandin!\n");
                            // return oynaBahcedekiHirsizOyunu(genislik+1, yukseklik+1, 1);
                            return true;
                        }
                    }
            }
        }
        // Uzaylý Hareketleri
        if (sayac == uzayliHiz) {
            bool kaybettinMi = false;
            for (i=0; i<uzayliSayisi; i++) {
                // if (uzayliKonum[i][0] == -1) continue; // Ölmüþ Uzaylý-
                int yeni_i, yeni_j, yon;
                do {
                    yeni_i = uzayliKonum[i][0]; yeni_j = uzayliKonum[i][1];
                    yon = rastgeleAralik(0, 4);
                    if (yon == uzayliEskiYon[i] && rastgeleAralik(1, 100) > 30) continue;
                    if (yon == 4) break;
                    yeni_i = uzayliKonum[i][0] + yonler[yon][0];
                    yeni_j = uzayliKonum[i][1] + yonler[yon][1];
                    if (yeni_i < 0 || yeni_i >= yukseklik+2) continue;
                    if (yeni_j < 0 || yeni_j >= genislik+2) continue;
                } while (tahta[yeni_i][yeni_j] == 2 || tahta[yeni_i][yeni_j] == 0);
                
                if (yon == 4) { uzayliEskiYon[i] = 4; continue;}
                else if (yon >= 2) { uzayliEskiYon[i] = yon - 2; }
                else { uzayliEskiYon[i] = yon + 2; }
                
                if (tahta[yeni_i][yeni_j] == 1 || (yeni_i == konum_i && yeni_j == konum_j)) { 
                    printf("Kaybettin!\n");
                    return false;
                }
                
                tahta[uzayliKonum[i][0]][uzayliKonum[i][1]] = bosluk;
                hucreYaz(uzayliKonum[i][0], uzayliKonum[i][1]);
                uzayliKonum[i][0] = yeni_i;
                uzayliKonum[i][1] = yeni_j;
                tahta[uzayliKonum[i][0]][uzayliKonum[i][1]] = 0;
                hucreYaz(uzayliKonum[i][0], uzayliKonum[i][1]);
            }
        }
        sleep(1000/hiz);
    }
}
#endif
