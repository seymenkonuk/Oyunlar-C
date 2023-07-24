#include <stdio.h>
#include "oyunMayinTarlasi.h"

main() {
    getch();
    while (1) {
        // Boþluk ile Bayrak Koy/Geri Al
        // Enter ile Aç/Týkla
        // W A S D ile hareket et
        oynaMayinTarlasiOyunu(10, 10, 10);
        while (getch() != '\r');
    }
}
