#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N, M, X0;
vector<int> H;
vector<int> S;
vector<int> X;

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

vector<int> travel(int start_city, int limit) {
    vector<int> route(1, start_city);
    int days = 0;
    int total_distance = 0;
    int odd_distance = 0, even_distance = 0;

    while (true) {
        int next_city;
        if (days % 2 == 0) {
            next_city = plan_A(route.back());
        } else {
            next_city = plan_B(route.back());
        }
        int dist = d(route.back(), next_city);
        if (total_distance + dist > limit) break;
        total_distance += dist;
        route.push_back(next_city);
        if (days % 2 == 0) {
            odd_distance += dist;
        } else {
            even_distance += dist;
        }
        days++;
    }

    return {odd_distance, even_distance};
}

int main() {
    cin >> N >> X0 >> M;
    H.resize(N + 1);
    S.resize(M);
    X.resize(M);

    for (int i = 1; i <= N; ++i) {
        cin >> H[i];
    }

    for (int i = 0; i < M; ++i) {
        cin >> S[i] >> X[i];
    }

    vector<vector<int>> ans(M, vector<int>(2));
    for (int i = 0; i < M; ++i) {
        ans[i] = travel(S[i], X[i]);
    }

    for (int i = 0; i < M; ++i) {
        cout << ans[i][0] << " " << ans[i][1] << endl;
    }

    return 0;
}
