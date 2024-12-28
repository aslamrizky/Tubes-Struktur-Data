#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <string>
#include <vector>
#include <algorithm>

#define namaStasiun(s) s->namaStasiun
#define stasiunSetelah(s) s->stasiunSetelah
#define edgeStasiunPertama(s) s->edgeStasiunPertama
#define destNamaStasiun(e) e->destNamaStasiun
#define jarak(e) e->jarak
#define edgeStasiunSetelah(e) e->edgeStasiunSetelah
#define stasiunPertama(G) G.stasiunPertama

#include <iostream>
using namespace std;

typedef struct stasiun *adrStasiun;
typedef struct edgeStasiun *adrEdgeStasiun;

struct stasiun {
    string namaStasiun;
    adrStasiun stasiunSetelah;
    adrEdgeStasiun edgeStasiunPertama;
};

struct edgeStasiun {
    string destNamaStasiun;
    int jarak;
    adrEdgeStasiun edgeStasiunSetelah;
};

struct graph {
    adrStasiun stasiunPertama;
};

void tambahStasiunBaru(string stasiunBaru, adrStasiun &s);
void initStasiun(graph &G);
void tambahStasiun(graph &G, string stasiunBaru);
void tampilkanRute(graph &G);
adrStasiun cariStasiun(graph &G, string stasiunDiCari);
void tambahEdgeStasiun(graph &G, string stasiunSumber, string destNamaStasiun, int jarak);
bool cariJalurDFS(graph &G, string sumber, string tujuan, vector<string> &path, int &totalJarak, vector<string> &bestPath, int &minNodes);
void jalurTercepat(graph &G, vector<string> &bestPath, int &minNodes);
void hapusStasiun(graph &G, string stasiunDiHapus);

#endif // GRAPH_H_INCLUDED
