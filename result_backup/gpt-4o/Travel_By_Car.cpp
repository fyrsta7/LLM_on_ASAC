#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <queue>

using namespace std;

struct City {
    int id;
    int altitude;
};

struct TripResult {
    int totalDistanceA;
    int totalDistanceB;
};

bool compareCities(const City& a, const City& b) {
    return a.altitude < b.altitude;
}

int getNearestCityIndex(const vector<City>& cities, int currentCityIndex, bool isA, int distanceDriven) {
    int n = cities.size();
    vector<pair<int, int>> distances;

    for (int i = currentCityIndex + 1; i < n; ++i) {
        if (abs(cities[currentCityIndex].altitude - cities[i].altitude) + distanceDriven > distanceDriven) {
            distances.push_back({abs(cities[currentCityIndex].altitude - cities[i].altitude), i});
        }
    }

    if (distances.empty())
        return -1;

    sort(distances.begin(), distances.end());

    if (isA) {
        if (distances.size() > 1) {
            if (distances[1].first == distances[0].first)
                return distances[0].second > distances[1].second ? distances[0].second : distances[1].second;
            return distances[1].second;
        }
        else
            return -1;
    }

    return distances[0].second;
}

TripResult calculateTripResult(const vector<City>& cities, int startCityIndex, int maxDistance) {
    bool isATurn = true;
    int distanceDrivenA = 0;
    int distanceDrivenB = 0;
    int currentCityIndex = startCityIndex;
    int totalDistanceDriven = 0;

    while (true) {
        int nextCityIndex = getNearestCityIndex(cities, currentCityIndex, isATurn, totalDistanceDriven);

        if (nextCityIndex == -1)
            break;

        int distance = abs(cities[currentCityIndex].altitude - cities[nextCityIndex].altitude);

        if (totalDistanceDriven + distance > maxDistance)
            break;

        totalDistanceDriven += distance;

        if (isATurn) {
            distanceDrivenA += distance;
        }
        else {
            distanceDrivenB += distance;
        }

        isATurn = !isATurn;
        currentCityIndex = nextCityIndex;
    }

    return { distanceDrivenA, distanceDrivenB };
}

int main() {
    int n;
    cin >> n;
    vector<City> cities(n);

    for (int i = 0; i < n; ++i) {
        cin >> cities[i].altitude;
        cities[i].id = i + 1;
    }

    int x0;
    cin >> x0;

    int m;
    cin >> m;
    vector<pair<int, int>> queries(m);

    for (int i = 0; i < m; ++i) {
        cin >> queries[i].first >> queries[i].second;
    }

    double minRatio = DBL_MAX;
    int bestStartCity = -1;

    for (int i = 0; i < n; ++i) {
        TripResult result = calculateTripResult(cities, i, x0);

        double ratio;
        if (result.totalDistanceB == 0) {
            ratio = DBL_MAX;
        }
        else {
            ratio = (double)result.totalDistanceA / result.totalDistanceB;
        }

        if (ratio < minRatio || (ratio == minRatio && cities[i].altitude > cities[bestStartCity].altitude)) {
            minRatio = ratio;
            bestStartCity = i;
        }
    }
    
    cout << bestStartCity + 1 << endl;

    for (const auto& query : queries) {
        TripResult result = calculateTripResult(cities, query.first - 1, query.second);
        cout << result.totalDistanceA << " " << result.totalDistanceB << endl;
    }

    return 0;
}