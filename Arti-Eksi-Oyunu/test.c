#include <stdio.h>
#include "oyunArtiEksi.h"

main() {
    getch();
    while (1) {
        oynaArtiEksiOyunu(true);
        while (getch() != '\r');
    }
}
