#include <stdio.h>
#include "nisanciOyunu.h"

main() {
    getch();
    while (1) {
        oynaNisanciOyunu(10, 25);
        while (getch() != '\r');
    }
}
