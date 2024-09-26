#include <iostream>
#include <string>
using namespace std;

class TreeNode {
public:
    char type; // 'B', 'I', or 'F'
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(char t) : type(t), left(nullptr), right(nullptr) {}
};

TreeNode* buildFbiTree(const string& s) {
    if (s.empty()) return nullptr;

    bool hasZero = false, hasOne = false;
    for (char c : s) {
        if (c == '0') hasZero = true;
        if (c == '1') hasOne = true;
    }

    char nodeType = hasZero && hasOne ? 'F' : (hasZero ? 'B' : 'I');
    TreeNode* node = new TreeNode(nodeType);

    if (s.length() > 1) {
        int mid = s.length() / 2;
        node->left = buildFbiTree(s.substr(0, mid));
        node->right = buildFbiTree(s.substr(mid));
    }

    return node;
}

void postOrderTraversal(TreeNode* node, string& result) {
    if (!node) return;
    postOrderTraversal(node->left, result);
    postOrderTraversal(node->right, result);
    result += node->type;
}

int main() {
    int N;
    string s;
    cin >> N >> s;

    TreeNode* root = buildFbiTree(s);
    string result;
    postOrderTraversal(root, result);

    cout << result << endl;

    return 0;
}