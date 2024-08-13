#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int weight;
    int left;
    int right;
};

vector<Node> tree;
vector<vector<int>> memo;

int checkSubtree(int leftRoot, int rightRoot) {
    if (leftRoot == -1 && rightRoot == -1) return 0;
    if (leftRoot == -1 || rightRoot == -1) return -1;
    if (tree[leftRoot].weight != tree[rightRoot].weight) return -1;
    if (memo[leftRoot][rightRoot] != -2) return memo[leftRoot][rightRoot]; 

    int leftCheck = checkSubtree(tree[leftRoot].left, tree[rightRoot].right);
    int rightCheck = checkSubtree(tree[leftRoot].right, tree[rightRoot].left);

    if (leftCheck == -1 || rightCheck == -1) return memo[leftRoot][rightRoot] = -1;

    return memo[leftRoot][rightRoot] = 1 + leftCheck + rightCheck;
}

int largestSymmetricSubtree(int root) {
    if (root == -1) return 0;
    
    int result = checkSubtree(tree[root].left, tree[root].right);
    if (result != -1) result += 1; 

    int leftResult = largestSymmetricSubtree(tree[root].left);
    int rightResult = largestSymmetricSubtree(tree[root].right);

    return max(result, max(leftResult, rightResult));
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
    
    memo.assign(n + 1, vector<int>(n + 1, -2));
    cout << largestSymmetricSubtree(1) << endl;

    return 0;
}
