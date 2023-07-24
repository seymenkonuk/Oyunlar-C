/*
Kelime Tahmin Oyunu
Zor Mod: ÝPUÇLARI KULLANILMAK ZORUNDA
Gün boyunca ayný kelime sorulur. 
*/
#ifndef SOZCUKOYUNU_H
#define SOZCUKOYUNU_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../lib/rastgele.h" // https://github.com/seymenkonuk/Rastgele-C commit 1

int oynaSozcukOyunu(int harf, bool zorMod);

int oynaSozcukOyunu(int harf, bool zorMod) {
    // Türkçe Karakter 
    int dosyaHarflerTR[29] = {};
    int terminalKHarfler[29] = {0};
    int terminalBHarfler[29] = {0};
    int i, karakter = 'A';
    for (i=1; i<=29; i++) {
        if (i==4 || i==9 || i==12 || i==19 || i==23 || i==26) continue;
        while (karakter == 'Q' || karakter == 'W' || karakter == 'X') karakter++;
        dosyaHarflerTR[i-1] = karakter;
        terminalBHarfler[i-1] = karakter;
        terminalKHarfler[i-1] = karakter - ('A'-'a');
        karakter++;
    }
    dosyaHarflerTR[3] = -57; terminalBHarfler[3] = -128; terminalKHarfler[3] = -121;
    dosyaHarflerTR[8] = -48; terminalBHarfler[8] = -90; terminalKHarfler[8] = -89;
    dosyaHarflerTR[11] = -35; terminalBHarfler[11] = -104; terminalKHarfler[11] = 105; /*i*/ terminalKHarfler[10] = -115; // ý
    dosyaHarflerTR[18] = -42; terminalBHarfler[18] = -103; terminalKHarfler[18] = -108;
    dosyaHarflerTR[22] = -34; terminalBHarfler[22] = -98; terminalKHarfler[22] = -97;
    dosyaHarflerTR[25] = -36; terminalBHarfler[25] = -102; terminalKHarfler[25] = -127;
    // Türkçe Karakter
    
    int enFazlaKacTaneHarf[29]; for (i=0; i<29; i++) enFazlaKacTaneHarf[i] = harf;
    int enAzKacTaneHarf[29]; for (i=0; i<29; i++) enAzKacTaneHarf[i] = 0;
    int dogrular[harf]; for (i=0; i<harf; i++) dogrular[i] = 0;
    
    int kelimeleriOku(int adet, char dizi[adet][harf+1]) {
        int i, sonuc = 0;
        FILE* dosya; dosya = fopen("kelimeler.txt", "r");
        if (dosya == NULL) return -1;
        char kelime[1000];
        while (!feof(dosya)) {
            fscanf(dosya, "%s\n", &kelime);
            for (i=0; kelime[i] != '\0'; i++);
            if (harf != i) continue;
            if (dizi != NULL) for (i=0; i<=harf; i++) dizi[sonuc][i] = kelime[i];
            sonuc++;
        }
        fclose(dosya);
        return sonuc;
    }
    
    int kacinciHarfDosya(int harf) {
        int i; for (i=0; i<29; i++) if (dosyaHarflerTR[i] == harf) return i;
        return -1;
    }
    
    int kacinciHarfTerminal(int harf) {
        int i; for (i=0; i<29; i++) if (terminalBHarfler[i] == harf || terminalKHarfler[i] == harf) return i;
        return -1;
    }
    
    int tahminYap(int adet, char dizi[adet][harf+1]) {
        int i, j, index = 0, kontrol = 0;
        char kelime[harf+1];  kelime[harf] = '\0';
        int kacTaneHarf[29]; for (i=0; i<29; i++) kacTaneHarf[i] = 0;
        
        while (1) {
            char karakter = getch();
            int karakterDegeri = kacinciHarfTerminal(karakter);
            
            for (i=0; i<kontrol; i++) printf(" ");
            for (i=0; i<kontrol; i++) printf("%c", 8);
            kontrol = 0;
            
            if (karakterDegeri != -1) {
                if (index < harf && kacTaneHarf[karakterDegeri] < enFazlaKacTaneHarf[karakterDegeri]) {
                    kacTaneHarf[karakterDegeri]++;
                    printf("%c", terminalBHarfler[karakterDegeri]);
                    kelime[index] = dosyaHarflerTR[karakterDegeri];
                    index++;
                }
            } else if (karakter == '\r') {
                if (index == harf) {
                    int sonuc; bool ayniMi;
                    for (i=0; i<adet; i++) {
                            ayniMi = true;
                            for (j=0; j<harf; j++) if (dizi[i][j] != kelime[j]) ayniMi = false;
                            if (ayniMi) {sonuc = i; break;}
                        }
                    
                    if (ayniMi) { // Kelimeler Listesinde Var Mý
                        bool kurallaraUygunMu = true;
                        if (zorMod) {
                            for (i=0; i<29; i++) {
                                if (enAzKacTaneHarf[i] > kacTaneHarf[i]) {
                                    kurallaraUygunMu = false;
                                }
                            }
                            for (i=0; i<harf; i++) if (dogrular[i] != 0 && dogrular[i] != kelime[i]) kurallaraUygunMu = false;
                        }
                        if (kurallaraUygunMu) { printf("\n"); return sonuc;}
                        printf(" (LUTFEN KURALLARA UYGUN BIR KELIME GIRINIZ)");
                        kontrol = 44; //UYARI MESAJININ UZUNLUGU
                    } else {
                        printf(" (LUTFEN ANLAMLI BIR KELIME GIRINIZ)");
                        kontrol = 36; //UYARI MESAJININ UZUNLUGU
                    }
                } else {
                    printf(" (%d HARFLI BIR KELIME GIRINIZ)", harf);
                    kontrol = 30; //UYARI MESAJININ UZUNLUGU
                    for (i=harf; i/10!=0; i/=10) kontrol++;
                }
            } else if (karakter == 8) { // backspace
                if (index > 0) {
                    index--;
                    kacTaneHarf[kacinciHarfDosya(kelime[index])]--;
                    printf("%c %c", 8, 8);
                }
            }
            
            for (i=0; i<kontrol; i++) printf("%c", 8);
        }
    }
    
    void bilgilendirmeMetni() {
        printf("Kelime Tahmin Oyununa Hosgeldin!");
        printf("\nOYUN HAKKINDA:");
        printf("\nTahminlerinizi lutfen buyuk harfle yapiniz.");
        printf("\n+: harf kelimede var ve dogru yerde.");
        printf("\n*: harf kelimede var fakat yanlis yerde.");
        printf("\n-: harf kelimede yok.\n\n");
    }
    
    int seed = ((time(NULL) / 60) / 60) / 24; srand(seed*10000);
    
    bilgilendirmeMetni();
    int adet = kelimeleriOku(1, NULL);
    if (adet == -1) { printf("Kelime Dosyasi Bulunamadi!\n"); return -1;}
    if (adet == 0) { printf("Kelime Bulunamadi!\n"); return -2;}
    char kelimeler[adet][harf+1];
    kelimeleriOku(adet, kelimeler);
    int dogruKelime = rastgeleAralik(0, adet-1);
    
    int tahminHakki = 6;
    for (i=1; i<=tahminHakki; i++) {
        printf("%d. Tahmininizi Giriniz: ", i);
        int tahmin = tahminYap(adet, kelimeler);
        if (tahmin == dogruKelime) {
            printf("\n\nTEBRIKLER! KAZANDIN!");
            return i;
        }
        // Tahminin Cevabýný Ver
        int j, k; for (j=0; j<24; j++) printf(" ");
        for (j=i; j/10!=0; j/=10) printf(" ");
        char cevap[harf+1]; cevap[harf] = '\0';
        bool kullanildiMi[harf]; 
        for (j=0; j<harf; j++) kullanildiMi[j] = false;
        for (j=0; j<harf; j++) cevap[j] = '-';
        for (j=0; j<harf; j++) 
            if (kelimeler[dogruKelime][j] == kelimeler[tahmin][j]) {
                kullanildiMi[j] = true;
                cevap[j] = '+';
                dogrular[j] = kelimeler[dogruKelime][j];
            }
        for (j=0; j<harf; j++) 
            for (k=0; k<harf; k++)  {
                if (j==k || kullanildiMi[k]) continue;
                if (kelimeler[dogruKelime][k] == kelimeler[tahmin][j]) {
                    kullanildiMi[k] = true;
                    cevap[j] = '*';
                }
            }
        if (zorMod) {
            for (j=0; j<harf; j++) {
                int kacTane = 0;
                for (k=0; k<harf; k++)
                    if (kelimeler[tahmin][j] == kelimeler[tahmin][k] && cevap[k] != '-')
                        kacTane++;
                if (cevap[j] == '-')
                    enFazlaKacTaneHarf[kacinciHarfDosya(kelimeler[tahmin][j])] = kacTane;
                else 
                    enAzKacTaneHarf[kacinciHarfDosya(kelimeler[tahmin][j])] = kacTane;
            }
        }
        printf("%s\n", cevap);
    }
    
    printf("\n\nKAYBETTIN!\nDOGRU KELIME: "); 
    // Doðru Kelimeyi Yazdýrma Ýþlemi
    for (i=0; i<harf; i++) printf("%c", terminalBHarfler[kacinciHarfDosya(kelimeler[dogruKelime][i])]);
    printf("\n");
    return -3;
}
#endif
