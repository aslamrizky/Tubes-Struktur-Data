#include "graph.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    graph G;
    initStasiun(G);

    int pilihan;
    string stasiunBaru, stasiunSumber, stasiunTujuan, stasiunHapus;
    int jarak;

    vector<string> path;
    vector<string> bestPath;
    int totalJarak;
    int minNodes;

    tambahStasiun(G, "Jakarta");
    tambahStasiun(G, "Tanjung Priok");
    tambahStasiun(G, "Manggarai");
    tambahStasiun(G, "Bekasi");
    tambahStasiun(G, "Depok");
    tambahStasiun(G, "Bogor");

    tambahEdgeStasiun(G, "Jakarta", "Tanjung Priok", 10);
    tambahEdgeStasiun(G, "Jakarta", "Manggarai", 35);
    tambahEdgeStasiun(G, "Manggarai", "Bekasi", 30);
    tambahEdgeStasiun(G, "Manggarai", "Depok", 55);
    tambahEdgeStasiun(G, "Depok", "Bogor", 15);
    tambahEdgeStasiun(G, "Manggarai", "Bogor", 70);

    do {
        cout << "\n---------- Menu ----------" << endl;
        cout << "1. Tampilkan Rute Stasiun" << endl;
        cout << "2. Cari Jalur Tercepat" << endl;
        cout << "3. Tambah Stasiun dan Rute" << endl;
        cout << "4. Hapus Stasiun" << endl;
        cout << "0. Keluar" << endl;
        cout << "--------------------------" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch(pilihan) {
            case 1:
                tampilkanRute(G);
                break;
            case 2:
                cout << "Masukkan nama stasiun sumber: ";
                getline(cin, stasiunSumber);
                cout << "Masukkan nama stasiun tujuan: ";
                getline(cin, stasiunTujuan);
                cout << endl;

                totalJarak = 0;
                bestPath.clear();
                minNodes = INT_MAX;

                if (cariJalurDFS(G, stasiunSumber, stasiunTujuan, path, totalJarak, bestPath, minNodes)) {
                    jalurTercepat(G, bestPath, minNodes);
                } else {
                cout << "Jalur tidak ditemukan!" << endl;
                }
                break;
            case 3:
                cout << "Masukkan nama stasiun baru: ";
                getline(cin, stasiunBaru);
                tambahStasiun(G, stasiunBaru);

                cout << "Masukkan nama stasiun sumber: ";
                getline(cin, stasiunSumber);
                cout << "Masukkan jarak: ";
                cin >> jarak;
                cin.ignore();

                tambahEdgeStasiun(G, stasiunSumber, stasiunBaru, jarak);
                break;
            case 4:
                cout << "Pilih stasiun yang ingin dihapus: ";
                getline(cin, stasiunHapus);
                hapusStasiun(G, stasiunHapus);
                break;
            case 0:
                cout << "Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi." << endl;
        }
    } while (pilihan != 0);

    return 0;
}
