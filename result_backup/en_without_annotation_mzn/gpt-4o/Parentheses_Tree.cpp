#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

struct TreeNode {
    int id;
    int b_num;
    vector<TreeNode*> children;

    TreeNode(int id, int b_num) : id(id), b_num(b_num) {}
};

bool valid(const vector<int>& sequence) {
    int balance = 0;
    for (int b : sequence) {
        balance += (b == 0 ? 1 : -1);
        if (balance < 0) return false;
    }
    return balance == 0;
}

int route_num(const vector<TreeNode*>& route, const vector<int>& b_num) {
    int count = 0;
    for (size_t i = 0; i < route.size(); ++i) {
        for (size_t j = i; j < route.size(); ++j) {
            vector<int> seq;
            for (size_t k = i; k <= j; ++k) {
                seq.push_back(b_num[route[k]->id - 1]);
            }
            if (valid(seq)) {
                count++;
            }
        }
    }
    return count;
}

int bitwise_xor(int a, int b) {
    return a ^ b;
}

void dfs(TreeNode* node, vector<TreeNode*>& path, vector<int>& b_num, vector<int>& num, int& id) {
    path.push_back(node);
    num[node->id - 1] = route_num(path, b_num);

    for (TreeNode* child : node->children) {
        dfs(child, path, b_num, num, id);
    }

    path.pop_back();
}

int main() {
    int n;
    cin >> n;

    vector<string> bracket(n);
    vector<int> father(n-1);
    vector<int> b_num(n);

    for (int i = 0; i < n; ++i) {
        cin >> bracket[i];
        b_num[i] = (bracket[i] == "(") ? 0 : 1;
    }
    
    for (int i = 0; i < n-1; ++i) {
        cin >> father[i];
    }
    
    vector<TreeNode*> nodes(n);
    for (int i = 0; i < n; ++i) {
        nodes[i] = new TreeNode(i + 1, b_num[i]);
    }
    
    for (int i = 0; i < n-1; ++i) {
        nodes[father[i] - 1]->children.push_back(nodes[i + 1]);
    }

    vector<TreeNode*> path;
    vector<int> num(n);
    int id = 1;
    dfs(nodes[0], path, b_num, num, id);
    
    vector<int> ans(n);
    ans[0] = num[0] * 1;
    for (int i = 1; i < n; ++i) {
        ans[i] = bitwise_xor(ans[i-1], num[i] * (i + 1));
    }

    cout << ans[n-1] << endl;

    for (TreeNode* node : nodes) {
        delete node;
    }

    return 0;
}