#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int distance(int begin, int target, int M) {
    return target >= begin ? target - begin : target + M - begin;
}

int round_next(int begin, int d, int len) {
    return (begin + d - 1) % len + 1;
}

int go_up(vector<int>& layer_stairs, vector<int>& layer_number, int enter, int M) {
    vector<int> room_with_stairs;
    for (int i = 1; i <= M; ++i) {
        if (layer_stairs[i - 1] == 1) {
            room_with_stairs.push_back(i);
        }
    }
    int stair_len = room_with_stairs.size();
    int d = M;
    for (int i = 1; i <= M; ++i) {
        if (layer_stairs[i - 1] == 1) {
            d = min(d, distance(enter, i, M));
        }
    }
    int begin = round_next(enter, d, M);
    int begin_loc = find(room_with_stairs.begin(), room_with_stairs.end(), begin) - room_with_stairs.begin();
    return room_with_stairs[round_next(begin_loc, layer_number[enter - 1] - 1, stair_len)];
}

int main() {
    int N, M, p;
    cin >> N >> M >> p;
    vector<vector<int>> stairs(N, vector<int>(M));
    vector<vector<int>> number(N, vector<int>(M));
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
        code[i + 1] = go_up(stairs[i], number[i], code[i], M);
    }

    int answer = 0;
    for (int i = 0; i < N; ++i) {
        answer = (answer + number[i][code[i] - 1]) % 20123;
    }

    cout << answer << endl;
    return 0;
}
