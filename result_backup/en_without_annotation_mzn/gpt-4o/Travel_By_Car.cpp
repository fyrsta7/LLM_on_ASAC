#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int N, X0, M;
std::vector<int> H, S, X;

int d(int i, int j) {
    return std::abs(H[i] - H[j]);
}

bool near(int d1, int d2, int H1, int H2) {
    return d1 < d2 || (d1 == d2 && H1 < H2);
}

int plan_B(int current_city) {
    int nearest = N;
    for (int i = current_city + 1; i < N; ++i) {
        if (near(d(current_city, nearest), d(current_city, i), H[nearest], H[i])) {
            nearest = i;
        }
    }
    return nearest;
}

int plan_A(int current_city) {
    int nearest = N, second_near = N;
    for (int i = current_city + 1; i < N; ++i) {
        if (near(d(current_city, nearest), d(current_city, i), H[nearest], H[i])) {
            second_near = nearest;
            nearest = i;
        } else if (near(d(current_city, second_near), d(current_city, i), H[second_near], H[i])) {
            second_near = i;
        }
    }
    return second_near;
}

std::vector<int> travel(int start_city, int limit) {
    std::vector<int> route(N + 1, N + 1);
    std::vector<int> res(2, 0);
    int days = 0;
    int total_distance_A = 0, total_distance_B = 0;

    route[0] = start_city;
    while (true) {
        int next_city;
        if (days % 2 == 0) {
            next_city = plan_A(route[days]);
            total_distance_A += d(route[days], next_city);
        } else {
            next_city = plan_B(route[days]);
            total_distance_B += d(route[days], next_city);
        }

        if (total_distance_A + total_distance_B > limit || next_city == N + 1) break;

        route[++days] = next_city;
    }

    res[0] = total_distance_A;
    res[1] = total_distance_B;
    return res;
}

int main() {
    std::cin >> N;
    H.resize(N);
    for (int i = 0; i < N; ++i) std::cin >> H[i];
    std::cin >> X0 >> M;

    S.resize(M);
    X.resize(M);
    for (int i = 0; i < M; ++i) std::cin >> S[i];
    for (int i = 0; i < M; ++i) std::cin >> X[i];

    std::vector<std::vector<int>> ans(M, std::vector<int>(2));
    for (int i = 0; i < M; ++i) {
        ans[i] = travel(S[i], X[i]);
    }

    for (int i = 0; i < M; ++i) {
        std::cout << ans[i][0] << " , " << ans[i][1] << "\n";
    }
    
    return 0;
}