#include <stdio.h>
#include "oyunMayinTarlasi.h"

main() {
    getch();
    while (1) {
        // Bo�luk ile Bayrak Koy/Geri Al
        // Enter ile A�/T�kla
        // W A S D ile hareket et
        oynaMayinTarlasiOyunu(10, 10, 10);
        while (getch() != '\r');
    }
}
