#include <stdio.h>
#include "tetrisOyunu.h"

main() {
    getch();
    while (1) {
        printf("Bitti!\nPuanin: %d", oynaTetrisOyunu(10, 20));
        while (getch() != '\r');
    }
}
