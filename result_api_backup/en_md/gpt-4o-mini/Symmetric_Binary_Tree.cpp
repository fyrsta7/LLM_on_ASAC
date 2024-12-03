#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>

using namespace std;

struct TreeNode {
    int weight;
    int left;
    int right;
};

vector<TreeNode> tree;

pair<bool, int> isSymmetric(int node) {
    if (node == -1) return {true, 0};

    int left = tree[node].left;
    int right = tree[node].right;

    pair<bool, int> leftResult = isSymmetric(left);
    pair<bool, int> rightResult = isSymmetric(right);

    if (leftResult.first && rightResult.first && 
        tree[left].weight == tree[right].weight) {
        int totalCount = 1 + leftResult.second + rightResult.second;
        return {true, totalCount};
    } else {
        return {false, max(leftResult.second, rightResult.second)};
    }
}

int main() {
    int n;
    cin >> n;

    tree.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> tree[i].weight;
    }
    for (int i = 1; i <= n; ++i) {
        cin >> tree[i].left >> tree[i].right;
    }

    int maxSymmetricSize = 0;
    for (int i = 1; i <= n; ++i) {
        auto result = isSymmetric(i);
        maxSymmetricSize = max(maxSymmetricSize, result.second);
    }

    cout << maxSymmetricSize << endl;
    
    return 0;
}