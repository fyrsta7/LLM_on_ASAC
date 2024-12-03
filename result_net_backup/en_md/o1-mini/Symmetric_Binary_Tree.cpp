#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    int left, right;
    TreeNode() : val(0), left(-1), right(-1) {}
};

vector<TreeNode> tree;
unordered_map<string, int> memo;

string getSubtreeKey(int node) {
    if (node == -1) return "#";
    string leftKey = getSubtreeKey(tree[node].left);
    string rightKey = getSubtreeKey(tree[node].right);
    return to_string(tree[node].val) + "(" + leftKey + ")" + "(" + rightKey + ")";
}

int findSymmetricSubtree(int node) {
    if (node == -1) return 0;
    
    string subtreeKey = getSubtreeKey(node);
    
    if (memo.find(subtreeKey) != memo.end()) {
        return memo[subtreeKey];
    }
    
    int leftSize = findSymmetricSubtree(tree[node].left);
    int rightSize = findSymmetricSubtree(tree[node].right);
    
    memo[subtreeKey] = max(leftSize, rightSize) + 1;
    return memo[subtreeKey];
}

int main() {
    int n;
    cin >> n;
    
    tree.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> tree[i].val;
    }
    
    for (int i = 0; i < n; ++i) {
        cin >> tree[i].left >> tree[i].right;
    }
    
    int result = 0;
    for (int i = 0; i < n; ++i) {
        result = max(result, findSymmetricSubtree(i));
    }
    
    cout << result << endl;
    return 0;
}