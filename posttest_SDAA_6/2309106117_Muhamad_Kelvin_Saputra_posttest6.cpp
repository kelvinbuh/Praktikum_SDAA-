#include <iostream>
#include <cstring>
#include <cmath> 

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

void mergeSort(Pemain arr[], int left, int right);
void quickSort(Pemain arr[], int low, int high);

int fibonacciSearch(Pemain arr[], int n, int x);
int jumpSearch(Pemain arr[], int n, int x);
int boyerMooreSearch(char text[], char pattern[]);

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

void merge(Pemain arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Pemain L[MAX_PEMAIN], R[MAX_PEMAIN];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].nomorPunggung <= R[j].nomorPunggung) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Pemain arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int partition(Pemain arr[], int low, int high) {
    int pivot = arr[high].nomorPunggung;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].nomorPunggung > pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(Pemain arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Fibonacci Search untuk data integer (nomor punggung)
int fibonacciSearch(Pemain arr[], int n, int x) {
    int fibMMm2 = 0; // (m-2)'th Fibonacci No.
    int fibMMm1 = 1; // (m-1)'th Fibonacci No.
    int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (arr[i].nomorPunggung < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (arr[i].nomorPunggung > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else return i;
    }

    if (fibMMm1 && arr[offset + 1].nomorPunggung == x) return offset + 1;

    return -1;
}

// Jump Search untuk data integer (nomor punggung)
int jumpSearch(Pemain arr[], int n, int x) {
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1].nomorPunggung < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    while (arr[prev].nomorPunggung < x) {
        prev++;
        if (prev == min(step, n))
            return -1;
    }

    if (arr[prev].nomorPunggung == x)
        return prev;

    return -1;
}

// Boyer-Moore Search untuk data string (nama)
void badCharHeuristic(char* str, int size, int badchar[256]) {
    for (int i = 0; i < 256; i++)
        badchar[i] = -1;
    for (int i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

int boyerMooreSearch(char text[], char pattern[]) {
    int m = strlen(pattern);
    int n = strlen(text);

    int badchar[256];
    badCharHeuristic(pattern, m, badchar);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            return s;
        } else {
            s += max(1, j - badchar[(int)text[s + j]]);
        }
    }

    return -1;
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
        cout << "4. Urutkan Pemain (Merge Sort Ascending)\n";
        cout << "5. Urutkan Pemain (Quick Sort Descending)\n";
        cout << "6. Cari Pemain (Fibonacci Search Nomor Punggung)\n";
        cout << "7. Cari Pemain (Jump Search Nomor Punggung)\n";
        cout << "8. Cari Pemain (Boyer-Moore Search Nama)\n";
        cout << "9. Keluar\n";
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
                mergeSort(queue.pemain, queue.front, queue.rear - 1);
                cout << "Pemain telah diurutkan secara ascending (Merge Sort).\n";
                tampilkanPemain(queue);
                break;
            case 5:
                quickSort(queue.pemain, queue.front, queue.rear - 1);
                cout << "Pemain telah diurutkan secara descending (Quick Sort).\n";
                tampilkanPemain(queue);
                break;
            case 6: {
                int nomor;
                cout << "Masukkan Nomor Punggung yang ingin dicari: ";
                cin >> nomor;
                int idx = fibonacciSearch(queue.pemain, queue.rear - queue.front, nomor);
                if (idx != -1) {
                    cout << "Pemain ditemukan pada indeks: " << idx << "\n";
                } else {
                    cout << "Pemain tidak ditemukan.\n";
                }
                break;
            }
            case 7: {
                int nomor;
                cout << "Masukkan Nomor Punggung yang ingin dicari: ";
                cin >> nomor;
                int idx = jumpSearch(queue.pemain, queue.rear - queue.front, nomor);
                if (idx != -1) {
                    cout << "Pemain ditemukan pada indeks: " << idx << "\n";
                } else {
                    cout << "Pemain tidak ditemukan.\n";
                }
                break;
            }
           case 8: {
                char nama[MAX_NAMA];
                cout << "Masukkan Nama Pemain yang ingin dicari: ";
                cin.ignore();
                cin.getline(nama, MAX_NAMA);

                bool found = false;
                for (int i = queue.front; i < queue.rear; i++) {
                    int idx = boyerMooreSearch(queue.pemain[i].nama, nama);
                    if (idx != -1) {
                        cout << "Pemain ditemukan pada indeks: " << i << " (Nama: " << queue.pemain[i].nama << ")\n";
                        found = true;
                        break; 
                    }
                }

                if (!found) {
                    cout << "Pemain tidak ditemukan.\n";
                }
                break;
                }


            case 9:
                cout << "Terima kasih! Keluar dari program.\n";
                break;
            default:
                cout << "Opsi tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 9);

    return 0;
}




