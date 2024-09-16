#include <iostream>

using namespace std;

void menaraHanoi(int n, char asal, char tujuan, char sementara) {
    if (n == 1) {
        cout << "Pindahkan piringan 1 dari menara " << asal << " ke menara " << tujuan << endl;
        return;
    }

    menaraHanoi(n - 1, asal, sementara, tujuan);

    cout << "Pindahkan piringan " << n << " dari menara " << asal << " ke menara " << tujuan << endl;

    menaraHanoi(n - 1, sementara, tujuan, asal);
}

int main() {
    int n = 3; 
    cout << "Langkah-langkah memindahkan " << n << " piringan dalam Menara Hanoi (A = asal, C = tujuan, B = sementara:)\n";
    menaraHanoi(n, 'A', 'C', 'B'); 
    return 0;
}