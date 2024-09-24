#include <iostream>

using namespace std;

const int MAX_PEMAIN = 100;
const int MAX_NAMA = 50;
const int MAX_POSISI = 30;

struct Pemain {
    char nama[MAX_NAMA];
    char posisi[MAX_POSISI];
    int nomorPunggung;
    int usia;
};

// Prototipe fungsi
void tambahPemain(Pemain* pemain, int& jumlah);
void tampilkanPemain(Pemain* pemain, int jumlah);
void updatePemain(Pemain* pemain, int jumlah);
void hapusPemain(Pemain* pemain, int& jumlah);

int main() {
    Pemain pemain[MAX_PEMAIN];  
    int jumlahPemain = 0;      
    int pilihan;

    do {
        cout << "\nMenu Manajemen Klub Bola:\n";
        cout << "1. Tambah Pemain\n";
        cout << "2. Tampilkan Pemain\n";
        cout << "3. Update Pemain\n";
        cout << "4. Hapus Pemain\n";
        cout << "5. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPemain(pemain, jumlahPemain);
                break;
            case 2:
                tampilkanPemain(pemain, jumlahPemain);
                break;
            case 3:
                updatePemain(pemain, jumlahPemain);
                break;
            case 4:
                hapusPemain(pemain, jumlahPemain);
                break;
            case 5:
                cout << "Terima kasih! Keluar dari program.\n";
                break;
            default:
                cout << "Opsi tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 5);

    return 0;
}

void tambahPemain(Pemain* pemain, int& jumlah) {
    if (jumlah < MAX_PEMAIN) {
        cout << "Masukkan Nama Pemain: ";
        cin.ignore(); 
        cin.getline(pemain[jumlah].nama, MAX_NAMA);
        cout << "Masukkan Posisi Pemain: ";
        cin.getline(pemain[jumlah].posisi, MAX_POSISI);
        cout << "Masukkan Nomor Punggung: ";
        cin >> pemain[jumlah].nomorPunggung;
        cout << "Masukkan Usia Pemain: ";
        cin >> pemain[jumlah].usia;

        jumlah++;
        cout << "Pemain berhasil ditambahkan!\n";
    } else {
        cout << "Jumlah pemain maksimum telah tercapai!\n";
    }
}

void tampilkanPemain(Pemain* pemain, int jumlah) {
    if (jumlah == 0) {
        cout << "Tidak ada pemain yang terdaftar.\n";
        return;
    }
    cout << "\nDaftar Pemain:\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "Pemain " << (i + 1) << ": " << pemain[i].nama 
             << ", Posisi: " << pemain[i].posisi 
             << ", Nomor Punggung: " << pemain[i].nomorPunggung 
             << ", Usia: " << pemain[i].usia << " tahun\n";
    }
}

void updatePemain(Pemain* pemain, int jumlah) {
    int index;
    cout << "Masukkan nomor pemain yang ingin diupdate (1-" << jumlah << "): ";
    cin >> index;
    index--; 

    if (index >= 0 && index < jumlah) {
        cout << "Masukkan Nama Pemain Baru: ";
        cin.ignore(); 
        cin.getline(pemain[index].nama, MAX_NAMA);
        cout << "Masukkan Posisi Pemain Baru: ";
        cin.getline(pemain[index].posisi, MAX_POSISI);
        cout << "Masukkan Nomor Punggung Baru: ";
        cin >> pemain[index].nomorPunggung;
        cout << "Masukkan Usia Pemain Baru: ";
        cin >> pemain[index].usia;

        cout << "Data pemain berhasil diperbarui!\n";
    } else {
        cout << "Nomor pemain tidak valid.\n";
    }
}

void hapusPemain(Pemain* pemain, int& jumlah) {
    int index;
    cout << "Masukkan nomor pemain yang ingin dihapus (1-" << jumlah << "): ";
    cin >> index;
    index--; 

    if (index >= 0 && index < jumlah) {
        for (int i = index; i < jumlah - 1; i++) {
            pemain[i] = pemain[i + 1]; 
        }
        jumlah--; 
        cout << "Data pemain berhasil dihapus!\n";
    } else {
        cout << "Nomor pemain tidak valid.\n";
    }
}
