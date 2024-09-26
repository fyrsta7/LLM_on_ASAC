#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    long long mn;
    long long lazy;
} tree_node;

class SegmentTree {
public:
    int n;
    vector<Node> tree;
    SegmentTree(int size) : n(size), tree(4 * size + 4) {}
    
    void build(vector<long long> &arr, int node, int l, int r){
        if(l == r){
            tree[node].mn = arr[l];
            tree[node].lazy = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(arr, node*2, l, mid);
        build(arr, node*2+1, mid+1, r);
        tree[node].mn = min(tree[node*2].mn, tree[node*2+1].mn);
        tree[node].lazy = 0;
    }
    
    void push_down(int node, int l, int r){
        if(tree[node].lazy != 0){
            int mid = (l + r) / 2;
            apply(node*2, l, mid, tree[node].lazy);
            apply(node*2+1, mid+1, r, tree[node].lazy);
            tree[node].lazy = 0;
        }
    }
    
    void apply(int node, int l, int r, long long val){
        tree[node].mn += val;
        tree[node].lazy += val;
    }
    
    bool query_min(int node, int l, int r, int ql, int qr, long long val){
        if(ql > r || qr < l){
            return true;
        }
        if(ql <= l && r <= qr){
            return tree[node].mn >= val;
        }
        push_down(node, l, r);
        int mid = (l + r) / 2;
        bool left = query_min(node*2, l, mid, ql, qr, val);
        bool right = query_min(node*2+1, mid+1, r, ql, qr, val);
        return left && right;
    }
    
    void update_range(int node, int l, int r, int ql, int qr, long long val){
        if(ql > r || qr < l){
            return;
        }
        if(ql <= l && r <= qr){
            apply(node, l, r, val);
            return;
        }
        push_down(node, l, r);
        int mid = (l + r) / 2;
        update_range(node*2, l, mid, ql, qr, val);
        update_range(node*2+1, mid+1, r, ql, qr, val);
        tree[node].mn = min(tree[node*2].mn, tree[node*2+1].mn);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<long long> r(n+1);
    for(int i=1;i<=n;i++) cin >> r[i];
    SegmentTree st(n);
    st.build(r, 1, 1, n);
    bool ok = true;
    int fail_order = 0;
    for(int j=1; j<=m; j++){
        long long d, s, t;
        cin >> d >> s >> t;
        if(ok){
            if(st.query_min(1, 1, n, s, t, d)){
                st.update_range(1, 1, n, s, t, -d);
            }
            else{
                ok = false;
                fail_order = j;
            }
        }
    }
    if(ok){
        cout << "0\n";
    }
    else{
        cout << "-1\n" << fail_order << "\n";
    }
}