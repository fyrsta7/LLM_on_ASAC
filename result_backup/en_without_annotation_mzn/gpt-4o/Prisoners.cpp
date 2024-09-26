#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int N, M;
vector<vector<int>> conflict;
vector<int> prison1, prison2;
int final_value = INT_MAX;

void solve(int idx) {
    if (idx == N) {
        int value1 = 0, value2 = 0;
        if (prison1.size() >= 2) {
            for (const auto& c : conflict) {
                if (find(prison1.begin(), prison1.end(), c[0]) != prison1.end() && 
                    find(prison1.begin(), prison1.end(), c[1]) != prison1.end()) {
                    value1 = max(value1, c[2]);
                }
            }
        }
        if (prison2.size() >= 2) {
            for (const auto& c : conflict) {
                if (find(prison2.begin(), prison2.end(), c[0]) != prison2.end() &&
                    find(prison2.begin(), prison2.end(), c[1]) != prison2.end()) {
                    value2 = max(value2, c[2]);
                }
            }
        }
        final_value = min(final_value, max(value1, value2));
        return;
    }

    prison1.push_back(idx + 1);
    solve(idx + 1);
    prison1.pop_back();

    prison2.push_back(idx + 1);
    solve(idx + 1);
    prison2.pop_back();
}

int main() {
    cin >> N >> M;
    conflict.resize(M, vector<int>(3));
    for (int i = 0; i < M; ++i) {
        cin >> conflict[i][0] >> conflict[i][1] >> conflict[i][2];
    }

    solve(0);

    cout << final_value << endl;
    return 0;
}