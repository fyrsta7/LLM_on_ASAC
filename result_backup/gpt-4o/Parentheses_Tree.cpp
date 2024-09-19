#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

struct TreeNode {
    char parens;
    vector<int> children;
};

void countLegalSubstrings(const string &s, vector<int> &dp) {
    int n = s.length();
    vector<int> stack;
    dp.resize(n, 0);
    vector<int> balance(n + 1, 0);
    unordered_set<string> unique_subs;
    
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') {
            stack.push_back(i);
            balance[i + 1] = balance[i] + 1;
        } else {
            if (!stack.empty()) {
                int j = stack.back();
                stack.pop_back();
                balance[i + 1] = balance[i] - 1;
                string legal = s.substr(j, i - j + 1);
                if (unique_subs.find(legal) == unique_subs.end()) {
                    unique_subs.insert(legal);
                    dp[i] += 1;
                }
            } else {
                balance[i + 1] = balance[i];
            }
        }
    }
}

int dfs(TreeNode nodes[], int node, const string &parens, vector<int> &result, string &s) {
    s.push_back(parens[node - 1]);
    countLegalSubstrings(s, result);
    int local_sum = 0;
    for (int val : result) {
        local_sum += val;
    }
    int k = local_sum;
    int xorsum = node * k;
    
    for (int child : nodes[node].children) {
        xorsum ^= dfs(nodes, child, parens, result, s);
    }
    
    s.pop_back();
    return xorsum;
}

int main() {
    int n;
    cin >> n;
    string parens;
    cin >> parens;
    TreeNode nodes[n + 1];
    
    for (int i = 2; i <= n; ++i) {
        int parent;
        cin >> parent;
        nodes[parent].children.push_back(i);
    }
    
    string s;
    vector<int> result;
    
    int final_result = dfs(nodes, 1, parens, result, s);
    cout << final_result << endl;
    
    return 0;
}