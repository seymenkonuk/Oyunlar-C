/*
Mayýn Tarlasý Oyunu
*/
#ifndef OYUNMAYINTARLASI_H
#define OYUNMAYINTARLASI_H
#include <stdio.h>
#include <stdbool.h>
#include "../lib/rastgele.h" // https://github.com/seymenkonuk/Rastgele-C commit 1
#include "../lib/tahta.h" // https://github.com/seymenkonuk/Tahta-Olusturma-C commit 1

bool oynaMayinTarlasiOyunu(int genislik, int yukseklik, int mayinSayisi);

bool oynaMayinTarlasiOyunu(int genislik, int yukseklik, int mayinSayisi) {
    int yonler[8][2] = {{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0},{-1, -1}, {0, -1}, {1, -1}};
    int tahta[yukseklik][genislik];
    int arazi[yukseklik][genislik];
    
    void hucreYaz(int i, int j) {
        tahtaGit(j+1, i+1);
        if (tahta[i][j] == -1)
            printf(".");
        else if (tahta[i][j] == -10)
            printf("X");
        else if (tahta[i][j] == -11) // BAYRAK
            printf("F");
        else if (tahta[i][j] == 0)
            printf("-");
        else
            printf("%d", tahta[i][j]);
        tahtaGit(j+1, i+1);
    }
    
    void etrafaTikla(int i, int j) {
        tahta[i][j] = arazi[i][j];
        hucreYaz(i, j);
        if (tahta[i][j] != 0) return;
        int k;
        for (k=0; k<8; k++) {
            int yeni_i = i + yonler[k][0];
            int yeni_j = j + yonler[k][1];
            if (yeni_i >= 0 && yeni_i < yukseklik)
                if (yeni_j >= 0 && yeni_j < genislik)
                    if (tahta[yeni_i][yeni_j] == -1)
                        etrafaTikla(yeni_i, yeni_j);
        }
    }
    
    bool kazandinMi() {
        int i, j;
        for (i=0; i<yukseklik; i++)
            for (j=0; j<genislik; j++)
                if ((tahta[i][j] == -1 || tahta[i][j] == -11) && arazi[i][j] != -10)
                    return false;
        return true;
    }
    
    tahtaOlustur(genislik, yukseklik, 0);
    
    // Arazi ve Tahtayý Sýfýrla
    int i, j, k;
    for (i=0; i<yukseklik; i++) for (j=0; j<genislik; j++) {arazi[i][j] = 0; tahta[i][j] = -1;}
    // Mayýnlarý Oluþtur
    for (i=0; i<mayinSayisi && i<genislik*yukseklik; i++) {
        int rastgele_i, rastgele_j;
        do {
            rastgele_i = rastgeleAralik(0, yukseklik-1);
            rastgele_j = rastgeleAralik(0, genislik-1);
        } while (arazi[rastgele_i][rastgele_j] != 0);
        arazi[rastgele_i][rastgele_j] = -10;
    }
    // Araziyi Güncelle
    for (i=0; i<yukseklik; i++)
        for (j=0; j<genislik; j++)
            if (arazi[i][j] == 0)
                for (k=0; k<8; k++) {
                    int yeni_i = i + yonler[k][0];
                    int yeni_j = j + yonler[k][1];
                    if (yeni_i >= 0 && yeni_i < yukseklik)
                        if (yeni_j >= 0 && yeni_j < genislik)
                            if (arazi[yeni_i][yeni_j] == -10)
                                arazi[i][j] += 1;
                }
    
    // Tahtayý Göster
    for (i=0; i<yukseklik; i++) for (j=0; j<genislik; j++) hucreYaz(i, j);
    tahtaGit(1,1);
    while (1) {
        char tus = getch();
        tahtaKontrol(tus, 0);
        if (tus == '\r' && tahta[konumy-1][konumx-1] == -1) {
            etrafaTikla(konumy-1, konumx-1);
            if (tahta[konumy-1][konumx-1] == -10) {tahtaGit(genislik, yukseklik); printf("\n\nKaybettin!\n"); return false;}
            if (kazandinMi()) {tahtaGit(genislik, yukseklik); printf("\n\nKazandin!\n"); return true;}
        } else if (tus == 32 && tahta[konumy-1][konumx-1] == -1) {// boþluk
            tahta[konumy-1][konumx-1] = -11;
            hucreYaz(konumy-1, konumx-1);
        } else if (tus == 32 && tahta[konumy-1][konumx-1] == -11) {
            tahta[konumy-1][konumx-1] = -1;
            hucreYaz(konumy-1, konumx-1);
        }
    }
}
#endif
