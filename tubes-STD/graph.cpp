#include "graph.h"
#include <string>
#include <vector>
#include <algorithm>

void tambahStasiunBaru(string stasiunBaru, adrStasiun &s) {
    s = new stasiun;
    namaStasiun(s) = stasiunBaru;
    stasiunSetelah(s) = NULL;
    edgeStasiunPertama(s) = NULL;
}

void initStasiun(graph &G) {
    stasiunPertama(G) = NULL;
}

void tambahStasiun(graph &G, string stasiunBaru) {
    adrStasiun s;
    tambahStasiunBaru(stasiunBaru, s);
    if (stasiunPertama(G) == NULL) {
        stasiunPertama(G) = s;
    } else {
        adrStasiun s2 = stasiunPertama(G);
        while (stasiunSetelah(s2) != NULL) {
            s2 = stasiunSetelah(s2);
        }
        stasiunSetelah(s2) = s;
    }
}

void tampilkanRute(graph &G) {
    cout << "Rute Stasiun" << endl;
    adrStasiun s = stasiunPertama(G);
    while (s != NULL) {
        cout << "Rute " << namaStasiun(s) << " : " << endl;
        adrEdgeStasiun e = edgeStasiunPertama(s);
        while (e != NULL) {
            cout << namaStasiun(s) << " -> " << destNamaStasiun(e) << " ( melewati " << jarak(e) << " stasiun lainnya )" << endl;
            e = edgeStasiunSetelah(e);
        }
        cout << endl;
        s = stasiunSetelah(s);
    }
}

adrStasiun cariStasiun(graph &G, string stasiunDiCari) {
    adrStasiun s = stasiunPertama(G);
    while (s != NULL) {
        if (namaStasiun(s) == stasiunDiCari) {
            return s;
        }
        s = stasiunSetelah(s);
    }
    return NULL;
}

void tambahEdgeStasiun(graph &G, string stasiunSumber, string destNamaStasiun, int jarak) {
    adrStasiun sumber = cariStasiun(G, stasiunSumber);
    adrStasiun tujuan = cariStasiun(G, destNamaStasiun);

    if (sumber == NULL || tujuan == NULL) {
        cout << "Stasiun tidak ditemukan!" << endl;
        return;
    }

    adrEdgeStasiun edge = new edgeStasiun;
    destNamaStasiun(edge) = destNamaStasiun;
    jarak(edge) = jarak;
    edgeStasiunSetelah(edge) = edgeStasiunPertama(sumber);
    edgeStasiunPertama(sumber) = edge;

    adrEdgeStasiun edgeBalik = new edgeStasiun;
    destNamaStasiun(edgeBalik) = stasiunSumber;
    jarak(edgeBalik) = jarak;
    edgeStasiunSetelah(edgeBalik) = edgeStasiunPertama(tujuan);
    edgeStasiunPertama(tujuan) = edgeBalik;

    cout << "Stasiun " << destNamaStasiun(edge) << " berhasil ditambah setelah stasiun " << stasiunSumber << endl;
}

bool cariJalurDFS(graph &G, string sumber, string tujuan, vector<string> &path, int &totalJarak, vector<string> &bestPath, int &minNodes) {
    adrStasiun stasiunSumber = cariStasiun(G, sumber);
    adrStasiun stasiunTujuan = cariStasiun(G, tujuan);

    if (stasiunSumber == NULL || stasiunTujuan == NULL) {
        return false;
    }

    path.push_back(sumber);

    if (sumber == tujuan) {

        int nodesCount = path.size();

        if (nodesCount < minNodes) {
            minNodes = nodesCount;
            bestPath = path;
        }

        cout << "Jalur: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << " (melewati " << totalJarak << " stasiun lainnya)" << endl;
        path.pop_back();
        return true;
    }

    adrEdgeStasiun e = edgeStasiunPertama(stasiunSumber);
    bool found = false;
    while (e != NULL) {
        if (find(path.begin(), path.end(), destNamaStasiun(e)) == path.end()) {
            totalJarak += jarak(e);
            if (cariJalurDFS(G, destNamaStasiun(e), tujuan, path, totalJarak, bestPath, minNodes)) {
                found = true;
            }
            totalJarak -= jarak(e);
        }
        e = edgeStasiunSetelah(e);
    }

    path.pop_back();
    return found;
}

void jalurTercepat(graph &G, vector<string> &bestPath, int &minNodes) {
    cout << "\nJalur tercepat: ";
    for (size_t i = 0; i < bestPath.size(); ++i) {
        cout << bestPath[i];
        if (i < bestPath.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}


void hapusStasiun(graph &G, string stasiunDiHapus) {
    adrStasiun s = stasiunPertama(G);
    adrStasiun prevStasiun = NULL;

    while (s != NULL && namaStasiun(s) != stasiunDiHapus) {
        prevStasiun = s;
        s = stasiunSetelah(s);
    }

    if (s == NULL) {
        cout << "Stasiun tidak ditemukan!" << endl;
        return;
    }

    adrEdgeStasiun e = edgeStasiunPertama(s);
    while (e != NULL) {
        adrEdgeStasiun temp = e;
        e = edgeStasiunSetelah(e);
        delete temp;
    }

    adrStasiun t = stasiunPertama(G);
    while (t != NULL) {
        adrEdgeStasiun prevEdge = NULL;
        e = edgeStasiunPertama(t);
        while (e != NULL) {
            if (destNamaStasiun(e) == stasiunDiHapus) {
                if (prevEdge == NULL) {
                    edgeStasiunPertama(t) = edgeStasiunSetelah(e);
                } else {
                    edgeStasiunSetelah(prevEdge) = edgeStasiunSetelah(e);
                }
                delete e;
                break;
            }
            prevEdge = e;
            e = edgeStasiunSetelah(e);
        }
        t = stasiunSetelah(t);
    }

    if (prevStasiun == NULL) {
        stasiunPertama(G) = stasiunSetelah(s);
    } else {
        stasiunSetelah(prevStasiun) = stasiunSetelah(s);
    }

    delete s;
    cout << "Stasiun " << stasiunDiHapus << " dan semua relasinya telah dihapus!" << endl;
}
