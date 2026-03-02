#include <stdio.h>
#include <string.h>
#include "auth.h"

bool login () {
    char user[20]; 
    char pass[20];
    int coba = 0;
    
    while (coba < 3) {
        printf("username: ");
        scanf("%s", user);  

        printf("password: ");
        scanf("%s", pass);

        if (strcmp(user, "erfandi") == 0 && strcmp(pass, "098") == 0) {
            printf("Login berhasil!\n");
            return true;  
        }

        printf("login salah! Percobaan ke-%d\n", coba + 1);
        coba++;
    }
    
    printf("Anda telah gagal login 3 kali.\n");
    return false;
}