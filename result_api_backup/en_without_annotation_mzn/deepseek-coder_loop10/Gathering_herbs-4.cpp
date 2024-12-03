#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Herb {
    int cost;
    int value;
};

bool compare(Herb a, Herb b) {
    return (double)a.value / a.cost > (double)b.value / b.cost;
}

int main() {
    int T, M;
    cin >> T >> M;
    vector<Herb> herbs(M);
    for (int i = 0; i < M; ++i) {
        cin >> herbs[i].cost >> herbs[i].value;
    }

    sort(herbs.begin(), herbs.end(), compare);

    int total = 0;
    int cost = 0;

    for (int i = 0; i < M; ++i) {
        if (cost + herbs[i].cost <= T) {
            cost += herbs[i].cost;
            total += herbs[i].value;
        }
    }

    cout << total << endl;

    return 0;
}