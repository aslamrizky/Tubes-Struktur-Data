#include "Train.h"

int main() {
    map<string, Vertex> kereta;

    // Tambahkan rute awal dari diagram
    tambahEdge(kereta, "Tanjung_Priok", "Jakarta", 2);
    tambahEdge(kereta, "Jakarta", "Manggarai", 7);
    tambahEdge(kereta, "Manggarai", "Depok", 11);
    tambahEdge(kereta, "Manggarai", "Bekasi", 6);
    tambahEdge(kereta, "Manggarai", "Bogor", 14);
    tambahEdge(kereta, "Depok", "Bogor", 3);

    int pilihan;
    do {
        cout << "\nMenu:\n";
        cout << "1. Tampilkan Semua Rute\n";
        cout << "2. Cari Rute Tercepat\n";
        cout << "3. Tambah Stasiun Baru\n";
        cout << "4. Hapus Stasiun\n";
        cout << "5. Tampilkan Semua Rute Alternatif\n";
        cout << "6. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            tampilkanSemuaRute(kereta);
        } else if (pilihan == 2) {
            string asal, tujuan;
            cout << "Masukkan stasiun asal: ";
            cin >> asal;
            cout << "Masukkan stasiun tujuan: ";
            cin >> tujuan;
            cariRuteTercepat(kereta, asal, tujuan);
        } else if (pilihan == 3) {
            string nama;
            int jumlah;
            cout << "Masukkan nama stasiun baru: ";
            cin >> nama;
            cout << "Masukkan jumlah koneksi: ";
            cin >> jumlah;

            vector<pair<string, int>> koneksi;
            for (int i = 0; i < jumlah; ++i) {
                string tujuan;
                int jarak;
                cout << "Masukkan stasiun tujuan dan jarak: ";
                cin >> tujuan >> jarak;
                koneksi.push_back({tujuan, jarak});
            }
            tambahStasiun(kereta, nama, koneksi);
        } else if (pilihan == 4) {
            string nama;
            cout << "Masukkan nama stasiun yang ingin dihapus: ";
            cin >> nama;
            hapusStasiun(kereta, nama);
        } else if (pilihan == 5) {
            string asal, tujuan;
            cout << "Masukkan stasiun asal: ";
            cin >> asal;
            cout << "Masukkan stasiun tujuan: ";
            cin >> tujuan;
            tampilkanSemuaRuteAlternatif(kereta, asal, tujuan);
        }
    } while (pilihan != 6);

    return 0;
}
