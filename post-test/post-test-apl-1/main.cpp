#include <stdio.h>
#include "auth.h"
#include "menu.h"

int main() {
    if (login()) {  // Jika login berhasil
        printf("\nLogin berhasil!\n");
        tampilkanMenu();  // Panggil fungsi menu (tanpa 'int')
    } else {
        printf("Akses ditolak! Program berhenti.\n");
    }
    return 0;
}
