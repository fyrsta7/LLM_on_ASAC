#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> T(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> T[i];
    }

    int x;
    cin >> x;

    unordered_map<int, int> visited;
    int turns = 0;
    int current = x;

    while (visited.find(current) == visited.end()) {
        visited[current] = turns;
        current = T[current];
        ++turns;
    }

    int cycle_start = current;
    int cycle_length = turns - visited[cycle_start];
    int pre_cycle_length = visited[cycle_start];

    if (x == cycle_start) {
        turns = cycle_length;
    } else {
        turns = pre_cycle_length + cycle_length;
    }

    cout << "turns=" << turns << endl;

    return 0;
}