#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N;
vector<int> number;
vector<int> tree;
vector<int> last;

bool build_tree(int left, int right, int idx) {
    if (left == right) {
        if (number[left - 1] == 1) tree[idx] = 0;
        else tree[idx] = 1;
    } else {
        bool all_zero = true, all_one = true;
        for (int i = left; i <= right; i++) {
            if (number[i - 1] == 0) all_one = false;
            else all_zero = false;
        }
        if (all_zero) tree[idx] = 1;
        else if (all_one) tree[idx] = 0;
        else tree[idx] = 2;
        
        int mid = (left + right - 1) / 2;
        build_tree(left, mid, idx + 1);
        build_tree(mid + 1, right, idx + right - left + 1);
    }
    return true;
}

bool last_order(int left, int right, int last_left, int last_right) {
    if (left == right) last[last_left] = tree[left];
    else {
        last[last_right] = tree[left];
        int mid = (right + left) / 2;
        last_order(left + 1, mid, last_left, (last_left + last_right) / 2 - 1);
        last_order(mid + 1, right, 
                   (last_left + last_right) / 2, last_right - 1);
    }
    return true;
}

int main() {
    cin >> N;
    int size = pow(2, N);
    number.resize(size);
    for (int i = 0; i < size; ++i) {
        cin >> number[i];
    }

    int node_num = pow(2, N + 1) - 1;
    tree.resize(node_num + 1);
    last.resize(node_num + 1);

    build_tree(1, size, 1);
    last_order(1, node_num, 1, node_num);

    for (int i = 1; i <= node_num; ++i) {
        if (last[i] == 0) cout << "I";
        else if (last[i] == 1) cout << "B";
        else cout << "F";
    }
    cout << endl;

    return 0;
}