/*
Daha Ýyi Rastgele Fonksiyonlarý
*/

#ifndef RASTGELE_H
#ifndef ESKIRASTGELE_H
#define RASTGELE_H
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define srand(x) {srand(x); karistirildiMi = true;}

static bool karistirildiMi = false;

long long int rastgeleAralik(long long int min, long long int maks); // min maks arasýnda rastgele sayý döndürür. RAND_MAX limiti yoktur.

long long int rastgeleAralik(long long int min, long long int maks) {
    if (!karistirildiMi) srand(time(NULL)); // srand daha önce hiç çalýþtýrýlmadýysa srand çalýþtýr
    if (min > maks) return rastgeleAralik(maks, min);
    unsigned long long int fark = maks - min; // min-maks arasý deðil, 0-fark arasý sayý belirleyeceðiz
    unsigned long long int sonuc;
    if (fark>RAND_MAX) { // rand fonksiyonu yetmiyorsa
        // Kaç bit olduðunu bul
        int kacBit = 0;
        {
            unsigned long long int depo = fark;
            while (depo > 0) {
                depo = depo/2;
                kacBit++;
            }
        }
        while (1) {
            sonuc = 0; int i;
            // O kadar bit sayý üret
            for (i=0; i<kacBit; i++) {
                int bit = rastgeleAralik(0, 1);
                sonuc = sonuc*2+bit;
            }
            if (sonuc <= fark) break;
        }
    } else { // rand limitleri içerisindeyse
        do {
            sonuc = rand();
        } while (sonuc > RAND_MAX - (RAND_MAX+1)%(fark+1));
        sonuc = sonuc % (fark + 1);
    }
    return sonuc + min;
}
#endif
#endif
