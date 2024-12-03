#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef long long ll;

const int OFFSET = 100000;
const int MAX_BALANCE = 200001;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    // Nodes are 1-based
    vector<vector<int>> tree(n+1, vector<int>());
    for(int i=2;i<=n;i++){
        int f;
        cin >> f;
        tree[f].push_back(i);
    }
    // Initialize frequency array
    int* freq = new int[MAX_BALANCE]();
    ll ans =0;
    // Initialize balance and freq
    int balance =0;
    freq[OFFSET + balance] =1;
    // DFS using iterative approach to avoid stack overflow
    // Each stack element: node, child index, k_parent, balance before node
    struct StackFrame{
        int node;
        int child_idx;
        ll k_parent;
        int balance_before;
    };
    vector<StackFrame> stack_frames;
    // Initialize stack with root
    stack_frames.push_back(StackFrame{1, 0, 0, balance});
    while(!stack_frames.empty()){
        StackFrame &current = stack_frames.back();
        int u = current.node;
        if(current.child_idx == 0){
            // Entering the node
            // Update balance
            if(s[u-1] == '('){
                balance +=1;
            }
            else{
                balance -=1;
            }
            // Calculate k_i
            if(balance + OFFSET >=0 && balance + OFFSET < MAX_BALANCE){
                ll k_new = freq[balance + OFFSET];
                ll k_i = current.k_parent + k_new;
                ans ^= ((ll)u * k_i);
                // Update frequency
                freq[balance + OFFSET] +=1;
                // Update the frame with k_i
                current.k_parent = k_i;
            }
        }
        if(current.child_idx < tree[current.node].size()){
            // Process next child
            int child = tree[current.node][current.child_idx];
            current.child_idx +=1;
            // Push child to stack
            stack_frames.push_back(StackFrame{child, 0, current.k_parent, balance});
        }
        else{
            // Exiting the node
            // Revert balance and frequency
            if(s[u-1] == '('){
                balance -=1;
            }
            else{
                balance +=1;
            }
            freq[balance + OFFSET] -=1;
            stack_frames.pop_back();
        }
    }
    cout << ans;
    delete[] freq;
}