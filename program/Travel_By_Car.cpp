#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

int n;
vector<int> heights;

// Function to simulate driving for given start and max distance
pair<int, int> drive(int start, int max_distance) {
    int distA = 0, distB = 0;
    bool turnA = true;
    int current_city = start;
    int total_distance = 0;

    while (true) {
        int next_city_idx = -1;
        int second_next_city_idx = -1;
        int min_distance = INT_MAX;
        int second_min_distance = INT_MAX;

        for (int i = current_city + 1; i < n; ++i) {
            int distance = abs(heights[current_city] - heights[i]);
            if (distance < min_distance) {
                second_min_distance = min_distance;
                second_next_city_idx = next_city_idx;
                min_distance = distance;
                next_city_idx = i;
            } else if (distance < second_min_distance) {
                second_min_distance = distance;
                second_next_city_idx = i;
            }
        }

        int next_city = turnA ? second_next_city_idx : next_city_idx;
        if (next_city == -1)
            break;

        int travel_distance = abs(heights[current_city] - heights[next_city]);
        if (total_distance + travel_distance > max_distance)
            break;

        total_distance += travel_distance;
        if (turnA) {
            distA += travel_distance;
        } else {
            distB += travel_distance;
        }
        current_city = next_city;
        turnA = !turnA;
    }
    
    return make_pair(distA, distB);
}

int main() {
    cin >> n;
    heights.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }

    int x0;
    cin >> x0;
    
    int m;
    cin >> m;
    
    vector<pair<int, int>> queries(m);
    for (int i = 0; i < m; ++i) {
        cin >> queries[i].first >> queries[i].second;
        queries[i].first--;  // Convert to 0-based index
    }

    // Find the best starting city for x0
    int best_start = -1;
    double best_ratio = INFINITY;

    for (int i = 0; i < n; ++i) {
        pair<int, int> result = drive(i, x0);
        int distA = result.first;
        int distB = result.second;

        double ratio;
        if (distB == 0) {
            ratio = INFINITY;
        } else {
            ratio = (double)distA / distB;
        }

        if (ratio < best_ratio || (ratio == best_ratio && heights[i] > heights[best_start])) {
            best_ratio = ratio;
            best_start = i;
        }
    }

    cout << best_start + 1 << endl;  // Convert back to 1-based index

    // For each query, calculate the distances
    for (int i = 0; i < m; ++i) {
        pair<int, int> result = drive(queries[i].first, queries[i].second);
        cout << result.first << " " << result.second << endl;
    }

    return 0;
}