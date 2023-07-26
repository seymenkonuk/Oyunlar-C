/*
Kullanýcý ile Bilgisayar Arasýnda Artý Eksi Sayý Tahmin Oyunu
Bilgisayar Sayýyý En Fazla 7. Tahmininde Bulur
*/

#ifndef OYUNARTIEKSI_H
#define OYUNARTIEKSI_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/sayiGir.h" // https://github.com/seymenkonuk/Matematik-C commit 1
#include "../lib/rastgele.h" // https://github.com/seymenkonuk/Rastgele-C commit 1

int oynaArtiEksiOyunu(bool zorMod); // Zor Modda Bilgisayar Sayý Tutmaz, Kullanýcýnýn Tahminine Göre En Ýyi Cevabý Verir

int oynaArtiEksiOyunu(bool zorMod) {
    void cevapVer(int sayi1, int sayi2, int cevap[2]) {
        int basamak = 4;
        int basamaklar1[basamak], basamaklar2[basamak], i, j;
        // Basamaklarýna Ayýr
        for (i=0; sayi1>0; i++) {
            basamaklar1[i] = sayi1 % 10;
            sayi1 /= 10;
        }
        for (i=0; sayi2>0; i++) {
            basamaklar2[i] = sayi2 % 10;
            sayi2 /= 10;
        }
        // Artýyý Hesapla
        cevap[0] = 0;
        for (i=0; i<basamak; i++) if (basamaklar1[i] == basamaklar2[i]) cevap[0]++;
        // Eksiyi Hesapla
        cevap[1] = 0;
        for (i=0; i<basamak; i++)
            for (j=0; j<basamak; j++) {
                if (i==j) continue;
                if (basamaklar1[i] == basamaklar2[j]) cevap[1]++;
            }
    }
    bool basamaklariFarkliMi(int sayi) {
        int rakam[10] = {0};
        while (sayi > 0) {
            rakam[sayi%10]++;
            if (rakam[sayi%10] > 1) return false;
            sayi /= 10;
        }
        return true;
    }
    
    int i, j;
    int puanlar[10000] = {0}, havuz = 0, adim = 0, sira = 0, oyuncu = rastgeleAralik(1,2);
    int bilgisayarSayiPuan[10000] = {0}; // Zor Modda Kullanýlacak
    
    // Basamaklarý Farklý Sayýlarý 1 Yap
    for (i=1000; i<10000; i++) {
        if (!basamaklariFarkliMi(i)) continue;
        puanlar[i] = 1; havuz++; bilgisayarSayiPuan[i] = 1;
    }
    system("cls");
    printf("Arti Eksi Sayi Tahmin Oyunu Basliyor...\n");
    
    // Bilgisayar Sayý Tutsun (Zor Mod ise Bu Sayý Önemsizdir)
    int bilgisayarinSayisi;
    do {
        bilgisayarinSayisi = rastgeleAralik(1023, 9876);
    } while (!basamaklariFarkliMi(bilgisayarinSayisi));
    
    int kimKazandi = 0; bool bittiMi = false;
    while (1) {
        sira = (sira%2)+1;
        // HÝLE Yapýldýysa
        if (havuz == 0) {printf("Hile Yaptin!"); return -1;}
        // Oyun Bitti Mi
        if (sira==1) {
            if (bittiMi) {
                // Zor Mod ise Sayý Tut
                if (zorMod)
                    for (i=1000; i<10000; i++)
                        if (bilgisayarSayiPuan[i]==1) {
                            bilgisayarinSayisi = i;
                            break;
                        }
                
                if (kimKazandi == 0) printf("Berabere");
                else if (kimKazandi == 1) printf("Oyuncu Kazandi");
                else printf("Tuttugum Sayi: %d\nBilgisayar Kazandi", bilgisayarinSayisi);
                return adim*kimKazandi;
            }
            adim++;
        }
        
        if (sira==oyuncu) {
            printf("%d. Tahminin: ", adim);
            int kullaniciTahmini;
            while (1) {
                kullaniciTahmini = sayiGirAralik(1023, 9876);
                if (basamaklariFarkliMi(kullaniciTahmini)) break;
                printf("Hatali deger girisi! Tekrar Deger Giriniz!\n");
                printf("%d. Tahminin: ", adim);
            }
            int cevap[2]; 
            
            if (!zorMod)
                cevapVer(kullaniciTahmini, bilgisayarinSayisi, cevap);
            else {
                // Cevaplarý Puanla
                int cevapPuan[5][5] = {0}, enFazlaPuan = 0;
                for (i=1000; i<10000; i++) {
                    if (bilgisayarSayiPuan[i] == 0) continue;
                    int kCevap[2]; cevapVer(kullaniciTahmini, i, kCevap);
                    cevapPuan[kCevap[0]][kCevap[1]]++;
                    if (cevapPuan[kCevap[0]][kCevap[1]] > enFazlaPuan) {
                         enFazlaPuan = cevapPuan[kCevap[0]][kCevap[1]];
                         cevap[0] = kCevap[0];
                         cevap[1] = kCevap[1];
                    }
                }
                
                // Ýhtimalleri Güncelle
                for (i=1000; i<10000; i++) {
                    if (bilgisayarSayiPuan[i] == 0) continue;
                    int kCevap[2]; cevapVer(kullaniciTahmini, i, kCevap);
                    if (kCevap[0] == cevap[0] && kCevap[1] == cevap[1]) continue;
                    bilgisayarSayiPuan[i] = 0;
                }
            }
            
            printf("Bilgisayarin Cevabi: +%d -%d\n", cevap[0], cevap[1]);
            if (cevap[0] == 4) {kimKazandi += 1; bittiMi = true;}
        } else {
            // Tahminleri Puanla
            int enIyiTahminPuani = 10000, adet = 0;
            for (i=1000; i<10000; i++) { // i tahminini yapacak olsam
                if (puanlar[i] == 0) continue;
                int cevaplar[5][5] = {0}, puan = 0;
                for (j=1000; j<10000; j++) {
                    if (puanlar[j] == 0) continue;
                    int cevap[2]; cevapVer(i, j, cevap);
                    cevaplar[cevap[0]][cevap[1]]++;
                    if (cevap[0] < 4 && cevaplar[cevap[0]][cevap[1]] > puan) puan = cevaplar[cevap[0]][cevap[1]];
                }
                puanlar[i] = puan+1;
                if (puan < enIyiTahminPuani) {adet = 1; enIyiTahminPuani = puan; }
                if (puan == enIyiTahminPuani) adet += 1;
            }
            // Tahmin Yap
            int tahmin; adet = rastgeleAralik(0, adet-1);
            for (i = 1000; i < 10000; i++) {
                if (puanlar[i] == enIyiTahminPuani + 1) {
                    tahmin = i; 
                    if (adet == 0) break;
                    adet -= 1;
                }
            }
            
            printf("%d. Tahminim: %d\nCevabin: ", adim, tahmin);
            // Cevap Bekle
            int arti, eksi;
            while (1) {
                scanf("%d %d", &arti, &eksi);
                if (arti >= 0 && arti <= 4 && eksi >= 0 && eksi <= 4 && arti + eksi <= 4) break;
                printf("Hatali deger girisi! Tekrar Deger Giriniz!\n");
                printf("%d. Tahminim: %d\nCevabin: ", adim, tahmin);
            }
            // Doðru Bildin
            if (arti == 4) {kimKazandi -= 1; bittiMi = true;}
            
            // Ýhtimalleri Güncelle
            for (i=1000; i<10000; i++) {
                if (puanlar[i] == 0) continue;
                int cevap[2]; cevapVer(tahmin, i, cevap);
                if (cevap[0] == arti && cevap[1] == eksi) continue;
                // KESÝNLÝKLE Doðru Olamaz
                puanlar[i] = 0; havuz--;
            }
        }
    }
}
#endif
