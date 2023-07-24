#include <stdio.h>
#include "bahcedekiHirsizOyunu.h"

main() {
    getch();
    while (1) {
        oynaBahcedekiHirsizOyunu(25, 25, 3);
        
        while (getch() != '\r');
    }
}
