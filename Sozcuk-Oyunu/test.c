#include <stdio.h>
#include <stdbool.h>
#include "sozcukOyunu.h"

main() {
    getch();
    while (1) {
        oynaSozcukOyunu(5, false);
        while (getch() != '\r');
    }
}
