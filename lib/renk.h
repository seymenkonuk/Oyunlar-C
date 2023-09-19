/*
Kullanýlacak Rengi Deðiþtirir
*/

#ifndef RENK_H
#define RENK_H
#include <stdio.h>

typedef enum {
    Siyah = 30,
    Kirmizi,
    Yesil,
    Sari,
    Mavi,
    Magenta,
    Camgobegi,
    Beyaz,
    Sifirla = 0
} renk;

void RenkDegistir(renk Renk) {
    printf("\033[1;%dm", Renk);
}

#endif
