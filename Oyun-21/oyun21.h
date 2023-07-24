/*
N Kiþilik 21 Oyunu Baþlatýr
*/
#ifndef OYUN21_H
#define OYUN21_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../lib/rastgele.h" // https://github.com/seymenkonuk/Rastgele-C commit 1

void oyna21Oyunu(); // N Kiþilik 21 Oyunu Baþlatýr

void oyna21Oyunu() {
    int oyuncu_sayisi, kalan_kart_sayisi = 52, sira = 0, deste[52], i, j;
    
    do {
        system("cls");
        printf ("Oyuncu sayisini giriniz: ");
        scanf ("%d", &oyuncu_sayisi);
    } while (oyuncu_sayisi > 52);
    
    int puanlar[oyuncu_sayisi]; for (i=0; i<oyuncu_sayisi; i++) puanlar[i] = 0;
    int kac1var[oyuncu_sayisi]; for (i=0; i<oyuncu_sayisi; i++) kac1var[i] = 0;
    bool oynama_hakki[oyuncu_sayisi]; for (i=0; i<oyuncu_sayisi; i++) oynama_hakki[i] = true;
    
    // Desteyi Karýþtýr
    {
        int kartlar[52] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
        bool secildiMi[52]; for (i=0; i<52; i++) secildiMi[i] = false;
        for (i=0; i<52; i++) {
            int rastgele;
            do {
                rastgele = rastgeleAralik(0, 51);
            } while (secildiMi[rastgele]);
            secildiMi[rastgele] = true;
            deste[i] = kartlar[rastgele];
        }
    }
    
    while (1) {
        sira = (sira%oyuncu_sayisi) + 1;
        if (oynama_hakki[sira-1]) {
            system("cls");
            for (i=0; i<oyuncu_sayisi; i++) {
                if (oyuncu_sayisi >= 10 && (i+1) < 10) printf(" ");
                printf("%d. Oyuncu: %d", i+1, puanlar[i]);
                
                for (j=1; j<=kac1var[i]; j++) printf("/%d", puanlar[i]+10*j);
                
                if (puanlar[i] > 21)
                    printf(" (Kaybetti)");
                else if (!oynama_hakki[i])
                    printf(" (Bekliyor)");
                printf("\n");
            }
            if (puanlar[sira-1] > 21) {
                oynama_hakki[sira-1] = false; 
                continue; 
            }
        } else {
            for (i=0; i<oyuncu_sayisi; i++) if (oynama_hakki[i]) break;
            if (kalan_kart_sayisi == 0 || i == oyuncu_sayisi) break;
            continue;
        }
        
        int hamle;
        printf("\nSira %d. Oyuncuda - Kart cekmek icin 1, pas gecmek icin 2 yaz: ", sira);
        scanf("%d",&hamle);
        if (hamle == 1) {
            puanlar[sira-1] += deste[kalan_kart_sayisi - 1];
            if (deste[kalan_kart_sayisi - 1] == 1) kac1var[sira-1]++;
            kalan_kart_sayisi--;
        } else if (hamle == 2) {
            oynama_hakki[sira-1] = false;
        } else {
            sira--;
            printf("Hatali Giris! - Tekrar Hamle Yap!\n\n");
            continue;
        }
    }
    
    printf("\nOyun Bitti: ");
    int maxpuan = 0, kazanan = 0, x = 0;
    for (i=0; i<oyuncu_sayisi; i++) {
        if (puanlar[i] <= 21 && puanlar[i] > maxpuan)
            maxpuan = puanlar[i];
        else if (kac1var[i] >= 1 && puanlar[i] + 10 <= 21 && puanlar[i] + 10 > maxpuan)
            maxpuan = puanlar[i] + 10;
    }
    for (i=0; i<oyuncu_sayisi; i++) if (puanlar[i] == maxpuan || (kac1var[i]>0 && puanlar[i]+10 == maxpuan)) kazanan++;
    if (kazanan == 0)
        printf("Kimse kazanamadi");
    else if (kazanan == oyuncu_sayisi)
        printf("Berabere");
    else {
        for (i=0; i<oyuncu_sayisi; i++) {
            if (puanlar[i] == maxpuan || (kac1var[i]>0 && puanlar[i]+10 == maxpuan)) {
                printf("%d.", i+1);
                x++;
                if (x == kazanan) break;
                if (x == kazanan-1) printf(" ve ");
                else printf(", ");
            }
        }
        printf(" Oyuncu Kazandi!");
    }
}
#endif
