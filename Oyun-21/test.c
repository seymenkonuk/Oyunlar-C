#include <stdio.h>
#include "oyun21.h"

main() {
    getch();
    while (1) {
        oyna21Oyunu();
        while (getch() != '\r');
    }
}
