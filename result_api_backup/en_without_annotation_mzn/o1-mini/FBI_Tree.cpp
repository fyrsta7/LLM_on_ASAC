#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    int size = 1<<N;
    vector<int> number(size+1);
    for(int i=1;i<=size;i++) cin>>number[i];
    int node_num = (1<<(N+1)) -1;
    vector<int> tree(node_num+1, 0);
    // Compute prefix sums
    vector<int> prefix0(size+1,0), prefix1(size+1,0);
    for(int i=1;i<=size;i++){
        prefix0[i] = prefix0[i-1] + (number[i]==0?1:0);
        prefix1[i] = prefix1[i-1] + (number[i]==1?1:0);
    }
    // Build tree
    function<void(int, int, int)> build_tree = [&](int left, int right, int idx) {
        if(left == right){
            tree[idx] = (number[left]==1)? 0 : 1;
        }
        else{
            int count0 = prefix0[right] - prefix0[left-1];
            int count1 = prefix1[right] - prefix1[left-1];
            if(count0 ==0) tree[idx] =0;
            else if(count1 ==0) tree[idx]=1;
            else tree[idx]=2;
            int mid = (left + right -1)/2;
            build_tree(left, mid, idx+1);
            build_tree(mid+1, right, idx + (mid - left +1) +1 -1);
        }
    };
    build_tree(1, size, 1);
    // Adjust build_tree index for right child
    // Correct the index for right child
    // Redefine build_tree with correct index calculation
    tree.assign(node_num+1, 0);
    build_tree = [&](int left, int right, int idx) -> void{
        if(left == right){
            tree[idx] = (number[left]==1)? 0 : 1;
        }
        else{
            int count0 = prefix0[right] - prefix0[left-1];
            int count1 = prefix1[right] - prefix1[left-1];
            if(count0 ==0) tree[idx] =0;
            else if(count1 ==0) tree[idx]=1;
            else tree[idx]=2;
            int mid = (left + right)/2;
            build_tree(left, mid, idx*2);
            build_tree(mid+1, right, idx*2+1);
        }
    };
    build_tree(1, size, 1);
    // Now build last_order
    vector<int> last(node_num+1, 0);
    function<void(int, int, int, int)> last_order = [&](int left, int right, int last_left, int last_right) -> void{
        if(left == right){
            last[last_left] = tree[left];
        }
        else{
            last[last_right] = tree[left];
            int mid = (left + right)/2;
            int mid_last = (last_left + last_right)/2;
            last_order(left+1, mid, last_left, mid_last -1);
            last_order(mid+1, right, mid_last, last_right -1);
        }
    };
    last_order(1, node_num, 1, node_num);
    // Output
    string res;
    res.reserve(node_num);
    for(int i=1;i<=node_num;i++){
        if(last[i]==0) res += 'I';
        else if(last[i]==1) res += 'B';
        else res += 'F';
    }
    cout << res;
}