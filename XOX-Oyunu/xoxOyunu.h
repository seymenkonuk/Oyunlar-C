/*
Kullanýcý ile Bilgisayar Arasýnda Oynanabilen XOX Oyunu
*/

#ifndef XOXOYUNU_H
#define XOXOYUNU_H
#include <stdio.h>

int tahta[9];

// Fonksiyonlar
int xoxOyna(int sira);
void tahtayiGoster();
void hamleYapOyuncu();
void hamleYapPC();
int analizEt(int konum, int adim);
int oyunBittiMi();

int xoxOyna(int sira) {
    if (sira != 1 && sira != 2) return 0;
    int i, hamle;
    
    for (i=0; i<9; i++) tahta[i] = 0; // Tahtayý Sýfýrla
    
    tahtayiGoster();
    for (hamle = 1; hamle <=9; hamle++) {
        getch();
        if (hamle % 2 == sira % 2) // Oyuncunun Sýrasý
            hamleYapOyuncu();
        else                       // Bilgisayarýn Sýrasý
            hamleYapPC();
        
        tahtayiGoster(sira);
        
        int sonuc = oyunBittiMi();
        if (sonuc == 1)
            return (hamle+1)/2;    // Oyuncu x Hamlede Kazandý
        else if (sonuc == 2)
            return -1*(hamle+1)/2; // Bilgisayar x Hamlede Kazandý
    }
    return 0; // Berabere
}

void tahtayiGoster(int sira) {
    int i;
    system("cls");
    for (i=0; i<9; i++) {
             if (tahta[i] == 0)    printf(". ");
        else if (tahta[i] == sira) printf("X ");
        else                       printf("O ");
        
        if ((i+1)%3 == 0) printf("\n");
    }
}

void hamleYapOyuncu() {
    int konum;
    do {
        printf("Konum giriniz: ");
        scanf("%d", &konum);
        konum--;
    } while (konum < 0 || konum >= 9 || tahta[konum] != 0);
    tahta[konum] = 1;
}

void hamleYapPC() {
    int i, konum, enIyiPuan = -10;
    for (i=0; i<9; i++) {
        if (tahta[i] != 0) continue;
        int puan = analizEt(i, 0);
        if (puan > enIyiPuan) {
            enIyiPuan = puan;
            konum = i;
        }
    }
    tahta[konum] = 2;
}

int analizEt(int konum, int adim) {
    int x = adim % 2;
    if (x == 0) x = 2;
    // adim % 2 == 0 bilgisayarýn sýrasý
    tahta[konum] = x;
    int bittiMi = oyunBittiMi();
    if (bittiMi != 0) {
        tahta[konum] = 0;
        if (bittiMi == 2)
            return 1;
        if (bittiMi == 1)
            return -1;
    }
    
    int i, sonuc = -100;
    for (i=0; i<9; i++) {
        if (tahta[i] != 0) continue;
        int puan = analizEt(i, adim+1);
        
        if (sonuc == -100) {
            sonuc = puan;
            continue;
        }
        
        if ((adim%2==1 && puan > sonuc)
        ||  (adim%2==0 && puan < sonuc))
            sonuc = puan;
    }
    
    tahta[konum] = 0;
    if (sonuc == -100)
        return 0;
    return sonuc;
}

int oyunBittiMi() {
    int i, j;
    // Yatay Kontrol
    for (i=0; i<3; i++) {
        if (tahta[i*3] == 0) continue;
        for (j=1; j<3 && tahta[i*3] == tahta[i*3+j]; j++);
        if (j<3) continue;
        return tahta[i*3];
    }
    // Dikey Kontrol
    for (j=0; j<3; j++) {
        if (tahta[j] == 0) continue;
        for (i=1; i<3 && tahta[j] == tahta[i*3+j]; i++);
        if (i<3) continue;
        return tahta[j];
    }
    // Çapraz Kontrol
    if (tahta[4] != 0) { // Merkez 0 Deðilse
        if (tahta[0] == tahta[4] && tahta[4] == tahta[8])
            return tahta[4];
        if (tahta[2] == tahta[4] && tahta[4] == tahta[6])
            return tahta[4];
    }
    return 0; // Oyun Bitmedi
}
#endif
