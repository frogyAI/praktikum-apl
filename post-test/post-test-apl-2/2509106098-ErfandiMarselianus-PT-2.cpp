#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

struct Akun {
    char nama[50];
    char passnim[50];
};
struct Binatang {
    char nama[50];
    char jenis[50];
    char habitat[50];
    int umur;
};

#define MAX_binatang 100
int banyak = 0;
Binatang kebunBinatang[MAX_binatang];  

void tampilkanBinatang(Binatang b, int nomor) {
    cout << "\n--- Data Binatang ke-" << nomor << " ---" << endl;
    cout << "Nama    : " << b.nama << endl;
    cout << "Jenis   : " << b.jenis << endl;
    cout << "Habitat : " << b.habitat << endl;
    cout << "Umur    : " << b.umur << " tahun" << endl;
}

int main() {
    struct Akun user;
    char loginNama[50];
    char loginPassnim[50];
    int kesempatan = 3;
    int menuUtama;
    
    // Inisialisasi user kosong
    user.nama[0] = '\0';
    user.passnim[0] = '\0';

    do {
        printf("\n=== MENU UTAMA ===\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &menuUtama);
        
        switch(menuUtama) {
            case 1:
                printf("\n=== REGISTRASI ===\n");
                printf("Masukkan Nama: ");
                scanf("%s", user.nama);
                printf("Masukkan Password: ");
                scanf("%s", user.passnim);
                printf("\nRegistrasi Berhasil!\n");
                break;
                
            case 2:
                if(strlen(user.nama) == 0) {
                    printf("\nAnda belum melakukan registrasi! Silakan registrasi terlebih dahulu.\n");
                    break;
                }
                
                kesempatan = 3;
                while (kesempatan > 0) {
                    printf("\n=== LOGIN ===\n");
                    printf("Nama: ");
                    scanf("%s", loginNama);
                    printf("Password: ");
                    scanf("%s", loginPassnim);

                    if(strcmp(loginNama, user.nama) == 0 && strcmp(loginPassnim, user.passnim) == 0) {
                        printf("\nLogin Berhasil!\n");
                        
                        // Menu Kebun Binatang (struktur asli Anda)
                        int pilihan, index;
                        do {
                            cout << "\n=== MENU PROGRAM KEBUN BINATANG ===" << endl;
                            cout << "1. Tampilkan Semua Binatang" << endl;
                            cout << "2. Tambah Binatang" << endl;
                            cout << "3. Lihat Detail Binatang" << endl;
                            cout << "4. Ubah Binatang" << endl;
                            cout << "5. Hapus Binatang" << endl;
                            cout << "6. Cari Binatang" << endl;
                            cout << "7. KEMBALI KE MENU UTAMA" << endl;
                            cout << "Pilihan: ";
                            cin >> pilihan;
                            
                            switch(pilihan) {
                                case 1:
                                    if(banyak == 0) {
                                        cout << "\nBelum ada data binatang." << endl;
                                    } else {
                                        cout << "\n=== DAFTAR SEMUA BINATANG ===" << endl;
                                        cout << "Total: " << banyak << " binatang" << endl;
                                        for(int i = 0; i < banyak; i++) {
                                            cout << i+1 << ". " << kebunBinatang[i].nama 
                                                 << " (" << kebunBinatang[i].jenis << ")" << endl;
                                        }
                                    }
                                    break;
                                    
                                case 2: { 
                                    if(banyak < MAX_binatang) {
                                        Binatang b;
                                        
                                        cout << "\n=== TAMBAH BINATANG BARU ===" << endl;
                                        cout << "Masukkan nama binatang: ";
                                        cin >> b.nama;
                                        
                                        cout << "Masukkan jenis (Karnivora/Herbivora/Omnivora): ";
                                        cin >> b.jenis;
                                        
                                        cout << "Masukkan habitat (Darat/Air/Udara): ";
                                        cin >> b.habitat;
                                        
                                        cout << "Masukkan umur (tahun): ";
                                        cin >> b.umur;
                                        
                                        kebunBinatang[banyak] = b;  
                                        banyak++;
                                        
                                        cout << "\nBinatang berhasil ditambahkan!" << endl;
                                        tampilkanBinatang(b, banyak);
                                    } else {
                                        cout << "\nData binatang sudah penuh!" << endl;
                                    }
                                    break;
                                }
                                    
                                case 3: 
                                    if(banyak > 0) {
                                        cout << "\n=== LIHAT DETAIL BINATANG ===" << endl;
                                        cout << "Masukkan nomor binatang (1-" << banyak << "): ";
                                        cin >> index;
                                        
                                        if(index >= 1 && index <= banyak) {
                                            tampilkanBinatang(kebunBinatang[index-1], index);
                                        } else {
                                            cout << "Nomor tidak valid!" << endl;
                                        }
                                    } else {
                                        cout << "\nTidak ada data binatang." << endl;
                                    }
                                    break;
                                    
                                case 4:
                                    if(banyak > 0) {
                                        cout << "\n=== UBAH DATA BINATANG ===" << endl;
                                        cout << "Masukkan nomor binatang yang akan diubah (1-" << banyak << "): ";
                                        cin >> index;
                                        
                                        if(index >= 1 && index <= banyak) {
                                            Binatang &b = kebunBinatang[index-1];  
                                            
                                            cout << "\nData lama:" << endl;
                                            tampilkanBinatang(b, index);
                                            
                                            cout << "\nMasukkan data baru:" << endl;
                                            cout << "Nama binatang (" << b.nama << "): ";
                                            cin >> b.nama;
                                            
                                            cout << "Jenis (" << b.jenis << "): ";
                                            cin >> b.jenis;
                                            
                                            cout << "Habitat (" << b.habitat << "): ";
                                            cin >> b.habitat;
                                            
                                            cout << "Umur (" << b.umur << " tahun): ";
                                            cin >> b.umur;
                                            
                                            cout << "\nData binatang berhasil diubah!" << endl;
                                            tampilkanBinatang(b, index);
                                        } else {
                                            cout << "Nomor tidak valid!" << endl;
                                        }
                                    } else {
                                        cout << "\nTidak ada data binatang untuk diubah." << endl;
                                    }
                                    break;
                                    
                                case 5: 
                                    if(banyak > 0) {
                                        cout << "\n=== HAPUS BINATANG ===" << endl;
                                        cout << "Masukkan nomor binatang yang akan dihapus (1-" << banyak << "): ";
                                        cin >> index;
                                        
                                        if(index >= 1 && index <= banyak) {
                                            
                                            cout << "\nData yang akan dihapus:" << endl;
                                            tampilkanBinatang(kebunBinatang[index-1], index);
                                            
                                            char konfirmasi;
                                            cout << "\nYakin ingin menghapus? (y/n): ";
                                            cin >> konfirmasi;
                                            
                                            if(konfirmasi == 'y' || konfirmasi == 'Y') {
                                                for(int i = index-1; i < banyak-1; i++) {
                                                    kebunBinatang[i] = kebunBinatang[i+1];
                                                }
                                                banyak--;
                                                cout << "Binatang berhasil dihapus!" << endl;
                                            } else {
                                                cout << "Penghapusan dibatalkan." << endl;
                                            }
                                        } else {
                                            cout << "Nomor tidak valid!" << endl;
                                        }
                                    } else {
                                        cout << "\nTidak ada data binatang untuk dihapus." << endl;
                                    }
                                    break;
                                    
                                case 6: { 
                                    if(banyak > 0) {
                                        cout << "\n=== CARI BINATANG ===" << endl;
                                        cout << "Pilih kriteria pencarian:" << endl;
                                        cout << "1. Cari berdasarkan nama" << endl;
                                        cout << "2. Cari berdasarkan jenis" << endl;
                                        cout << "3. Cari berdasarkan habitat" << endl;
                                        cout << "Pilihan: ";
                                        
                                        int kriteria;
                                        cin >> kriteria;
                                        
                                        char keyword[50];
                                        cout << "Masukkan kata kunci: ";
                                        cin >> keyword;
                                        
                                        cout << "\nHasil pencarian:" << endl;
                                        int ditemukan = 0;
                                        
                                        for(int i = 0; i < banyak; i++) {
                                            bool cocok = false;
                                            
                                            switch(kriteria) {
                                                case 1:
                                                    if(strstr(kebunBinatang[i].nama, keyword) != NULL)
                                                        cocok = true;
                                                    break;
                                                case 2:
                                                    if(strstr(kebunBinatang[i].jenis, keyword) != NULL)
                                                        cocok = true;
                                                    break;
                                                case 3:
                                                    if(strstr(kebunBinatang[i].habitat, keyword) != NULL)
                                                        cocok = true;
                                                    break;
                                                default:
                                                    cout << "Kriteria tidak valid!" << endl;
                                                    break;
                                            }
                                            
                                            if(cocok) {
                                                tampilkanBinatang(kebunBinatang[i], i+1);
                                                ditemukan++;
                                            }
                                        }
                                        
                                        if(ditemukan == 0) {
                                            cout << "Tidak ada binatang yang cocok dengan pencarian." << endl;
                                        } else {
                                            cout << "\nDitemukan " << ditemukan << " binatang." << endl;
                                        }
                                    } else {
                                        cout << "\nTidak ada data binatang." << endl;
                                    }
                                    break;
                                }
                                    
                                case 7: 
                                    cout << "\nKembali ke Menu Utama..." << endl;
                                    break;
                                    
                                default:
                                    cout << "\nPilihan tidak valid!" << endl;
                            }
                        } while(pilihan != 7);
                        
                        break; // Keluar dari while login
                    } else {
                        kesempatan--;
                        printf("Login Gagal! Sisa kesempatan: %d\n", kesempatan);
                        if(kesempatan > 0) {
                            printf("Silakan coba lagi.\n");
                        }
                    }
                }
                
                if(kesempatan == 0) {
                    printf("\nAnda gagal login 3 kali. Akses ditolak.\n");
                }
                break;
                
            case 3:
                printf("\nTerima kasih! Program selesai.\n");
                break;
                
            default:
                printf("\nPilihan tidak valid!\n");
        }
    } while(menuUtama != 3);
    
    return 0;
}