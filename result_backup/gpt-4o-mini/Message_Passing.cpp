#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> T(n + 1); // using 1-based index
    for (int i = 1; i <= n; ++i) {
        cin >> T[i];
    }

    vector<int> rounds(n + 1, -1); // Track how many rounds each student can play
    int maxRounds = 0;

    for (int i = 1; i <= n; ++i) {
        if (rounds[i] != -1) continue; // Already processed

        unordered_set<int> visited;
        int curr = i;
        int depth = 0;
        while (visited.find(curr) == visited.end()) {
            visited.insert(curr);
            curr = T[curr];
            depth++;
        }

        // If we found a cycle, determine how long until someone learns their birthday
        int cycle_start = curr;
        int cycle_length = 0;
        do {
            cycle_length++;
            curr = T[curr];
        } while (curr != cycle_start);

        int chain_length = depth - cycle_length;
        for (int member : visited) {
            if (chain_length >= 0) {
                rounds[member] = chain_length + cycle_length; // All in this component have the same rounds
            } else {
                rounds[member] = cycle_length; // Leading into a direct cycle
            }
        }

        maxRounds = max(maxRounds, rounds[i]);
    }

    cout << maxRounds << endl;
    return 0;
}