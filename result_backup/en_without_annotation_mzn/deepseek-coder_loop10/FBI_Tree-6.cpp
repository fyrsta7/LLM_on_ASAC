#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N;
vector<int> number;
vector<int> tree;
vector<char> last;

void build_tree(int left, int right, int idx) {
    if (left == right) {
        tree[idx] = (number[left] == 1) ? 0 : 1;
    } else {
        int mid = (left + right) / 2;
        int left_count = 0, right_count = 0;
        for (int i = left; i <= mid; ++i) left_count += (number[i] == 0);
        for (int i = mid + 1; i <= right; ++i) right_count += (number[i] == 0);
        
        if (left_count == 0 && right_count == 0) tree[idx] = 0;
        else if (left_count == 0 || right_count == 0) tree[idx] = 1;
        else tree[idx] = 2;
        
        build_tree(left, mid, 2 * idx);
        build_tree(mid + 1, right, 2 * idx + 1);
    }
}

void last_order(int left, int right, int last_left, int last_right) {
    if (left == right) {
        last[last_left] = (tree[left] == 0) ? 'I' : (tree[left] == 1) ? 'B' : 'F';
    } else {
        int mid = (left + right) / 2;
        last[last_right] = (tree[left] == 0) ? 'I' : (tree[left] == 1) ? 'B' : 'F';
        last_order(left + 1, mid, last_left, (last_left + last_right) / 2 - 1);
        last_order(mid + 1, right, (last_left + last_right) / 2, last_right - 1);
    }
}

int main() {
    cin >> N;
    int size = pow(2, N);
    number.resize(size);
    for (int i = 0; i < size; ++i) cin >> number[i];
    
    int node_num = pow(2, N + 1) - 1;
    tree.resize(node_num + 1);
    last.resize(node_num + 1);
    
    build_tree(1, size, 1);
    last_order(1, node_num, 1, node_num);
    
    for (int i = 1; i <= node_num; ++i) cout << last[i];
    cout << endl;
    
    return 0;
}
