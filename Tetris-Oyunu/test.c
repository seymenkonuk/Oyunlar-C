#include <stdio.h>
#include "tetrisOyunu.h"

main() {
    getch();
    while (1) {
        oynaTetrisOyunu(10, 20);
        printf("Bitti!");
        while (getch() != '\r');
    }
}
