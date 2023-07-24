#include <stdio.h>
#include "oyun2048.h"

main() {
    getch();
    while (1) {
        oyna2048Oyunu(5, 'Z');
        while (getch() != '\r');
    }
}
