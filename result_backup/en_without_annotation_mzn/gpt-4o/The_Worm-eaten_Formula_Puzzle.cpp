#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Function to find the position of a character in the alphabet
int charPosition(char c) {
    return c - 'A';
}

// Utility function to check if all elements in 'result' are unique
bool allDifferent(const vector<int>& result) {
    unordered_map<int, bool> seen;
    for (int num : result) {
        if (seen.find(num) != seen.end()) {
            return false;
        }
        seen[num] = true;
    }
    return true;
}

// Recursive function to check the add_sum property
bool calculate(const vector<vector<int>>& cal, int i, int flag, int N) {
    if (i == 0)
        return true;
    return (cal[0][i - 1] + cal[1][i - 1] + flag) % N == cal[2][i - 1] &&
           calculate(cal, i - 1, (cal[0][i - 1] + cal[1][i - 1] + flag) / N, N);
}

// Solve the problem
bool solveProblem(int N, const vector<vector<string>>& add, vector<int>& result) {
    vector<vector<int>> add_num(3, vector<int>(N));
    vector<vector<int>> tmp(3, vector<int>(N));

    // Map add strings to positions in the alphabet
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            add_num[i][j] = charPosition(add[i][j][0]);
        }
    }

    // Generate all permutations of 0 to N-1
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 0);

    do {
        if (!allDifferent(perm))
            continue;

        // Map add_num to current permutation (result)
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < N; ++j) {
                tmp[i][j] = perm[add_num[i][j]];
            }
        }

        // Check if current permutation satisfies the condition
        if (calculate(tmp, N, 0, N)) {
            result = perm;
            return true;
        }
    } while (next_permutation(perm.begin(), perm.end()));

    return false;
}

int main() {
    int N;
    cin >> N;

    vector<vector<string>> add(3, vector<string>(N));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> add[i][j];
        }
    }

    vector<int> result(N);

    if (solveProblem(N, add, result)) {
        for (int i = 0; i < N; ++i) {
            cout << result[i] << " ";
        }
        cout << endl;
    } else {
        cout << "No solution found" << endl;
    }

    return 0;
}
