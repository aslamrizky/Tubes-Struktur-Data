#include "Train.h"

int main() {
    TrainGraph train;
    train.addStation("Tanjung Priok");
    train.addStation("Jakarta");
    train.addStation("Manggarai");
    train.addStation("Bekasi");
    train.addStation("Depok");
    train.addStation("Bogor");

    train.addEdge("Tanjung Priok", "Jakarta", 2);
    train.addEdge("Jakarta", "Manggarai", 7);
    train.addEdge("Manggarai", "Depok", 11);
    train.addEdge("Manggarai", "Bekasi", 6);
    train.addEdge("Depok", "Bogor", 3);


    train.displayRoute("Jakarta", "Tanjung Priok");
    train.displayRoute("Jakarta", "Bekasi");
    train.displayRoute("Jakarta", "Depok");
    train.displayRoute("Jakarta", "Bogor");

    return 0;
}
