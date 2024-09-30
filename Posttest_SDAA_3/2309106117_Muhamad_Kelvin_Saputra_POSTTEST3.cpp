#include <iostream>

using namespace std;

const int MAX_NAMA = 50;
const int MAX_POSISI = 30;

struct Pemain {
    char nama[MAX_NAMA];
    char posisi[MAX_POSISI];
    int nomorPunggung;
    int usia;
    Pemain* next; 
};

void tambahPemain(Pemain*& head);
void tampilkanPemain(Pemain* head);
void updatePemain(Pemain* head);
void hapusPemain(Pemain*& head);

int main() {
    Pemain* head = nullptr; 
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
                tambahPemain(head);
                break;
            case 2:
                tampilkanPemain(head);
                break;
            case 3:
                updatePemain(head);
                break;
            case 4:
                hapusPemain(head);
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

void tambahPemain(Pemain*& head) {
    Pemain* pemainBaru = new Pemain;

    cout << "Masukkan Nama Pemain: ";
    cin.ignore(); 
    cin.getline(pemainBaru->nama, MAX_NAMA);
    cout << "Masukkan Posisi Pemain: ";
    cin.getline(pemainBaru->posisi, MAX_POSISI);
    cout << "Masukkan Nomor Punggung: ";
    cin >> pemainBaru->nomorPunggung;
    cout << "Masukkan Usia Pemain: ";
    cin >> pemainBaru->usia;

    pemainBaru->next = nullptr;

    if (head == nullptr) {
        head = pemainBaru; 
    } else {
        Pemain* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next; 
        }
        temp->next = pemainBaru; 
    }

    cout << "Pemain berhasil ditambahkan!\n";
}

void tampilkanPemain(Pemain* head) {
    if (head == nullptr) {
        cout << "Tidak ada pemain yang terdaftar.\n";
        return;
    }

    Pemain* temp = head;
    int i = 1;
    cout << "\nDaftar Pemain:\n";
    while (temp != nullptr) {
        cout << "Pemain " << i << ": " << temp->nama 
             << ", Posisi: " << temp->posisi 
             << ", Nomor Punggung: " << temp->nomorPunggung 
             << ", Usia: " << temp->usia << " tahun\n";
        temp = temp->next;
        i++;
    }
}

void updatePemain(Pemain* head) {
    if (head == nullptr) {
        cout << "Tidak ada pemain yang terdaftar.\n";
        return;
    }

    int nomor;
    cout << "Masukkan nomor pemain yang ingin diupdate: ";
    cin >> nomor;

    Pemain* temp = head;
    int i = 1;
    while (temp != nullptr && i < nomor) {
        temp = temp->next;
        i++;
    }

    if (temp == nullptr) {
        cout << "Pemain tidak ditemukan.\n";
    } else {
        cout << "Masukkan Nama Pemain Baru: ";
        cin.ignore(); 
        cin.getline(temp->nama, MAX_NAMA);
        cout << "Masukkan Posisi Pemain Baru: ";
        cin.getline(temp->posisi, MAX_POSISI);
        cout << "Masukkan Nomor Punggung Baru: ";
        cin >> temp->nomorPunggung;
        cout << "Masukkan Usia Pemain Baru: ";
        cin >> temp->usia;

        cout << "Data pemain berhasil diperbarui!\n";
    }
}

void hapusPemain(Pemain*& head) {
    if (head == nullptr) {
        cout << "Tidak ada pemain yang terdaftar.\n";
        return;
    }

    int nomor;
    cout << "Masukkan nomor pemain yang ingin dihapus: ";
    cin >> nomor;

    if (nomor == 1) {
        Pemain* temp = head;
        head = head->next;
        delete temp;
        cout << "Data pemain berhasil dihapus!\n";
    } else {
        Pemain* temp = head;
        Pemain* prev = nullptr;
        int i = 1;

        while (temp != nullptr && i < nomor) {
            prev = temp;
            temp = temp->next;
            i++;
        }

        if (temp == nullptr) {
            cout << "Pemain tidak ditemukan.\n";
        } else {
            prev->next = temp->next;
            delete temp;
            cout << "Data pemain berhasil dihapus!\n";
        }
    }
}

