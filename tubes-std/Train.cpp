#include "Train.h"

void tambahVertex(map<string, Vertex>& vertices, const string& nama) {
    if (vertices.find(nama) == vertices.end()) {
        vertices[nama] = {nama, {}};
    }
}

void tambahEdge(map<string, Vertex>& vertices, const string& asal, const string& tujuan, int jarak) {
    tambahVertex(vertices, asal);
    tambahVertex(vertices, tujuan);

    vertices[asal].koneksi.push_back({tujuan, jarak});
    vertices[tujuan].koneksi.push_back({asal, jarak}); // Graf tidak berarah
}

void tampilkanSemuaRute(map<string, Vertex>& vertices) {
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        string nama = it->first;
        Vertex& vertex = it->second;

        cout << nama << " -> ";
        bool first = true;
        for (auto edgeIt = vertex.koneksi.begin(); edgeIt != vertex.koneksi.end(); ++edgeIt) {
            if (!first) cout << ", ";
            cout << "(" << edgeIt->tujuan << ", " << edgeIt->jarak << ")";
            first = false;
        }
        cout << "\n";
    }
}

void cariRuteTercepat(const map<string, Vertex>& vertices, const string& asal, const string& tujuan) {
    map<string, int> jarak;
    map<string, string> sebelumnya;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> antrian;

    for (map<string, Vertex>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
        jarak[it->first] = numeric_limits<int>::max();
    }
    jarak[asal] = 0;
    antrian.push(make_pair(0, asal));

    while (!antrian.empty()) {
        pair<int, string> top = antrian.top();
        int jarakSaatIni = top.first;
        string sekarang = top.second;
        antrian.pop();

        if (jarakSaatIni > jarak[sekarang]) continue;

        for (int i = 0; i < vertices.at(sekarang).koneksi.size(); ++i) {
            const Edge& edge = vertices.at(sekarang).koneksi[i];
            int jarakBaru = jarakSaatIni + edge.jarak;
            if (jarakBaru < jarak[edge.tujuan]) {
                jarak[edge.tujuan] = jarakBaru;
                sebelumnya[edge.tujuan] = sekarang;
                antrian.push(make_pair(jarakBaru, edge.tujuan));
            }
        }
    }

    if (jarak[tujuan] == numeric_limits<int>::max()) {
        cout << "Tidak ada rute dari " << asal << " ke " << tujuan << "\n";
        return;
    }

    cout << "Rute tercepat dari " << asal << " ke " << tujuan << " dengan jarak " << jarak[tujuan] << ":\n";
    vector<string> rute;
    for (string stasiun = tujuan; !stasiun.empty(); stasiun = sebelumnya[stasiun]) {
        rute.push_back(stasiun);
    }
    reverse(rute.begin(), rute.end());

    for (int i = 0; i < rute.size(); ++i) {
        cout << rute[i];
        if (i != rute.size() - 1) cout << " -> ";
    }
    cout << "\n";
}

void tambahStasiun(map<string, Vertex>& vertices, const string& nama, const vector<pair<string, int>>& koneksi) {
    tambahVertex(vertices, nama);
    for (int i = 0; i < koneksi.size(); ++i) {
        const string& tujuan = koneksi[i].first;
        int jarak = koneksi[i].second;
        tambahEdge(vertices, nama, tujuan, jarak);
    }
    cout << "Stasiun " << nama << " berhasil ditambahkan.\n";
}

void hapusStasiun(map<string, Vertex>& vertices, const string& nama) {
    if (vertices.find(nama) == vertices.end()) {
        cout << "Stasiun " << nama << " tidak ditemukan.\n";
        return;
    }

    vertices.erase(nama);

    for (map<string, Vertex>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        Vertex& vertex = it->second;
        vertex.koneksi.erase(
            remove_if(vertex.koneksi.begin(), vertex.koneksi.end(),
                      [&nama](const Edge& edge) { return edge.tujuan == nama; }),
            vertex.koneksi.end());
    }

    cout << "Stasiun " << nama << " berhasil dihapus.\n";
}

void cariSemuaRute(const map<string, Vertex>& vertices, const string& asal, const string& tujuan, vector<string>& ruteSaatIni, vector<vector<string>>& semuaRute, map<string, bool>& visited) {
    visited[asal] = true;
    ruteSaatIni.push_back(asal);

    if (asal == tujuan) {
        semuaRute.push_back(ruteSaatIni);
    } else {
        for (int i = 0; i < vertices.at(asal).koneksi.size(); ++i) {
            const Edge& edge = vertices.at(asal).koneksi[i];
            if (!visited[edge.tujuan]) {
                cariSemuaRute(vertices, edge.tujuan, tujuan, ruteSaatIni, semuaRute, visited);
            }
        }
    }

    ruteSaatIni.pop_back();
    visited[asal] = false;
}

void tampilkanSemuaRuteAlternatif(const map<string, Vertex>& vertices, const string& asal, const string& tujuan) {
    vector<string> ruteSaatIni;
    vector<vector<string>> semuaRute;
    map<string, bool> visited;

    for (map<string, Vertex>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
        visited[it->first] = false;
    }

    cariSemuaRute(vertices, asal, tujuan, ruteSaatIni, semuaRute, visited);

    if (semuaRute.empty()) {
        cout << "Tidak ada rute dari " << asal << " ke " << tujuan << "\n";
    } else {
        cout << "Semua rute alternatif dari " << asal << " ke " << tujuan << ":\n";
        for (int i = 0; i < semuaRute.size(); ++i) {
            const vector<string>& rute = semuaRute[i];
            int jarakTotal = 0;

            for (int j = 0; j < rute.size(); ++j) {
                if (j != 0) {
                    const string& sebelumnya = rute[j - 1];
                    const string& sekarang = rute[j];

                    // Cari jarak antara dua simpul
                    for (const Edge& edge : vertices.at(sebelumnya).koneksi) {
                        if (edge.tujuan == sekarang) {
                            jarakTotal += edge.jarak;
                            break;
                        }
                    }
                }

                cout << rute[j];
                if (j != rute.size() - 1) cout << " -> ";
            }
            cout << " dengan jarak " << jarakTotal << "\n";
        }
    }
}
