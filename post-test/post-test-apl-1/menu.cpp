#include <stdio.h>
#include "menu.h"

void tampilkanMenu() { 
    int pilihan;
    int jam, menit, detik, sisa;
    
    do {
        printf("\n=== MENU KONVERSI WAKTU ===\n");
        printf("1. Jam ke Menit & Detik\n");
        printf("2. Menit ke Jam & Detik\n");
        printf("3. Detik ke Jam & Menit\n");
        printf("4. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        
        if(pilihan == 1) {
            printf("Masukan jam: ");
            scanf("%d", &jam);
            
            printf("\nHasil konversi:\n");
            printf("Menit: %d\n", jam * 60);
            printf("Detik: %d\n", jam * 3600);
        }
        else if(pilihan == 2) {
            printf("Masukan menit: ");
            scanf("%d", &menit);
            
            printf("\nHasil konversi:\n");
            printf("Jam  : %d\n", menit / 60);
            printf("Detik: %d\n", menit * 60);
        }
        else if(pilihan == 3) {
            printf("Masukan detik: ");
            scanf("%d", &detik);
            
            jam = detik / 3600;
            sisa = detik % 3600;
            menit = sisa / 60;
            detik = sisa % 60;
            
            printf("\nHasil konversi:\n");
            printf("%d Jam, %d Menit, %d Detik\n", jam, menit, detik);
        }
        else if(pilihan == 4) {
            printf("\nTerima kasih! Program selesai.\n");
        }
        else {
            printf("\nPilihan tidak valid! Silakan coba lagi.\n");
        }
        
        printf("\n");  
        
    } while(pilihan != 4);
}