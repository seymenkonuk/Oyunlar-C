/*
Tetris Oyunu
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "../lib/imlec.h" // https://github.com/seymenkonuk/Imlec-Kontrol-C
#include "../lib/rastgele.h" // https://github.com/seymenkonuk/Rastgele-C
#include "../lib/renk.h" // https://github.com/seymenkonuk/Yazi-Rengi-C

int oynaTetrisOyunu(int genislik, int yukseklik);

int oynaTetrisOyunu(int genislik, int yukseklik) {
    int hiz = 60; int puan = 0;
    void skorDegistir(int artis) {
        puan += artis;
        // Ekranda G�ster
        gotoxy((genislik+2)*2+2+6,14);
        RenkDegistir(Sifirla);
        printf("%d", puan);
        gotoxy(0, yukseklik+2);
    }
    
    // Tahtay� Olu�turma
    RenkDegistir(Sifirla);
    system("cls"); int i, j;
    for (i=0; i<genislik+2; i++) printf("%c%c", 219, 219);
    for (i=0; i<yukseklik+1; i++) printf("\n%c%c", 219, 219);
    for (i=0; i<genislik+1; i++) printf("%c%c", 219, 219);
    for (i=1; i<yukseklik+1; i++) { gotoxy((genislik+1)*2, i); printf("%c%c", 219, 219);}
    
    // Bloklar[blok_ismi][yon][parca][x,y]
    int blokSayisi = 7;
    int bloklar[7][4][4][2] = {
        {   {{-1,0}, {0,0}, {1,0}, {2,0}},    // �izgi 0 Kere Sola D�nm��
            {{0,-1}, {0,0}, {0,1}, {0,2}},    // �izgi 1 Kere Sola D�nm��
            {{-1,0}, {0,0}, {1,0}, {2,0}},    // �izgi 2 Kere Sola D�nm��
            {{0,-1}, {0,0}, {0,1}, {0,2}}},   // �izgi 3 Kere Sola D�nm��
            
        {   {{0,0}, {1,0}, {0,1}, {1,1}},     // Kare 0 Kere Sola D�nm��
            {{0,0}, {1,0}, {0,1}, {1,1}},     // Kare 1 Kere Sola D�nm��
            {{0,0}, {1,0}, {0,1}, {1,1}},     // Kare 2 Kere Sola D�nm��
            {{0,0}, {1,0}, {0,1}, {1,1}}},    // Kare 3 Kere Sola D�nm��
            
        {   {{-1,0}, {0,0}, {1,0}, {0,1}},    // T 0 Kere Sola D�nm��
            {{0,-1}, {0,0}, {1,0}, {0,1}},    // T 1 Kere Sola D�nm��
            {{0,0}, {-1,1}, {0,1}, {1,1}},    // T 2 Kere Sola D�nm��
            {{1,-1}, {0,0}, {1,0}, {1,1}}},   // T 3 Kere Sola D�nm��
            
        {   {{-1,0}, {0,0}, {1,0}, {1,1}},    // L 0 Kere Sola D�nm��
            {{0,-1}, {1,-1}, {0,0}, {0,1}},   // L 1 Kere Sola D�nm��
            {{-1,0}, {-1,1}, {0,1}, {1,1}},   // L 2 Kere Sola D�nm��
            {{0,-1}, {0,0}, {-1,1}, {0,1}}},  // L 3 Kere Sola D�nm��
            
        {   {{-1,0}, {0,0}, {1,0}, {-1,1}},   // Ters L 0 Kere Sola D�nm��
            {{0,-1}, {0,0}, {0,1}, {1,1}},    // Ters L 1 Kere Sola D�nm��
            {{1,-1}, {-1,0}, {0,0}, {1,0}},   // Ters L 2 Kere Sola D�nm��
            {{-1,-1}, {0,-1}, {0,0}, {0,1}}}, // Ters L 3 Kere Sola D�nm��
            
        {   {{0,0}, {1,0}, {-1,1}, {0,1}},    // S 0 Kere Sola D�nm��
            {{-1,-1}, {-1,0}, {0,0}, {0,1}},  // S 1 Kere Sola D�nm��
            {{0,0}, {1,0}, {-1,1}, {0,1}},    // S 2 Kere Sola D�nm��
            {{-1,-1}, {-1,0}, {0,0}, {0,1}}},  // S 3 Kere Sola D�nm��
            
        {   {{-1,0}, {0,0}, {0,1}, {1,1}},    // Z 0 Kere Sola D�nm��
            {{0,-1}, {-1,0}, {0,0}, {-1,1}},  // Z 1 Kere Sola D�nm��
            {{-1,0}, {0,0}, {0,1}, {1,1}},    // Z 2 Kere Sola D�nm��
            {{0,-1}, {-1,0}, {0,0}, {-1,1}}},  // Z 3 Kere Sola D�nm��
    };
    
    // Tahta Dizisini Olu�turma
    int tahta[yukseklik+2][genislik+2];
    for (i=0; i<yukseklik+2; i++) 
        for (j=0; j<genislik+2; j++)
            if (j==0 || i==yukseklik+1 || j==genislik+1)
                tahta[i][j] = 1;
            else
                tahta[i][j] = 0;
    
    // Gerekli De�i�kenler
    int yedekBlok = -1; bool degistirilebilirMi=true; // HOLD
    int gelecekBlok[3]; for (i=0; i<3; i++) gelecekBlok[i] = rastgeleAralik(0, blokSayisi-1);
    int yeniBlok, merkezx, merkezy, yon;
    int yercekimi, yercekimiHiz = 15, maxYercekimiHiz = 3; int hizlanma = 0;
    
    // Yaz�lar� Yazma
    gotoxy((genislik+2)*2+2, 0);
    printf("Yedek");
    gotoxy((genislik+2)*2+2, 4);
    printf("Siradakiler");
    // Puan� G�ster
    gotoxy((genislik+2)*2+2,14);
    printf("Puan: ");
    skorDegistir(0);
    
    // Oyun Mekanikleri
    while (1) {
        merkezx = genislik/2+genislik%2; merkezy = -1; yon = 0; yercekimi = 0;
        // Yeni Blok �ret
        yeniBlok = gelecekBlok[0];
        for (i=0; i<3-1; i++) gelecekBlok[i] = gelecekBlok[i+1];
        gelecekBlok[2] = rastgeleAralik(0, blokSayisi-1);
        
        // S�radaki Bloklar� Ekranda G�ster
        for (i=0; i<3; i++) {
            // Temizle
            gotoxy((genislik+2)*2+2, 5+3*i);
            printf("        ");
            gotoxy((genislik+2)*2+2, 6+3*i);
            printf("        ");
            
            // Bloklar� �iz
            RenkDegistir(Siyah + gelecekBlok[i]);
            for (j=0; j<4; j++) {
                gotoxy((genislik+2)*2+4 + bloklar[gelecekBlok[i]][0][j][0]*2, 5+3*i + bloklar[gelecekBlok[i]][0][j][1]);
                printf("%c%c", 219, 219);
            }
        }
        
        // Blo�u D���r
        while (1) {
            gotoxy(0, yukseklik+2);
            sleep(1000/hiz);
            yercekimi++;
            // Hareketler
            bool yedeklendiMi = false; // C Tu�una Bas�ld� M�
            bool boslukBasildiMi = false;
            int kx=0, ky=0, kyon=0, depo=0;
            if (kbhit()) {
                char tus = getch();
                if (tus=='s' || tus=='S') {
                    ky=1;
                    skorDegistir(1);
                } else if (tus=='a' || tus=='A') {
                    kx=-1;
                } else if (tus=='d' || tus=='D') {
                    kx=1;
                } else if (tus=='q' || tus=='Q') {
                    kyon=-1;
                } else if (tus=='e' || tus=='E') {
                    kyon=1;
                } else if ((tus=='c' || tus=='C') && degistirilebilirMi) {
                    degistirilebilirMi = false;
                    depo = yedekBlok;
                    yedekBlok = yeniBlok;
                    yedeklendiMi = true;
                    
                    // Yedek Blo�un Oldu�u Yeri Temizle
                    gotoxy((genislik+2)*2+2, 1);
                    printf("        ");
                    gotoxy((genislik+2)*2+2, 2);
                    printf("        ");
                    // Yedek Blo�u Ekranda G�ster
                    RenkDegistir(Siyah + yedekBlok);
                    for (i=0; i<4; i++) {
                        gotoxy((genislik+2)*2+4 + bloklar[yedekBlok][0][i][0]*2, 1 + bloklar[yedekBlok][0][i][1]);
                        printf("%c%c", 219, 219);
                    }
                } else if (tus==32) { // Bo�luk Tu�u, En A�a�� G�nder
                    ky = 1;
                    boslukBasildiMi = true;
                }
            }
            
            // Eskisini Sil
            for (i=0; i<4; i++) {
                int parca_y = merkezy+bloklar[yeniBlok][yon][i][1];
                int parca_x = merkezx+bloklar[yeniBlok][yon][i][0];
                if (parca_y<=0) continue;
                gotoxy(parca_x*2, parca_y); printf("  ");
            }
            gotoxy(0, yukseklik+2);
            
            if (yedeklendiMi && depo == -1) break;
            else if (yedeklendiMi){
                yeniBlok = depo;
                merkezx = genislik/2+genislik%2; merkezy = -1; yon = 0; yercekimi = 0;
                continue;
            }
            
            do {
                // Hareket Yap�labilir Mi
                merkezx += kx; merkezy += ky; yon = (yon + kyon+4) % 4;
                for (i=0; i<4; i++) {
                    int parca_y = merkezy+bloklar[yeniBlok][yon][i][1];
                    int parca_x = merkezx+bloklar[yeniBlok][yon][i][0];
                    if (parca_x<=0) break; if (parca_x>=genislik+1) break;
                    if (parca_y<=0) continue;
                    if (tahta[parca_y][parca_x] != 0) break;
                }
                if (i<4) { // Yap�lamazsa Geri Getir
                    merkezx -= kx; merkezy -= ky; yon = (yon - kyon+4)%4;
                    break;
                }
                if (boslukBasildiMi) skorDegistir(2);
            } while (boslukBasildiMi);
            
            // Yenisini G�ster
            RenkDegistir(Siyah + yeniBlok);
            for (i=0; i<4; i++) {
                int parca_y = merkezy+bloklar[yeniBlok][yon][i][1];
                int parca_x = merkezx+bloklar[yeniBlok][yon][i][0];
                if (parca_y<=0) continue;
                gotoxy(parca_x*2, parca_y); printf("%c%c", 219, 219);
                continue;
            }
            gotoxy(0, yukseklik+2);
            
            // A�A�I D��T�YSE YEN�S�N� GET�R
            // D��me Bitti Mi
            bool dustuMu = false;
            for (i=0; i<4; i++) {
                int parca_y = merkezy+bloklar[yeniBlok][yon][i][1];
                int parca_x = merkezx+bloklar[yeniBlok][yon][i][0];
                if (1+parca_y < 0) continue;
                if (tahta[1+parca_y][parca_x] != 0) {
                    dustuMu = true;
                    degistirilebilirMi = true;
                    // D��en Blok, Alan�n �st�nde, Oyun Bitti
                    if (parca_y <= 0) {
                        RenkDegistir(Sifirla);
                        return puan;
                    }
                }
            }
            if (dustuMu) {
                // Tahtay� G�ncelle
                for (i=0; i<4; i++) {
                    int parca_y = merkezy+bloklar[yeniBlok][yon][i][1];
                    int parca_x = merkezx+bloklar[yeniBlok][yon][i][0];
                    tahta[parca_y][parca_x] = yeniBlok + 1;
                }
                
                // SATIR DOLDUYSA SATIRI S�L
                int depoTahta[yukseklik+2][genislik+2]; for (i=0; i<yukseklik+2; i++) for (j=0; j<genislik+2; j++) depoTahta[i][j] = tahta[i][j];
                int kacSatirDolu = 0;
                for (i=1; i<=yukseklik; i++) {
                    for (j=1; j<=genislik; j++) if (tahta[i][j] == 0) break;
                    if (j<=genislik) continue; // Sat�r dolu de�ilse
                    kacSatirDolu++;
                    if (i==1) {
                        for (j=1; j<=genislik; j++) tahta[i][j] = 0;
                        continue;
                    }
                    int k; for (k=i-1; k>=1; k--) {
                        for (j=1; j<=genislik; j++) {
                            tahta[k+1][j] = tahta[k][j];
                        }
                    }
                    
                }
                if (kacSatirDolu == 1) skorDegistir(100);
                if (kacSatirDolu == 2) skorDegistir(300);
                if (kacSatirDolu == 3) skorDegistir(500);
                if (kacSatirDolu == 4) skorDegistir(800);
                
                // De�i�iklikleri G�rsel Olarak G�ster
                for (i=1; i<=yukseklik; i++)
                    for (j=1; j<=genislik; j++)
                        if (tahta[i][j]!=0 && depoTahta[i][j]!=tahta[i][j]) {
                            RenkDegistir(Siyah + tahta[i][j]-1);
                            gotoxy(j*2, i);
                            printf("%c%c", 219, 219);
                        } else if (tahta[i][j]==0 && depoTahta[i][j]!=0) {
                            gotoxy(j*2, i);
                            printf("  ");
                        }
                
                // Oyun H�zlans�n
                hizlanma++;
                if (hizlanma == 5) {
                    hizlanma = 0;
                    if (yercekimiHiz > maxYercekimiHiz) yercekimiHiz--;
                }
                break;
            }
            
            
            // Bir Birim A�a�� Kayd�r (YER�EK�M�)
            if (yercekimi >= yercekimiHiz) {
                yercekimi = 0;
                
                // D��me Bitti Mi
                bool dustuMu = false;
                for (i=0; i<4; i++) {
                    int parca_y = merkezy+bloklar[yeniBlok][yon][i][1];
                    int parca_x = merkezx+bloklar[yeniBlok][yon][i][0];
                    if (1+parca_y < 0) continue;
                    if (tahta[1+parca_y][parca_x] == 1) {
                        dustuMu = true;
                        degistirilebilirMi = true;
                        if (parca_y <= 0) {
                            RenkDegistir(Sifirla);
                            return puan;
                        }
                    }
                }
                if (!dustuMu) {
                    // Eskisini Sil
                    for (i=0; i<4; i++) {
                        int parca_y = merkezy+bloklar[yeniBlok][yon][i][1];
                        int parca_x = merkezx+bloklar[yeniBlok][yon][i][0];
                        if (parca_y<=0) continue;
                        gotoxy(parca_x*2, parca_y); printf("  ");
                    }
                    gotoxy(0, yukseklik+2);
                    
                    merkezy++; 
                    // Yenisini G�ster
                    for (i=0; i<4; i++) {
                        int parca_y = merkezy+bloklar[yeniBlok][yon][i][1];
                        int parca_x = merkezx+bloklar[yeniBlok][yon][i][0];
                        if (parca_y<=0) continue;
                        gotoxy(parca_x*2, parca_y); printf("%c%c", 219, 219);
                        continue;
                    }
                    gotoxy(0, yukseklik+2);
                    
                }
            }
            
        }
    }
}
