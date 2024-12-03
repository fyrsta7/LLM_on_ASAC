#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N, M, X0;
vector<int> H;
vector<int> S;
vector<int> X;

struct City {
    int index;
    int height;
    int distance;
};

bool compareCities(const City &a, const City &b) {
    if (a.distance != b.distance) return a.distance < b.distance;
    return a.height < b.height;
}

vector<int> plan_B(int current_city) {
    vector<City> cities;
    for (int i = current_city + 1; i <= N; ++i) {
        cities.push_back({i, H[i], abs(H[current_city] - H[i])});
    }
    sort(cities.begin(), cities.end(), compareCities);
    return {cities[0].index, cities[0].distance};
}

vector<int> plan_A(int current_city) {
    vector<City> cities;
    for (int i = current_city + 1; i <= N; ++i) {
        cities.push_back({i, H[i], abs(H[current_city] - H[i])});
    }
    sort(cities.begin(), cities.end(), compareCities);
    if (cities.size() > 1) {
        return {cities[1].index, cities[1].distance};
    } else {
        return {cities[0].index, cities[0].distance};
    }
}

vector<int> travel(int start_city, int limit) {
    int current_city = start_city;
    int total_distance_A = 0, total_distance_B = 0;
    int days = 0;

    while (true) {
        if (days % 2 == 0) {
            vector<int> next_city = plan_A(current_city);
            if (total_distance_A + total_distance_B + next_city[1] > limit) break;
            total_distance_A += next_city[1];
            current_city = next_city[0];
        } else {
            vector<int> next_city = plan_B(current_city);
            if (total_distance_A + total_distance_B + next_city[1] > limit) break;
            total_distance_B += next_city[1];
            current_city = next_city[0];
        }
        days++;
    }

    return {total_distance_A, total_distance_B};
}

int main() {
    cin >> N;
    H.resize(N + 1);
    for (int i = 1; i <= N; ++i) cin >> H[i];
    cin >> X0 >> M;
    S.resize(M);
    X.resize(M);
    for (int i = 0; i < M; ++i) cin >> S[i] >> X[i];

    vector<vector<int>> ans(M, vector<int>(2));
    for (int i = 0; i < M; ++i) {
        ans[i] = travel(S[i], X[i]);
    }

    for (int i = 0; i < M; ++i) {
        cout << ans[i][0] << " " << ans[i][1] << endl;
    }

    return 0;
}
