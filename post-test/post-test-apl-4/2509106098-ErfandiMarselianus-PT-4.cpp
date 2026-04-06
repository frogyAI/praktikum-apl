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
Akun user;


void tampilkanHeader(char judul[]) {
    cout << "\n=== " << judul << " ===\n";
}

void tampilkanMenuUtama() {
    printf("\n=== MENU UTAMA ===\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Keluar\n");
    printf("Pilihan: ");
}

void tampilkanMenuKebunBinatang() {
    cout << "\n=== MENU PROGRAM KEBUN BINATANG ===" << endl;
    cout << "1. Tampilkan Semua Binatang" << endl;
    cout << "2. Tambah Binatang" << endl;
    cout << "3. Lihat Detail Binatang" << endl;
    cout << "4. Ubah Binatang" << endl;
    cout << "5. Hapus Binatang" << endl;
    cout << "6. Cari Binatang" << endl;
    cout << "7. KEMBALI KE MENU UTAMA" << endl;
    cout << "Pilihan: ";
}

void tampilkanBinatang(Binatang b, int nomor) {
    cout << "\n--- Data Binatang ke-" << nomor << " ---" << endl;
    cout << "Nama    : " << b.nama << endl;
    cout << "Jenis   : " << b.jenis << endl;
    cout << "Habitat : " << b.habitat << endl;
    cout << "Umur    : " << b.umur << " tahun" << endl;
}

void ubahUmurBinatang(Binatang &b, int umurBaru) {
    cout << "\nAlamat memori binatang: " << &b << endl;
    cout << "Umur lama: " << b.umur << " tahun" << endl;
    b.umur = umurBaru;
    cout << "Umur baru: " << b.umur << " tahun" << endl;
}

void ubahHabitatBinatang(Binatang &b, char habitatBaru[]) {
    cout << "\nAlamat memori: " << &b << endl;
    cout << "Habitat lama: " << b.habitat << endl;
    strcpy(b.habitat, habitatBaru);
    cout << "Habitat baru: " << b.habitat << endl;
}

void tambahUmurBinatangRef(Binatang &b, int tahunTambah) {
    cout << "\nMenambah umur " << tahunTambah << " tahun" << endl;
    cout << "Alamat memori: " << &b << endl;
    b.umur = b.umur + tahunTambah;
    cout << "Umur sekarang: " << b.umur << " tahun" << endl;
}

void gantiNamaBinatang(Binatang *b, char namaBaru[]) {
    cout << "\nAlamat memori yang ditunjuk: " << b << endl;
    cout << "Nama lama: " << (*b).nama << endl;
    strcpy(b->nama, namaBaru);
    cout << "Nama baru: " << b->nama << endl;
}

void gantiJenisBinatang(Binatang *b, char jenisBaru[]) {
    cout << "\nAlamat memori: " << b << endl;
    cout << "Jenis lama: " << (*b).jenis << endl;
    strcpy((*b).jenis, jenisBaru);
    cout << "Jenis baru: " << b->jenis << endl;
}

void kurangiUmurBinatang(Binatang *b, int tahunKurang) {
    cout << "\nMengurangi umur " << tahunKurang << " tahun" << endl;
    cout << "Alamat memori: " << b << endl;
    cout << "Umur lama: " << b->umur << " tahun" << endl;
    b->umur = b->umur - tahunKurang;
    cout << "Umur sekarang: " << (*b).umur << " tahun" << endl;
}

void tukarPosisiBinatang(Binatang *binatang1, Binatang *binatang2) {
    cout << "\nMenukar posisi binatang" << endl;
    cout << "Alamat binatang1: " << binatang1 << endl;
    cout << "Alamat binatang2: " << binatang2 << endl;
    
    Binatang temp = *binatang1;
    *binatang1 = *binatang2;
    *binatang2 = temp;
    
    cout << "Posisi berhasil ditukar!" << endl;
}

void hitungRataRataUmur(Binatang *arr, int jumlah, float *hasil) {
    int total = 0;
    for(int i = 0; i < jumlah; i++) {
        total += (arr + i)->umur;
    }
    *hasil = (float)total / jumlah;
    cout << "\nRata-rata umur: " << *hasil << " tahun" << endl;
}

void registrasi(Akun *user) {
    tampilkanHeader("REGISTRASI");
    printf("Masukkan Nama: ");
    scanf("%s", (*user).nama);
    printf("Masukkan Password: ");
    scanf("%s", (*user).passnim);
    printf("\nRegistrasi Berhasil!\n");
}

void login(Akun user, char loginNama[], char loginPassnim[], int &kesempatan, bool &berhasil) {
    if(strcmp(loginNama, user.nama) == 0 && strcmp(loginPassnim, user.passnim) == 0) {
        printf("\nLogin Berhasil!\n");
        berhasil = true;
    } else {
        kesempatan--;
        printf("Login Gagal! Sisa kesempatan: %d\n", kesempatan);
        if(kesempatan > 0) {
            printf("Silakan coba lagi.\n");
        }
        berhasil = false;
    }
}

void tampilkanSemuaBinatang(Binatang kebunBinatang[], int banyak) {
    if(banyak == 0) {
        cout << "\nBelum ada data binatang." << endl;
        return;
    }
    
    tampilkanHeader("DAFTAR SEMUA BINATANG");
    cout << "Total: " << banyak << " binatang" << endl;
    for(int i = 0; i < banyak; i++) {
        cout << i+1 << ". " << kebunBinatang[i].nama 
             << " (" << kebunBinatang[i].jenis << ")" << endl;
    }
}

void tambahBinatang(Binatang kebunBinatang[], int *banyak) {
    if(*banyak < MAX_binatang) {
        Binatang b;
        
        tampilkanHeader("TAMBAH BINATANG BARU");
        cout << "Masukkan nama binatang: ";
        cin >> b.nama;
        
        cout << "Masukkan jenis (Karnivora/Herbivora/Omnivora): ";
        cin >> b.jenis;
        
        cout << "Masukkan habitat (Darat/Air/Udara): ";
        cin >> b.habitat;
        
        cout << "Masukkan umur (tahun): ";
        cin >> b.umur;
        
        kebunBinatang[*banyak] = b;  
        (*banyak)++;
        
        cout << "\nBinatang berhasil ditambahkan!" << endl;
        tampilkanBinatang(b, *banyak);
    } else {
        cout << "\nData binatang sudah penuh!" << endl;
    }
}

void lihatDetailBinatang(Binatang kebunBinatang[], int banyak) {
    if(banyak > 0) {
        int index;
        tampilkanHeader("LIHAT DETAIL BINATANG");
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
}

void ubahBinatang(Binatang kebunBinatang[], int banyak) {
    if(banyak > 0) {
        int index;
        tampilkanHeader("UBAH DATA BINATANG");
        cout << "\nMasukkan nomor binatang yang akan diubah (1-" << banyak << "): ";
        cin >> index;
        
        if(index >= 1 && index <= banyak) {
            Binatang &b = kebunBinatang[index-1];
            
            cout << "\nData lama:" << endl;
            tampilkanBinatang(b, index);
            
            cout << "\nMasukkan data baru:" << endl;
            cout << "Nama binatang (" << b.nama << "): ";
            cin >> b.nama;
            
            cout << "\nJenis (" << b.jenis << "): ";
            cin >> b.jenis;
            
            cout << "\nHabitat (" << b.habitat << "): ";
            cin >> b.habitat;
            
            cout << "\nUmur (" << b.umur << " tahun): ";
            cin >> b.umur;
            
            cout << "\nData binatang berhasil diubah!" << endl;
            tampilkanBinatang(b, index);
        } else {
            cout << "\nNomor tidak valid!" << endl;
        }
    } else {
        cout << "\nTidak ada data binatang untuk diubah." << endl;
    }
}

void hapusBinatang(Binatang kebunBinatang[], int *banyak) {
    if(*banyak > 0) {
        int index;
        tampilkanHeader("HAPUS BINATANG");
        cout << "Masukkan nomor binatang yang akan dihapus (1-" << *banyak << "): ";
        cin >> index;
        
        if(index >= 1 && index <= *banyak) {
            cout << "\nData yang akan dihapus:" << endl;
            tampilkanBinatang(kebunBinatang[index-1], index);
            
            char konfirmasi;
            cout << "\nYakin ingin menghapus? (y/n): ";
            cin >> konfirmasi;
            
            if(konfirmasi == 'y' || konfirmasi == 'Y') {
                for(int i = index-1; i < *banyak-1; i++) {
                    kebunBinatang[i] = kebunBinatang[i+1];
                }
                (*banyak)--;
                cout << "\nBinatang berhasil dihapus!" << endl;
            } else {
                cout << "\nPenghapusan dibatalkan." << endl;
            }
        } else {
            cout << "Nomor tidak valid!" << endl;
        }
    } else {
        cout << "\nTidak ada data binatang untuk dihapus." << endl;
    }
}

void cariBinatang(Binatang kebunBinatang[], int banyak) {
    if(banyak > 0) {
        tampilkanHeader("CARI BINATANG");
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
}

bool cekRegistrasi(Akun user) {
    return strlen(user.nama) > 0;
}

int jalankanMenuKebunBinatang() {
    int pilihan;
    tampilkanMenuKebunBinatang();
    cin >> pilihan;
    return pilihan;
}

int main() {
    char loginNama[50];
    char loginPassnim[50];
    int kesempatan = 3;
    int menuUtama;
    bool loginBerhasil = false;
    
    user.nama[0] = '\0';
    user.passnim[0] = '\0';

    do {
        tampilkanMenuUtama();
        scanf("%d", &menuUtama);
        
        switch(menuUtama) {
            case 1:
                registrasi(&user);
                break;
                
            case 2:
                if(!cekRegistrasi(user)) {
                    printf("\nAnda belum melakukan registrasi! Silakan registrasi terlebih dahulu.\n");
                    break;
                }
                
                kesempatan = 3;
                loginBerhasil = false;
                
                while (kesempatan > 0 && !loginBerhasil) {
                    tampilkanHeader("LOGIN");
                    printf("Nama: ");
                    scanf("%s", loginNama);
                    printf("Password: ");
                    scanf("%s", loginPassnim);

                    login(user, loginNama, loginPassnim, kesempatan, loginBerhasil);
                }
                
                if(kesempatan == 0) {
                    printf("\nAnda gagal login 3 kali. Akses ditolak.\n");
                }
                
                if(loginBerhasil) {
                    int pilihan;
                    do {
                        pilihan = jalankanMenuKebunBinatang();
                        
                        switch(pilihan) {
                            case 1:
                                tampilkanSemuaBinatang(kebunBinatang, banyak);
                                break;
                                
                            case 2:
                                tambahBinatang(kebunBinatang, &banyak);
                                break;
                                
                            case 3:
                                lihatDetailBinatang(kebunBinatang, banyak);
                                break;
                                
                            case 4:
                                ubahBinatang(kebunBinatang, banyak);
                                break;
                                
                            case 5:
                                hapusBinatang(kebunBinatang, &banyak);
                                break;
                                
                            case 6:
                                cariBinatang(kebunBinatang, banyak);
                                break;
                                
                            case 7:
                                cout << "\nKembali ke Menu Utama..." << endl;
                                break;
                                
                            default:
                                cout << "\nPilihan tidak valid!" << endl;
                        }
                    } while(pilihan != 7);
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