#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct City {
    int id;
    int altitude;
    bool operator<(const City &other) const {
        return altitude < other.altitude;
    }
};

int main() {
    int n;
    cin >> n;
    vector<City> cities(n);
    for (int i = 0; i < n; ++i) {
        cities[i].id = i + 1;
        cin >> cities[i].altitude;
    }
    sort(cities.begin(), cities.end());

    vector<int> rank(n + 1);
    for (int i = 0; i < n; ++i) {
        rank[cities[i].id] = i;
    }

    int x0;
    cin >> x0;

    int m;
    cin >> m;
    vector<pair<int, int>> queries(m);
    for (int i = 0; i < m; ++i) {
        cin >> queries[i].first >> queries[i].second;
    }

    vector<int> closest(n, -1), secondClosest(n, -1);
    for (int i = 0; i < n; ++i) {
        if (i > 0) closest[i] = i - 1;
        if (i < n - 1) secondClosest[i] = i + 1;
    }

    auto updateClosest = [&](int i) {
        if (closest[i] != -1) {
            secondClosest[i] = closest[i];
            closest[i] = closest[closest[i]];
        }
    };

    vector<int> aDist(n + 1, 0), bDist(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int cityId = cities[i].id;
        int distA = 0, distB = 0;
        int totalDist = 0;
        bool isA = true;
        int current = i;

        while (true) {
            if (isA) {
                if (secondClosest[current] == -1 || totalDist + abs(cities[current].altitude - cities[secondClosest[current]].altitude) > x0) break;
                distA += abs(cities[current].altitude - cities[secondClosest[current]].altitude);
                totalDist += abs(cities[current].altitude - cities[secondClosest[current]].altitude);
                current = secondClosest[current];
            } else {
                if (closest[current] == -1 || totalDist + abs(cities[current].altitude - cities[closest[current]].altitude) > x0) break;
                distB += abs(cities[current].altitude - cities[closest[current]].altitude);
                totalDist += abs(cities[current].altitude - cities[closest[current]].altitude);
                current = closest[current];
            }
            isA = !isA;
        }

        aDist[cityId] = distA;
        bDist[cityId] = distB;
        updateClosest(i);
    }

    double minRatio = INFINITY;
    int minCity = -1;
    for (int i = 1; i <= n; ++i) {
        if (bDist[i] == 0) continue;
        double ratio = static_cast<double>(aDist[i]) / bDist[i];
        if (ratio < minRatio || (ratio == minRatio && cities[rank[i]].altitude > cities[rank[minCity]].altitude)) {
            minRatio = ratio;
            minCity = i;
        }
    }

    cout << minCity << endl;

    for (const auto &query : queries) {
        int start = query.first;
        int x = query.second;
        int distA = 0, distB = 0;
        int totalDist = 0;
        bool isA = true;
        int current = rank[start];

        while (true) {
            if (isA) {
                if (secondClosest[current] == -1 || totalDist + abs(cities[current].altitude - cities[secondClosest[current]].altitude) > x) break;
                distA += abs(cities[current].altitude - cities[secondClosest[current]].altitude);
                totalDist += abs(cities[current].altitude - cities[secondClosest[current]].altitude);
                current = secondClosest[current];
            } else {
                if (closest[current] == -1 || totalDist + abs(cities[current].altitude - cities[closest[current]].altitude) > x) break;
                distB += abs(cities[current].altitude - cities[closest[current]].altitude);
                totalDist += abs(cities[current].altitude - cities[closest[current]].altitude);
                current = closest[current];
            }
            isA = !isA;
        }

        cout << distA << " " << distB << endl;
    }

    return 0;
}
