#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N, M, X0;
vector<int> H;
vector<int> S, X;

int d(int i, int j) {
    return abs(H[i] - H[j]);
}

bool near(int d1, int d2, int H1, int H2) {
    return d1 < d2 || (d1 == d2 && H1 < H2);
}

int plan_B(int current_city) {
    int nearest = current_city + 1;
    for (int i = current_city + 2; i <= N; ++i) {
        if (near(d(current_city, i), d(current_city, nearest), H[i], H[nearest])) {
            nearest = i;
        }
    }
    return nearest;
}

int plan_A(int current_city) {
    int nearest = current_city + 1;
    int second_near = current_city + 2;
    for (int i = current_city + 3; i <= N; ++i) {
        if (near(d(current_city, i), d(current_city, nearest), H[i], H[nearest])) {
            second_near = nearest;
            nearest = i;
        } else if (near(d(current_city, i), d(current_city, second_near), H[i], H[second_near])) {
            second_near = i;
        }
    }
    return second_near;
}

pair<int, int> travel(int start_city, int limit) {
    vector<int> route = {start_city};
    int days = 0;
    int total_distance_A = 0, total_distance_B = 0;

    while (true) {
        int next_city;
        if (days % 2 == 0) {
            next_city = plan_A(route.back());
        } else {
            next_city = plan_B(route.back());
        }
        if (next_city > N || d(route.back(), next_city) + total_distance_A + total_distance_B > limit) {
            break;
        }
        route.push_back(next_city);
        if (days % 2 == 0) {
            total_distance_A += d(route[days], route[days + 1]);
        } else {
            total_distance_B += d(route[days], route[days + 1]);
        }
        ++days;
    }

    return {total_distance_A, total_distance_B};
}

int main() {
    cin >> N;
    H.resize(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> H[i];
    }
    cin >> X0 >> M;
    S.resize(M);
    X.resize(M);
    for (int i = 0; i < M; ++i) {
        cin >> S[i] >> X[i];
    }

    vector<pair<int, int>> ans(M);
    for (int i = 0; i < M; ++i) {
        ans[i] = travel(S[i], X[i]);
    }

    for (int i = 0; i < M; ++i) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }

    return 0;
}
