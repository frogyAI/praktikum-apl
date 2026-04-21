#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

struct Akun {
    char nama[50];
    char passnim[50];
};

struct Binatang {
    int kode;              
    char nama[50];
    char jenis[50];
    char habitat[50];
    int umur;
};

#define MAX_binatang 100

int banyak = 0;
int kodeTerakhir = 0;     
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
    cout << "7. Sorting Binatang" << endl;
    cout << "8. KEMBALI KE MENU UTAMA" << endl;
    cout << "Pilihan: ";
}

void tampilkanBinatang(Binatang b, int nomor) {
    cout << "\n--- Data Binatang ---" << endl;
    cout << "Kode    : " << b.kode << endl;      
    cout << "Nama    : " << b.nama << endl;
    cout << "Jenis   : " << b.jenis << endl;
    cout << "Habitat : " << b.habitat << endl;
    cout << "Umur    : " << b.umur << " tahun" << endl;
}

void tampilkanBinatangRingkas(Binatang b, int nomorUrut) {
    cout << nomorUrut << ". [Kode: " << b.kode << "] " 
         << b.nama << " (" << b.jenis << ")" << endl;
}


int CariKode(Binatang *arr, int kiri, int kanan, int targetKode) {
    if (kanan >= kiri) {
        int tengah = kiri + (kanan - kiri) / 2;
        
        if ((arr + tengah)->kode == targetKode) {
            return tengah;
        }
        
        if ((arr + tengah)->kode > targetKode) {
            return CariKode(arr, kiri, tengah - 1, targetKode);
        }
        
        return CariKode(arr, tengah + 1, kanan, targetKode);
    }
    return -1;
}

void cariBerdasarkanKode(Binatang *arr, int *n, int targetKode) {
    if (*n == 0) {
        cout << "\nBelum ada data binatang!" << endl;
        return;
    }
    
    Binatang tempArray[MAX_binatang];
    for(int i = 0; i < *n; i++) {
        tempArray[i] = *(arr + i);
    }
    
    for(int i = 0; i < *n - 1; i++) {
        for(int j = 0; j < *n - i - 1; j++) {
            if(tempArray[j].kode > tempArray[j+1].kode) {
                Binatang temp = tempArray[j];
                tempArray[j] = tempArray[j+1];
                tempArray[j+1] = temp;
            }
        }
    }
    
    int hasil = CariKode(tempArray, 0, *n - 1, targetKode);
    
    if (hasil != -1) {
        cout << "\n>>> HASIL: Kode " << targetKode << " ditemukan! <<<" << endl;
        cout << "(Menggunakan metode Binary Search" << endl;
        tampilkanBinatang(tempArray[hasil], hasil+1);
    } else {
        cout << "\n>>> HASIL: Kode " << targetKode << " TIDAK ditemukan! <<<" << endl;
        cout << "(Menggunakan metode Binary Search " << endl;
    }
}

int CariJenis(Binatang *arr, int *n, char targetJenis[]) {
    if (*n == 0) return -1;
    
    Binatang tempArray[MAX_binatang];
    for(int i = 0; i < *n; i++) {
        tempArray[i] = *(arr + i);
    }
    
    cout << "\n[Mengurutkan data berdasarkan JENIS]" << endl;
    for(int i = 0; i < *n - 1; i++) {
        for(int j = 0; j < *n - i - 1; j++) {
            if(strcmp(tempArray[j].jenis, tempArray[j+1].jenis) > 0) {
                Binatang temp = tempArray[j];
                tempArray[j] = tempArray[j+1];
                tempArray[j+1] = temp;
            }
        }
    }
    
    cout << "Data setelah diurutkan berdasarkan jenis:" << endl;
    for(int i = 0; i < *n; i++) {
        cout << "Indeks " << i << ": Jenis = " << tempArray[i].jenis 
             << ", Nama = " << tempArray[i].nama << endl;
    }
    
    int step = sqrt(*n);
    int prev = 0;
    
    cout << "\n[Proses Mencari]" << endl;
    cout << "Ukuran lompatan = " << *n << " = " << step << endl;
    cout << "Mencari jenis: '" << targetJenis << "'" << endl;
    
    int hitungLompatan = 0;
    while (prev < *n && strcmp(tempArray[min(step, *n) - 1].jenis, targetJenis) < 0) {
        prev = step;
        step += sqrt(*n);
        hitungLompatan++;
        cout << "Lompatan ke-" << hitungLompatan << ": prev = " << prev << ", step = " << step << endl;
        if (prev >= *n) {
            cout << "Melewati batas array, tidak ditemukan dalam blok" << endl;
            return -1;
        }
    }
    
    cout << "\nMelakukan Linear Search dalam blok [" << prev << " ... " << min(step, *n) << "]" << endl;
    int hitungLinear = 0;
    while (prev < min(step, *n)) {
        hitungLinear++;
        cout << "  Memeriksa indeks " << prev << ": " << tempArray[prev].jenis;
        if (strcmp(tempArray[prev].jenis, targetJenis) == 0) {
            cout << " -> COCOK" << endl;
            cout << "\n>>> Ditemukan pada indeks ke-" << prev << "! <<<" << endl;
            cout << "(Menggunakan metode Jump Search)" << endl;
            cout << "Jumlah lompatan: " << hitungLompatan << ", Linear check: " << hitungLinear << endl;
            return prev;
        }
        cout << " -> TIDAK COCOK" << endl;
        prev++;
    }
    
    return -1;
}

void cariBerdasarkanJenis(Binatang *arr, int *n, char targetJenis[]) {
    if (*n == 0) {
        cout << "\nBelum ada data binatang!" << endl;
        return;
    }
    
    int hasil = CariJenis(arr, n, targetJenis);
    
    if (hasil != -1) {
        cout << "\n=== SEMUA BINATANG DENGAN JENIS '" << targetJenis << "' ===" << endl;
        
        Binatang tempArray[MAX_binatang];
        for(int i = 0; i < *n; i++) {
            tempArray[i] = *(arr + i);
        }
        
        for(int i = 0; i < *n - 1; i++) {
            for(int j = 0; j < *n - i - 1; j++) {
                if(strcmp(tempArray[j].jenis, tempArray[j+1].jenis) > 0) {
                    Binatang temp = tempArray[j];
                    tempArray[j] = tempArray[j+1];
                    tempArray[j+1] = temp;
                }
            }
        }
        
        int ditemukan = 0;
        for(int i = 0; i < *n; i++) {
            if(strcmp(tempArray[i].jenis, targetJenis) == 0) {
                tampilkanBinatang(tempArray[i], i+1);
                ditemukan++;
            }
        }
        cout << "\nTotal ditemukan: " << ditemukan << " binatang" << endl;
    } else {
        cout << "\n>>> HASIL: Jenis '" << targetJenis << "' TIDAK ditemukan! <<<" << endl;
        cout << "(Menggunakan metode Jump Search - O(√n))" << endl;
    }
}


int CariHabitat(Binatang *arr, int *n, char targetHabitat[]) {
    if (*n == 0) return -1;
    
    Binatang tempArray[MAX_binatang];
    for(int i = 0; i < *n; i++) {
        tempArray[i] = *(arr + i);
    }
    
    cout << "\n[Mengurutkan hewan berdasarkan HABITAT]" << endl;
    for(int i = 0; i < *n - 1; i++) {
        for(int j = 0; j < *n - i - 1; j++) {
            if(strcmp(tempArray[j].habitat, tempArray[j+1].habitat) > 0) {
                Binatang temp = tempArray[j];
                tempArray[j] = tempArray[j+1];
                tempArray[j+1] = temp;
            }
        }
    }
    
    cout << "Data setelah diurutkan berdasarkan habitat:" << endl;
    for(int i = 0; i < *n; i++) {
        cout << "Indeks " << i << ": Habitat = " << tempArray[i].habitat 
             << ", Nama = " << tempArray[i].nama << endl;
    }
    
    int low = 0;
    int high = *n - 1;
    int pos;
    int hitungTebakan = 0;
    
    cout << "\n[Proses]" << endl;
    cout << "Mencari habitat: '" << targetHabitat << "'" << endl;
    
    int targetValue = 0;
    for(int i = 0; targetHabitat[i] != '\0'; i++) {
        targetValue += targetHabitat[i];
    }
    
    while (low <= high) {
        int lowValue = 0, highValue = 0;
        for(int i = 0; tempArray[low].habitat[i] != '\0'; i++) lowValue += tempArray[low].habitat[i];
        for(int i = 0; tempArray[high].habitat[i] != '\0'; i++) highValue += tempArray[high].habitat[i];
        
        if (lowValue == highValue) {
            if (targetValue == lowValue) pos = low;
            else break;
        } else {
            pos = low + ((targetValue - lowValue) * (high - low) / (highValue - lowValue));
        }
        
        hitungTebakan++;
        cout << "Tebakan ke-" << hitungTebakan << ": pos = " << pos;
        
        if (pos < 0 || pos > high) {
            cout << " (di luar batas)" << endl;
            break;
        }
        
        cout << ", Habitat = " << tempArray[pos].habitat << endl;
        
        if (strcmp(tempArray[pos].habitat, targetHabitat) == 0) {
            cout << "\n>>> Ditemukan pada indeks ke-" << pos << "! <<<" << endl;
            cout << "(Menggunakan metode Interpolation Search " << endl;
            cout << "Jumlah tebakan: " << hitungTebakan << endl;
            return pos;
        }
        
        if (strcmp(tempArray[pos].habitat, targetHabitat) < 0) {
            cout << "  -> Terlalu kecil, cari di kanan" << endl;
            low = pos + 1;
        } else {
            cout << "  -> Terlalu besar, cari di kiri" << endl;
            high = pos - 1;
        }
    }
    
    return -1;
}

void cariBerdasarkanHabitat(Binatang *arr, int *n, char targetHabitat[]) {
    if (*n == 0) {
        cout << "\nBelum ada data binatang!" << endl;
        return;
    }
    
    int hasil = CariHabitat(arr, n, targetHabitat);
    
    if (hasil != -1) {
        cout << "\n=== SEMUA BINATANG DENGAN HABITAT '" << targetHabitat << "' ===" << endl;
        
        Binatang tempArray[MAX_binatang];
        for(int i = 0; i < *n; i++) {
            tempArray[i] = *(arr + i);
        }
        
        for(int i = 0; i < *n - 1; i++) {
            for(int j = 0; j < *n - i - 1; j++) {
                if(strcmp(tempArray[j].habitat, tempArray[j+1].habitat) > 0) {
                    Binatang temp = tempArray[j];
                    tempArray[j] = tempArray[j+1];
                    tempArray[j+1] = temp;
                }
            }
        }
        
        int ditemukan = 0;
        for(int i = 0; i < *n; i++) {
            if(strcmp(tempArray[i].habitat, targetHabitat) == 0) {
                tampilkanBinatang(tempArray[i], i+1);
                ditemukan++;
            }
        }
        cout << "\nTotal ditemukan: " << ditemukan << " binatang" << endl;
    } else {
        cout << "\n>>> HASIL: Habitat '" << targetHabitat << "' TIDAK ditemukan! <<<" << endl;
        cout << "(Menggunakan metode Interpolation Search - O(log log n))" << endl;
    }
}

void cariBerdasarkanNama(Binatang *arr, int *n, char keyword[]) {
    if (*n == 0) {
        cout << "\nBelum ada data binatang!" << endl;
        return;
    }
    
    cout << "\n[Proses mencari]" << endl;
    int ditemukan = 0;
    
    for(int i = 0; i < *n; i++) {
        if(strstr((arr + i)->nama, keyword) != NULL) {
            if(ditemukan == 0) {
                cout << "\n>>> HASIL PENCARIAN <<<" << endl;
            }
            tampilkanBinatang(*(arr + i), i+1);
            ditemukan++;
        }
    }
    
    if(ditemukan == 0) {
        cout << "\nTidak ada binatang dengan nama yang mengandung '" << keyword << "'" << endl;
    } else {
        cout << "\nDitemukan " << ditemukan << " binatang." << endl;
    }
}

void cariBinatang(Binatang kebunBinatang[], int banyak) {
    if(banyak > 0) {
        tampilkanHeader("CARI BINATANG");
        cout << "Pilih kriteria pencarian:" << endl;
        cout << "1. Cari berdasarkan kode " << endl;
        cout << "2. Cari berdasarkan nama " << endl;
        cout << "3. Cari berdasarkan jenis " << endl;
        cout << "4. Cari berdasarkan habitat " << endl;
        cout << "Pilihan: ";
        
        int kriteria;
        cin >> kriteria;
        
        switch(kriteria) {
            case 1: {
                int kodeCari;
                cout << "Masukkan kode hewan: ";
                cin >> kodeCari;
                cariBerdasarkanKode(kebunBinatang, &banyak, kodeCari);
                break;
            }
            case 2: {
                char keyword[50];
                cout << "Masukkan nama binatang: ";
                cin >> keyword;
                cariBerdasarkanNama(kebunBinatang, &banyak, keyword);
                break;
            }
            case 3: {
                char keyword[50];
                cout << "Masukkan jenis binatang (Karnivora/Herbivora/Omnivora): ";
                cin >> keyword;
                cariBerdasarkanJenis(kebunBinatang, &banyak, keyword);
                break;
            }
            case 4: {
                char keyword[50];
                cout << "Masukkan habitat (Darat/Air/Udara): ";
                cin >> keyword;
                cariBerdasarkanHabitat(kebunBinatang, &banyak, keyword);
                break;
            }
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } else {
        cout << "\nTidak ada data binatang." << endl;
    }
}

void SortNama(Binatang arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(strcmp(arr[j].nama, arr[j+1].nama) < 0) {
                Binatang temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    cout << "\n=== SORTING NAMA SELESAI ===" << endl;
}

void SortUmur(Binatang arr[], int n) {
    for(int i = 1; i < n; i++) {
        Binatang key = arr[i];
        int j = i - 1;
        
        while(j >= 0 && arr[j].umur > key.umur) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    cout << "\n=== SORTING UMUR SELESAI ===" << endl;
}

void SortHabitat(Binatang arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        int indeksMin = i;
        
        for(int j = i + 1; j < n; j++) {
            if(strcmp(arr[j].habitat, arr[indeksMin].habitat) < 0) {
                indeksMin = j;
            }
        }
        
        if(indeksMin != i) {
            Binatang temp = arr[i];
            arr[i] = arr[indeksMin];
            arr[indeksMin] = temp;
        }
    }
    cout << "\n=== SORTING HABITAT SELESAI ===" << endl;
}

void SortKode(Binatang arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j].kode > arr[j+1].kode) {
                Binatang temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    cout << "\n=== SORTING KODE SELESAI ===" << endl;
}

void menuSorting() {
    if(banyak == 0) {
        cout << "\nBelum ada data binatang untuk di-sort!" << endl;
        return;
    }
    
    int pilihanSort;
    cout << "\n=== MENU SORTING BINATANG ===" << endl;
    cout << "1. Kode (Ascending)" << endl;      
    cout << "2. Nama (Z-A)" << endl;
    cout << "3. Umur (Termuda ke Tertua)" << endl;
    cout << "4. Habitat (A-Z)" << endl;
    cout << "5. Kembali" << endl;
    cout << "Pilihan: ";
    cin >> pilihanSort;
    
    Binatang tempArray[MAX_binatang];
    for(int i = 0; i < banyak; i++) {
        tempArray[i] = kebunBinatang[i];
    }
    
    switch(pilihanSort) {
        case 1:
            SortKode(tempArray, banyak);
            cout << "\n=== HASIL SORTING/PENGURUTAN ===" << endl;
            for(int i = 0; i < banyak; i++) {
                tampilkanBinatang(tempArray[i], i+1);
            }
            
            char simpan;
            cout << "\nSimpan hasil sorting ke data utama? (y/n): ";
            cin >> simpan;
            if(simpan == 'y' || simpan == 'Y') {
                for(int i = 0; i < banyak; i++) {
                    kebunBinatang[i] = tempArray[i];
                }
                cout << "Data berhasil disimpan!" << endl;
            }
            break;
            
        case 2:
            SortNama(tempArray, banyak);
            cout << "\n=== HASIL SORTING/PENGURUTAN ===" << endl;
            for(int i = 0; i < banyak; i++) {
                tampilkanBinatang(tempArray[i], i+1);
            }
            
            cout << "\nSimpan hasil sorting ke data utama? (y/n): ";
            cin >> simpan;
            if(simpan == 'y' || simpan == 'Y') {
                for(int i = 0; i < banyak; i++) {
                    kebunBinatang[i] = tempArray[i];
                }
                cout << "Data berhasil disimpan!" << endl;
            }
            break;
            
        case 3:
            SortUmur(tempArray, banyak);
            cout << "\n=== HASIL SORTING/PENGURUTAN ===" << endl;
            for(int i = 0; i < banyak; i++) {
                tampilkanBinatang(tempArray[i], i+1);
            }
            
            cout << "\nSimpan hasil sorting ke data utama? (y/n): ";
            cin >> simpan;
            if(simpan == 'y' || simpan == 'Y') {
                for(int i = 0; i < banyak; i++) {
                    kebunBinatang[i] = tempArray[i];
                }
                cout << "Data berhasil disimpan!" << endl;
            }
            break;
            
        case 4:
            SortHabitat(tempArray, banyak);
            cout << "\n=== HASIL SORTING/PENGURUTAN ===" << endl;
            for(int i = 0; i < banyak; i++) {
                tampilkanBinatang(tempArray[i], i+1);
            }
            
            cout << "\nSimpan hasil sorting ke data utama? (y/n): ";
            cin >> simpan;
            if(simpan == 'y' || simpan == 'Y') {
                for(int i = 0; i < banyak; i++) {
                    kebunBinatang[i] = tempArray[i];
                }
                cout << "Data berhasil disimpan!" << endl;
            }
            break;
            
        case 5:
            cout << "Kembali ke menu utama..." << endl;
            break;
            
        default:
            cout << "Pilihan tidak valid!" << endl;
    }
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
        tampilkanBinatangRingkas(kebunBinatang[i], i+1);
    }
}

void tambahBinatang(Binatang kebunBinatang[], int *banyak) {
    if(*banyak < MAX_binatang) {
        Binatang b;
        
        tampilkanHeader("TAMBAH BINATANG BARU");
        
        kodeTerakhir++;
        b.kode = kodeTerakhir;
        cout << "Kode hewan : " << b.kode << endl;
        
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
        cout << "Kode hewan: " << b.kode << endl;
        tampilkanBinatang(b, *banyak);
    } else {
        cout << "\nData binatang sudah penuh!" << endl;
    }
}

void lihatDetailBinatang(Binatang kebunBinatang[], int banyak) {
    if(banyak > 0) {
        int pilihan;
        cout << "\n=== LIHAT DETAIL BINATANG ===" << endl;
        cout << "1. Cari berdasarkan nomor urut" << endl;
        cout << "2. Cari berdasarkan kode hewan" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        if(pilihan == 1) {
            int index;
            cout << "Masukkan nomor urut (1-" << banyak << "): ";
            cin >> index;
            
            if(index >= 1 && index <= banyak) {
                tampilkanBinatang(kebunBinatang[index-1], index);
            } else {
                cout << "Nomor tidak valid!" << endl;
            }
        } 
        else if(pilihan == 2) {
            int kodeCari;
            cout << "Masukkan kode hewan: ";
            cin >> kodeCari;
            
            bool ditemukan = false;
            for(int i = 0; i < banyak; i++) {
                if(kebunBinatang[i].kode == kodeCari) {
                    tampilkanBinatang(kebunBinatang[i], i+1);
                    ditemukan = true;
                    break;
                }
            }
            
            if(!ditemukan) {
                cout << "Hewan dengan kode " << kodeCari << " tidak ditemukan!" << endl;
            }
        }
        else {
            cout << "Pilihan tidak valid!" << endl;
        }
    } else {
        cout << "\nTidak ada data binatang." << endl;
    }
}

void ubahBinatang(Binatang kebunBinatang[], int banyak) {
    if(banyak > 0) {
        int pilihan;
        cout << "\n=== UBAH DATA BINATANG ===" << endl;
        cout << "1. Ubah berdasarkan nomor urut" << endl;
        cout << "2. Ubah berdasarkan kode hewan" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        int index = -1;
        
        if(pilihan == 1) {
            int nomor;
            cout << "Masukkan nomor urut (1-" << banyak << "): ";
            cin >> nomor;
            
            if(nomor >= 1 && nomor <= banyak) {
                index = nomor - 1;
            }
        }
        else if(pilihan == 2) {
            int kodeCari;
            cout << "Masukkan kode hewan: ";
            cin >> kodeCari;
            
            for(int i = 0; i < banyak; i++) {
                if(kebunBinatang[i].kode == kodeCari) {
                    index = i;
                    break;
                }
            }
            
            if(index == -1) {
                cout << "Hewan dengan kode " << kodeCari << " tidak ditemukan!" << endl;
            }
        }
        else {
            cout << "Pilihan tidak valid!" << endl;
            return;
        }
        
        if(index != -1) {
            Binatang &b = kebunBinatang[index];
            
            cout << "\nData lama:" << endl;
            tampilkanBinatang(b, index+1);
            
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
            tampilkanBinatang(b, index+1);
        }
    } else {
        cout << "\nTidak ada data binatang untuk diubah." << endl;
    }
}

void hapusBinatang(Binatang kebunBinatang[], int *banyak) {
    if(*banyak > 0) {
        int pilihan;
        cout << "\n=== HAPUS BINATANG ===" << endl;
        cout << "1. Hapus berdasarkan nomor urut" << endl;
        cout << "2. Hapus berdasarkan kode hewan" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        int index = -1;
        
        if(pilihan == 1) {
            int nomor;
            cout << "Masukkan nomor urut (1-" << *banyak << "): ";
            cin >> nomor;
            
            if(nomor >= 1 && nomor <= *banyak) {
                index = nomor - 1;
            }
        }
        else if(pilihan == 2) {
            int kodeCari;
            cout << "Masukkan kode hewan: ";
            cin >> kodeCari;
            
            for(int i = 0; i < *banyak; i++) {
                if(kebunBinatang[i].kode == kodeCari) {
                    index = i;
                    break;
                }
            }
            
            if(index == -1) {
                cout << "Hewan dengan kode " << kodeCari << " tidak ditemukan!" << endl;
            }
        }
        else {
            cout << "Pilihan tidak valid!" << endl;
            return;
        }
        
        if(index != -1) {
            cout << "\nData yang akan dihapus:" << endl;
            tampilkanBinatang(kebunBinatang[index], index+1);
            
            char konfirmasi;
            cout << "\nYakin ingin menghapus? (y/n): ";
            cin >> konfirmasi;
            
            if(konfirmasi == 'y' || konfirmasi == 'Y') {
                for(int i = index; i < *banyak-1; i++) {
                    kebunBinatang[i] = kebunBinatang[i+1];
                }
                (*banyak)--;
                cout << "\nBinatang berhasil dihapus!" << endl;
            } else {
                cout << "\nPenghapusan dibatalkan." << endl;
            }
        }
    } else {
        cout << "\nTidak ada data binatang untuk dihapus." << endl;
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
                                menuSorting();
                                break;
                                
                            case 8:
                                cout << "\nKembali ke Menu Utama..." << endl;
                                break;
                                
                            default:
                                cout << "\nPilihan tidak valid!" << endl;
                        }
                    } while(pilihan != 8);
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