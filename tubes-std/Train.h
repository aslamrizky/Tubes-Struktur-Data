#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class TrainGraph {
public:
    void addStation(string station);
    void addEdge(string from, string to, int distance);
    void displayRoute(string start, string end);

private:
    map<string, vector<pair<string, int>>> graph;
};

#endif // TRAIN_H
