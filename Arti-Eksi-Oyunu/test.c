#include <stdio.h>
#include "oyunArtiEksi.h"

main() {
    getch();
    while (1) {
        oynaArtiEksiOyunu();
        while (getch() != '\r');
    }
}
