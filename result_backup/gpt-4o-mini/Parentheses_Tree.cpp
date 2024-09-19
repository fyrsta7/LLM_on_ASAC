#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int calculateLegalSubstrings(string& s) {
    int n = s.length();
    int count = 0;

    // Check all substrings
    for (int i = 0; i < n; ++i) {
        int balance = 0;
        unordered_set<string> substrings;

        for (int j = i; j < n; ++j) {
            if (s[j] == '(') {
                balance++;
            } else {
                balance--;
            }

            // Only consider if balance is non-negative
            if (balance < 0) break;

            if (balance == 0) {
                substrings.insert(s.substr(i, j - i + 1));
            }
        }
        count += substrings.size();
    }
    return count;
}

void dfs(int node, vector<vector<int>>& tree, string& parentheses, vector<int>& result) {
    string path;
    int current = node;

    // Build the path to the root
    while (current != 0) {
        path = parentheses[current - 1] + path; // node indices are 1-based
        current = tree[current][0]; // parent
    }

    result[node] = calculateLegalSubstrings(path);
}

int main() {
    int n;
    cin >> n;
    
    string parentheses;
    cin >> parentheses;

    vector<vector<int>> tree(n + 1);
    for (int i = 2; i <= n; ++i) {
        int parent;
        cin >> parent;
        tree[parent].push_back(i);
    }

    vector<int> result(n + 1, 0);
    
    // Perform DFS to calculate the k_i values
    for (int i = 1; i <= n; ++i) {
        dfs(i, tree, parentheses, result);
    }

    // Compute the final xor result
    int xorSum = 0;
    for (int i = 1; i <= n; ++i) {
        xorSum ^= (i * result[i]);
    }

    cout << xorSum << endl;
    return 0;
}