/*
Bilgisayar, Amiral Batt� Oyununda Kullan�c�n�n Gemilerinin Konumunu Bulmaya �al���r
*/

#ifndef AMIRALBATTIOYUNU_H
#define AMIRALBATTIOYUNU_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/rastgele.h" // https://github.com/seymenkonuk/Rastgele-C

int oynaAmiralBattiOyunu(int boyut, int gemiUzunluk[boyut+1]);

int oynaAmiralBattiOyunu(int boyut, int gemiUzunluk[boyut+1]) {
    int tahtaSec(int kacinci, int tahta[boyut][boyut], int tahmin[boyut][boyut], int puan[boyut][boyut]) {
        int i, j, k, m, n, sonuc=0;
        int platform[boyut][boyut]; for (i=0; i<boyut; i++) for (j=0; j<boyut; j++) platform[i][j] = tahmin[i][j];
        if (puan != NULL) for (i=0; i<boyut; i++) for (j=0; j<boyut; j++) puan[i][j] = 0;
        
        // Bitmemi� Gemi Uzunluklar�n� Bul
        int bitmemisGemiUzunluk[boyut+1];
        int toplamGemiAdedi = 0;
        for (i=0; i<boyut+1; i++) {
            toplamGemiAdedi += i*gemiUzunluk[i];
            bitmemisGemiUzunluk[i] = gemiUzunluk[i];
            for (j=0; j<i; j++) bitmemisGemiUzunluk[j] += gemiUzunluk[i];
        }
        
        i=0; j=0; int yon = 1;
        while (1) {
                    
            // j ileriden Limit D���na ��kt�ysa
            if (j>=boyut) {
                j=0; i++; 
                // Do�ru Tahtalardan Birisi Bulundu
                if (i>=boyut) {
                    sonuc++;
                    // T�m ��z�mlerde 
                    if (puan != NULL)
                        for (m=0; m<boyut; m++)
                            for (n=0; n<boyut; n++)
                                puan[m][n] += platform[m][n];
                    
                    // Geriye De�er D�nd�recekse
                    if (tahta != NULL && sonuc == kacinci) {
                        for (i=0; i<boyut; i++)
                            for (j=0; j<boyut; j++)
                                tahta[i][j] = platform[i][j];
                        return sonuc;
                    }
                    i=boyut-1; j=boyut-1;
                    yon = -1; continue;
                }
            }
            // j geriden Limit D���na ��kt�ysa
            if (j==-1) {
                j=boyut-1; i--;
                // Ba�ka Tahta Kalmad�
                if (i==-1) {return sonuc;}
            }
            
            if (tahmin[i][j] == -1) {
                platform[i][j]++;
                yon = 1;
            } else {
                j+=yon;
                continue;
            }
            
            // platform[i][j] Alamayaca�� Bir De�er Ald�ysa
            if (platform[i][j]>1) {
                platform[i][j] = -1;
                j--;
                yon = -1;
                continue;
            }
            
            // �imdilik Do�ru Bir De�er Ald�ysa
            bool dogruMu = true;
            
            // �apraz�nda 1 Olamaz
            if (platform[i][j] == 1) {
                int yonler[4][2] = {{1,1}, {-1,1}, {1,-1}, {-1,-1}};
                for (k=0; k<4; k++) {
                    int yeni_i = i+yonler[k][0];
                    int yeni_j = j+yonler[k][1];
                    if (yeni_i<0 || yeni_i>=boyut) continue;
                    if (yeni_j<0 || yeni_j>=boyut) continue;
                    if (platform[yeni_i][yeni_j] == 1) {
                        dogruMu = false;
                        break;
                    }
                }
            }
            if (!dogruMu) continue;
            
            // Gemi Adeti Fazla Veya Eksik Mi
            int bosluk = 0, bir = 0;
            for (m=0; m<boyut; m++) {
                for (n=0; n<boyut; n++) {
                    // Bo�luklar� Say
                    if (platform[m][n] == -1) bosluk++;
                    if (platform[m][n] == 1) bir++;
                }
            }
            if (bir > toplamGemiAdedi) continue; // Fazla
            if (bosluk+bir < toplamGemiAdedi) continue;
            
            // Gemi Uzunluk Kontrol Yeterli Mi
            int tBitmisGemiUzunluk[boyut+1]; for (k=0; k<boyut+1; k++) tBitmisGemiUzunluk[k]=0;
            int tBitmemisGemiUzunluk[boyut+1]; for (k=0; k<boyut+1; k++) tBitmemisGemiUzunluk[k]=0;
            
            for (m=0; m<boyut; m++) {
                for (n=0; n<boyut; n++) {
                    // Gemi De�ilse
                    if (platform[m][n] != 1) continue;
                    
                    // Daha �nce Zaten Bak�ld�ysa
                    if (m-1>=0 && platform[m-1][n] == 1) continue; 
                    if (n-1>=0 && platform[m][n-1] == 1) continue; 
                    
                    int uzunluk; bool gemiBitmisMi = true;
                    // Sa��na Bak, Uzunluk Say
                    for (k=n; k<boyut; k++) if (platform[m][k] != 1) break;
                    uzunluk = k-n;
                    if (k<boyut && platform[m][k] == -1) gemiBitmisMi = false;
                    
                    // A�a��s�na Bak, Uzunluk Say
                    if (uzunluk == 1) { // Uzunluk 1 den B�y�kse A�a��s� Zaten Olamaz
                        for (k=m; k<boyut; k++) if (platform[k][n] != 1) break;
                        uzunluk = k-m;
                        if (k<boyut && platform[k][n] == -1) gemiBitmisMi = false;
                    }
                    
                    // Gemi Bitmi� Mi
                    if (n-1>=0 && platform[m][n-1] == -1) gemiBitmisMi = false;
                    if (m-1>=0 && platform[m-1][n] == -1) gemiBitmisMi = false;
                    
                    tBitmemisGemiUzunluk[uzunluk]++;
                    if (tBitmemisGemiUzunluk[uzunluk] > bitmemisGemiUzunluk[uzunluk]) dogruMu = false;
                    
                    if (gemiBitmisMi) {
                        tBitmisGemiUzunluk[uzunluk]++;
                        if (tBitmisGemiUzunluk[uzunluk] > gemiUzunluk[uzunluk]) dogruMu = false;
                    }
                }
            }
            
            if (!dogruMu) continue;
            j++;
        }
    }
    
    // FONKS�YON BA�LANGICI
    int i, j; system("cls");
    printf("Amiral Batti Oyunu Basliyor...\n");
    // Kullan�c�n�n Tahtas� Hakk�ndaki Bilgisayar Tahmini
    int tahtaKullanici[boyut][boyut]; 
    for (i=0; i<boyut; i++) for (j=0; j<boyut; j++) tahtaKullanici[i][j] = -1;
    
    int adim = 0;
    while (1) {
        adim++;
        int puan[boyut][boyut];
        int gemiAdet = tahtaSec(0, NULL, tahtaKullanici, puan); // gemiAdet = ka� farkl� �ekilde tahta dizilebilir
            
        if (gemiAdet == 1) { // Tahta Tahmini Yap
            int tahminPC[boyut][boyut];
            tahtaSec(1, tahminPC, tahtaKullanici, NULL);
            printf("Gemilerinin Konumu:\n");
            for (i=0; i<boyut; i++) {
                for (j=0; j<boyut; j++)
                    printf("%d ", tahminPC[i][j]);
                printf("\n");
            }
            return adim;
        } else { // H�cre Tahmini Yap
            int tahmin_i=0, tahmin_j=0;
            for (i=0; i<boyut; i++) {
                for (j=0; j<boyut; j++) {
                    int puan1 = puan[i][j] - gemiAdet/2; if (puan1<0) puan1 = -puan1;
                    int puan2 = puan[tahmin_i][tahmin_j] - gemiAdet/2; if (puan2<0) puan2 = -puan2;
                    if (puan1<puan2) {
                        tahmin_i = i;
                        tahmin_j = j;
                    }
                }
            }
            printf("%d. Bilgisayarin Tahmini: %d, %d -> ", adim, tahmin_i, tahmin_j);
            int kullaniciCevap;
            do {
                kullaniciCevap = getch();
            } while (!(kullaniciCevap=='1' || kullaniciCevap=='0'));
            tahtaKullanici[tahmin_i][tahmin_j] = kullaniciCevap-'0';
            printf("%c\n", kullaniciCevap);
        }
    }
}
#endif
