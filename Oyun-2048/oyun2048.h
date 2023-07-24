/*
2048 Oyunu
*/
#ifndef OYUN2048_H
#define OYUN2048_H
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include "../lib/tahta.h" // https://github.com/seymenkonuk/Tahta-Olusturma-C commit 1
#include "../lib/rastgele.h" // https://github.com/seymenkonuk/Rastgele-C commit 1

void oyna2048Oyunu(int boyut, char kazanmaDegeri); // 2048 oyunu baþlatýr

void oyna2048Oyunu(int boyut, char kazanmaDegeri) {
    void tahtayiCiz(int tahta[boyut][boyut]) {
        int i, j;
        for (i=0; i<boyut; i++) {
            for (j=0; j<boyut; j++) {
                tahtaGit(j+1, i+1);
                if (tahta[i][j] != 0)
                    printf("%c", tahta[i][j] + 'A' - 1);
                else
                    printf(".");
            }
        }
        printf("\n\n");
    }
    void tahtayiDondur(int tahta[boyut][boyut]) {
        int depo[boyut][boyut], i, j;
        for (i=0; i<boyut; i++) for (j=0; j<boyut; j++) depo[i][j] = tahta[i][j];
        for (i=0; i<boyut; i++) for (j=0; j<boyut; j++) tahta[(boyut-1)-j][i] = depo[i][j];
        
    }
    int yercekimi(int tahta[boyut][boyut]) {
        int i, j, maksDeger = 0; bool farkliMi = false;
        bool birlesebilirMi[boyut][boyut];
        for (i=0; i<boyut; i++) for (j=0; j<boyut; j++) birlesebilirMi[i][j] = true;
        
        for (i=boyut-2; i>=0; i--) {
            if (i>=boyut-1) continue;
            bool kontrol = false;
            for (j=0; j<boyut; j++) {
                if (tahta[i][j] == 0) continue;
                if (tahta[i+1][j] == 0) {
                    tahta[i+1][j] = tahta[i][j];
                    tahta[i][j] = 0;
                    kontrol = true;
                    farkliMi = true;
                } else if (tahta[i+1][j] == tahta[i][j] && birlesebilirMi[i][j] && birlesebilirMi[i+1][j]) {
                    birlesebilirMi[i+1][j] = false;
                    tahta[i+1][j]++;
                    tahta[i][j] = 0;
                    farkliMi = true;
                }
            }
            if (kontrol) i+=2;
        }
        for (i=0; i<boyut; i++) for (j=0; j<boyut; j++) if (tahta[i][j]>maksDeger) maksDeger = tahta[i][j];
        if (!farkliMi) return 0;
        return maksDeger;
    }
    
    if (kazanmaDegeri > 'Z') kazanmaDegeri = 'Z';
    int i, j;
    int tahta[boyut][boyut]; for (i=0; i<boyut; i++) for (j=0; j<boyut; j++) tahta[i][j] = 0;
    bool kontrol[4];
    
    tahta[rastgeleAralik(0, boyut-1)][rastgeleAralik(0, boyut-1)] = 1;
    
    tahtaOlustur(boyut, boyut, 0);
    while (1) {
        int r_i, r_j;
        do {
            r_i = rastgeleAralik(0, boyut-1);
            r_j = rastgeleAralik(0, boyut-1);
        } while (tahta[r_i][r_j] != 0);
        tahta[r_i][r_j] = 1;
        if (rastgeleAralik(1, 100) <= 30) tahta[r_i][r_j] = 2; // %30 ihtimalle 
        tahtayiCiz(tahta);
        
        bool devamEdiyorMu = false;
        for (i=0; i<4; i++) {
            int kontrolTahta[boyut][boyut], k;
            for (j=0; j<boyut; j++) for (k=0; k<boyut; k++) kontrolTahta[j][k] = tahta[j][k];
            kontrol[i] = (yercekimi(kontrolTahta) != 0);
            devamEdiyorMu = devamEdiyorMu || kontrol[i];
            tahtayiDondur(tahta);
        }
        if (!devamEdiyorMu) {
            tahtayiCiz(tahta);
            printf("Kaybettin!"); 
            return; 
        }
        char tus; int adet;
        while (1) {
            tus = getch();
            if (tus == 's' || tus == 'S') {
                if (kontrol[0]) {
                    adet = 0;
                    break;
                }
            } else if (tus == 'a' || tus == 'A') {
                if (kontrol[1]) {
                    adet = 1;
                    break;
                }
            } else if (tus == 'w' || tus == 'W') {
                if (kontrol[2]) {
                    adet = 2;
                    break;
                }
            } else if (tus == 'd' || tus == 'D') {
                if (kontrol[3]) {
                    adet = 3;
                    break;
                }
            } 
        }
        
        for (i=0; i<adet; i++) tahtayiDondur(tahta);
        int maksBlok = yercekimi(tahta);
        if (adet != 0) for (i=adet; i<4; i++) tahtayiDondur(tahta);
        
        if (maksBlok-1+'A' >= kazanmaDegeri) {
            tahtayiCiz(tahta);
            printf("Kazandin!"); 
            return; 
        }
    }
}
#endif
