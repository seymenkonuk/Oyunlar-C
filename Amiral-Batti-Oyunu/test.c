#include <stdio.h>
#include "amiralBattiOyunu.h"

main() {
    getch();
    while (1) {
        int gemiUzunluk[7] = {0, 3, 2, 1, 0, 0, 0};
        printf("%d", oynaAmiralBattiOyunu(6, gemiUzunluk));
        while (getch() != '\r');
    }
}
