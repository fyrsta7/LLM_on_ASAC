#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int N, M, p;
vector<vector<int>> stairs;
vector<vector<int>> number;

int distance(int begin, int target) {
    return target >= begin ? target - begin : target + M - begin;
}

int round_next(int begin, int d, int len) {
    return (begin + d - 1) % len + 1;
}

int go_up(const vector<int>& layer_stairs, const vector<int>& layer_number, int enter) {
    vector<int> room_with_stairs;
    for (int i = 1; i <= M; ++i) {
        if (layer_stairs[i - 1] == 1) {
            room_with_stairs.push_back(i);
        }
    }
    int stair_len = room_with_stairs.size();
    int d = numeric_limits<int>::max();
    for (int i = 1; i <= M; ++i) {
        if (layer_stairs[i - 1] == 1) {
            d = min(d, distance(enter, i));
        }
    }
    int begin = round_next(enter, d, M);
    int begin_loc = find(room_with_stairs.begin(), room_with_stairs.end(), begin) - room_with_stairs.begin();
    return room_with_stairs[round_next(begin_loc, layer_number[enter - 1] - 1, stair_len)];
}

int main() {
    cin >> N >> M >> p;
    stairs.resize(N, vector<int>(M));
    number.resize(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> stairs[i][j];
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> number[i][j];
        }
    }

    vector<int> code(N);
    code[0] = p + 1;
    for (int i = 0; i < N - 1; ++i) {
        code[i + 1] = go_up(stairs[i], number[i], code[i]);
    }

    int answer = 0;
    for (int i = 0; i < N; ++i) {
        answer += number[i][code[i] - 1];
    }
    answer %= 20123;

    cout << answer << endl;
    return 0;
}
