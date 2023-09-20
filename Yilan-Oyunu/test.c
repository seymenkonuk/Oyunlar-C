#include <stdio.h>
#include "yilanOyunu.h"

main() {
    getch();
    while (1) {
        oynaYilanOyunu(50, 25, 10, 1);
        while (getch() != '\r');
    }
}
