#include "Train.h"

void TrainGraph::addStation(string station) {
    graph[station] = {};
}

void TrainGraph::addEdge(string from, string to, int distance) {
    graph[from].push_back(make_pair(to, distance));
    graph[to].push_back(make_pair(from, distance));
}

void TrainGraph::displayRoute(string start, string end) {
    queue<string> q;
    map<string, string> prev;
    q.push(start);
    prev[start] = "";

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        if (current == end) {
            // Rekonstruksi rute
            string route = end;
            while (prev[current] != "") {
                route = prev[current] + " -> " + route;
                current = prev[current];
            }
            cout << "Rute: " << route << endl;
            return;
        }

        for (auto neighbor : graph[current]) {
            // Hanya tambahkan tetangga yang melalui Manggarai
            if ((current == "Jakarta" && neighbor.first == "Depok") ||
                (current == "Jakarta" && (neighbor.first == "Bekasi" || neighbor.first == "Bogor"))) {
                if (neighbor.first == "Manggarai") {
                    q.push(neighbor.first);
                    prev[neighbor.first] = current;
                }
            } else if (prev.count(neighbor.first) == 0) {
                q.push(neighbor.first);
                prev[neighbor.first] = current;
            }
        }
    }

    cout << "Tidak ditemukan rute dari " << start << " ke " << end << endl;
}
