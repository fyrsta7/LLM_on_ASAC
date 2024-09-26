#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode {
    int weight;
    int left, right;
};

vector<TreeNode> tree;
vector<int> subtreeSize;

int calculateSubtreeSize(int node) {
    if (node == -1) return 0;
    if (subtreeSize[node] != -1) return subtreeSize[node];
    subtreeSize[node] = 1 + calculateSubtreeSize(tree[node].left) + calculateSubtreeSize(tree[node].right);
    return subtreeSize[node];
}

bool isSymmetric(int node1, int node2) {
    if (node1 == -1 && node2 == -1) return true;
    if (node1 == -1 || node2 == -1) return false;
    if (tree[node1].weight != tree[node2].weight) return false;
    return isSymmetric(tree[node1].left, tree[node2].right) && isSymmetric(tree[node1].right, tree[node2].left);
}

int findLargestSymmetricSubtree(int node) {
    if (node == -1) return 0;
    int left = tree[node].left, right = tree[node].right;
    int maxSubtreeSize = 1;
    if (isSymmetric(left, right)) {
        maxSubtreeSize = subtreeSize[node];
    } else {
        maxSubtreeSize = max(findLargestSymmetricSubtree(left), findLargestSymmetricSubtree(right));
    }
    return maxSubtreeSize;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    tree.resize(n + 1);
    subtreeSize.assign(n + 1, -1);

    for (int i = 1; i <= n; ++i) {
        cin >> tree[i].weight;
    }

    for (int i = 1; i <= n; ++i) {
        cin >> tree[i].left >> tree[i].right;
    }

    calculateSubtreeSize(1);
    int result = findLargestSymmetricSubtree(1);
    cout << result << endl;

    return 0;
}
