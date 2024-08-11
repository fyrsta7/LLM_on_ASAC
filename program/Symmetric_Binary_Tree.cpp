#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool isSymmetric(TreeNode* a, TreeNode* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return (a->val == b->val) && isSymmetric(a->left, b->right) && isSymmetric(a->right, b->left);
}

int countNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

pair<int, bool> largestSymmetricSubtreeHelper(TreeNode* root) {
    if (!root) return {0, true};

    auto [leftSize, leftSym] = largestSymmetricSubtreeHelper(root->left);
    auto [rightSize, rightSym] = largestSymmetricSubtreeHelper(root->right);

    if (leftSym && rightSym && isSymmetric(root->left, root->right)) {
        return {1 + leftSize + rightSize, true};
    }
    return {max(leftSize, rightSize), false};
}

int largestSymmetricSubtree(TreeNode* root) {
    return largestSymmetricSubtreeHelper(root).first;
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int i = 0; i < n; ++i) cin >> values[i];

    vector<TreeNode*> nodes(n + 1);
    for (int i = 1; i <= n; ++i) nodes[i] = new TreeNode(values[i - 1]);

    for (int i = 1; i <= n; ++i) {
        int left, right;
        cin >> left >> right;
        if (left != -1) nodes[i]->left = nodes[left];
        if (right != -1) nodes[i]->right = nodes[right];
    }

    cout << largestSymmetricSubtree(nodes[1]) << endl;

    return 0;
}
