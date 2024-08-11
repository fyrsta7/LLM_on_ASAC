#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
};

bool isMirror(Node* t1, Node* t2) {
    if(t1 == nullptr && t2 == nullptr) return true;
    if(t1 == nullptr || t2 == nullptr) return false;
    
    return (t1->val == t2->val) && isMirror(t1->left, t2->right) && isMirror(t1->right, t2->left);
}

int maxSymmetricSubtree(Node* root) {
    unordered_map<Node*, int> subtreeSize;
    
    if(root == nullptr) return 0;
    
    if(isMirror(root->left, root->right)) {
        return maxSymmetricSubtree(root->left) + maxSymmetricSubtree(root->right) + 1;
    }
    
    return max(maxSymmetricSubtree(root->left), maxSymmetricSubtree(root->right));
}

int main() {
    int n;
    cin >> n;
    
    Node* nodes[1000001];
    
    for(int i = 1; i <= n; i++) {
        int val, left, right;
        cin >> val >> left >> right;
        
        Node* newNode = new Node();
        newNode->val = val;
        newNode->left = (left == -1) ? nullptr : nodes[left];
        newNode->right = (right == -1) ? nullptr : nodes[right];
        
        nodes[i] = newNode;
    }
    
    cout << maxSymmetricSubtree(nodes[1]) << endl;
    
    return 0;
}