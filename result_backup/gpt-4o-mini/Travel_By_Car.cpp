#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct City {
    int index;
    int height;
};

bool compareByHeight(const City &a, const City &b) {
    return a.height < b.height;
}

pair<int, int> drive(int start, long long x, const vector<int>& heights) {
    long long distanceA = 0, distanceB = 0;
    int currentCity = start - 1;
    bool turnA = true; // A starts

    while (true) {
        vector<pair<int, int>> dists; // {distance, index}
        for (int i = currentCity + 1; i < heights.size(); i++) {
            dists.emplace_back(abs(heights[currentCity] - heights[i]), i);
        }

        if (dists.size() < 1) break; // No further cities
        
        sort(dists.begin(), dists.end()); // Sort by distance then by index
        if (turnA) {
            if (dists.size() < 2) break; // No second option
            distanceA += dists[1].first;
            if (distanceA + distanceB > x) break; // Out of range
            currentCity = dists[1].second;
        } else {
            distanceB += dists[0].first;
            if (distanceA + distanceB > x) break; // Out of range
            currentCity = dists[0].second;
        }
        turnA = !turnA; // Switch turn
    }

    return {static_cast<int>(distanceA), static_cast<int>(distanceB)};
}

int main() {
    int n;
    cin >> n;
    vector<int> heights(n);
    vector<City> cities(n);

    for (int i = 0; i < n; i++) {
        cin >> heights[i];
        cities[i] = {i + 1, heights[i]};
    }
    
    int x0;
    cin >> x0;
    
    sort(cities.begin(), cities.end(), compareByHeight);
    
    int bestCity = -1;
    double bestRatio = numeric_limits<double>::max();
    
    for (const auto &city : cities) {
        long long distanceA, distanceB;
        tie(distanceA, distanceB) = drive(city.index, x0, heights);
        
        double ratio = (distanceB == 0) ? numeric_limits<double>::infinity() : static_cast<double>(distanceA) / distanceB;
        
        if (ratio < bestRatio || (ratio == bestRatio && city.height > heights[bestCity - 1])) {
            bestRatio = ratio;
            bestCity = city.index;
        }
    }
    
    cout << bestCity << endl;

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int si;
        long long xi;
        cin >> si >> xi;
        auto result = drive(si, xi, heights);
        cout << result.first << " " << result.second << endl;
    }
    
    return 0;
}