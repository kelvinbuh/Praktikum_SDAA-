#include <iostream>

using namespace std;

const int MAX_NAMA = 50;
const int MAX_POSISI = 30;
const int MAX_PEMAIN = 100; 

struct Pemain {
    char nama[MAX_NAMA];
    char posisi[MAX_POSISI];
    int nomorPunggung;
    int usia;
};

struct Stack {
    Pemain pemain[MAX_PEMAIN];
    int top;
};

struct Queue {
    Pemain pemain[MAX_PEMAIN];
    int front;
    int rear;
};

void initStack(Stack& stack) {
    stack.top = -1;
}

void initQueue(Queue& queue) {
    queue.front = 0;
    queue.rear = 0;
}

bool isStackFull(Stack& stack) {
    return stack.top == MAX_PEMAIN - 1;
}

bool isStackEmpty(Stack& stack) {
    return stack.top == -1;
}

void push(Stack& stack, Pemain pemainBaru) {
    if (isStackFull(stack)) {
        cout << "Stack penuh. Tidak dapat menambahkan pemain.\n";
        return;
    }
    stack.pemain[++stack.top] = pemainBaru;
    cout << "Pemain berhasil ditambahkan ke stack!\n";
}

void transferStackToQueue(Stack& stack, Queue& queue) {
    while (!isStackEmpty(stack)) {
        queue.pemain[queue.rear++] = stack.pemain[stack.top--];
    }
}

void tampilkanPemain(Queue& queue) {
    if (queue.front == queue.rear) {
        cout << "Tidak ada pemain yang terdaftar.\n";
        return;
    }

    cout << "\nDaftar Pemain:\n";
    for (int i = queue.front; i < queue.rear; i++) {
        cout << "Pemain " << i + 1 << ": " 
             << queue.pemain[i].nama << ", Posisi: " 
             << queue.pemain[i].posisi << ", Nomor Punggung: " 
             << queue.pemain[i].nomorPunggung << ", Usia: " 
             << queue.pemain[i].usia << " tahun\n";
    }
}

int main() {
    Stack stack;
    Queue queue;
    initStack(stack);
    initQueue(queue);

    int pilihan;

    do {
        cout << "\nMenu Manajemen Klub Bola:\n";
        cout << "1. Tambah Pemain\n";
        cout << "2. Tampilkan Pemain\n";
        cout << "3. Transfer Pemain dari Stack ke Queue\n";
        cout << "4. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                Pemain pemainBaru;
                cout << "Masukkan Nama Pemain: ";
                cin.ignore();
                cin.getline(pemainBaru.nama, MAX_NAMA);
                cout << "Masukkan Posisi Pemain: ";
                cin.getline(pemainBaru.posisi, MAX_POSISI);
                cout << "Masukkan Nomor Punggung: ";
                cin >> pemainBaru.nomorPunggung;
                cout << "Masukkan Usia Pemain: ";
                cin >> pemainBaru.usia;
                push(stack, pemainBaru);
                break;
            }
            case 2:
                tampilkanPemain(queue);
                break;
            case 3:
                transferStackToQueue(stack, queue);
                cout << "Pemain telah dipindahkan dari Stack ke Queue.\n";
                break;
            case 4:
                cout << "Terima kasih! Keluar dari program.\n";
                break;
            default:
                cout << "Opsi tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 4);

    return 0;
}
