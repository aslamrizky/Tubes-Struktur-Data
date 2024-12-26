#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

// Struktur untuk Edge (koneksi antar stasiun)
struct Edge {
    string tujuan;
    int jarak;
};

// Struktur untuk Vertex (stasiun)
struct Vertex {
    string nama;
    vector<Edge> koneksi;
};

void tambahVertex(map<string, Vertex>& vertices, const string& nama);
void tambahEdge(map<string, Vertex>& vertices, const string& asal, const string& tujuan, int jarak);
void tampilkanSemuaRute(map<string, Vertex>& vertices);
void cariRuteTercepat(const map<string, Vertex>& vertices, const string& asal, const string& tujuan);
void tambahStasiun(map<string, Vertex>& vertices, const string& nama, const vector<pair<string, int>>& koneksi);
void hapusStasiun(map<string, Vertex>& vertices, const string& nama);
void cariSemuaRute(const map<string, Vertex>& vertices, const string& asal, const string& tujuan, vector<string>& ruteSaatIni, vector<vector<string>>& semuaRute, map<string, bool>& visited);
void tampilkanSemuaRuteAlternatif(const map<string, Vertex>& vertices, const string& asal, const string& tujuan);

#endif // GRAPH_H
