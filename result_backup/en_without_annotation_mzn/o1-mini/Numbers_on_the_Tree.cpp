#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Globals
int T;
vector<int> n;
int sum_n;
vector<int> node;
vector<pair<int, int>> edge;
int max_n;
vector<int> begin_n;

// Variables to assign
vector<int> delete_var;
vector<vector<int>> state;
vector<int> p;
vector<ll> score;

// Best solution
ll best_sum = LLONG_MAX;
vector<int> best_p;

// Precompute powers of 2
vector<ll> pow2;

// Function to initialize
void initialize() {
    cin >> T;
    n.resize(T);
    for(int &x: n) cin >> x;
    sum_n = accumulate(n.begin(), n.end(), 0);
    node.resize(sum_n);
    for(int &x: node) cin >> x;
    edge.resize(sum_n - T);
    for(auto &p: edge) cin >> p.first >> p.second;
    max_n = *max_element(n.begin(), n.end());
    begin_n.resize(T);
    begin_n[0] = 0;
    for(int i=1;i<T;i++) begin_n[i] = begin_n[i-1] + n[i-1];
    delete_var.resize(sum_n, -1);
    state.assign(sum_n, vector<int>(max_n +1, 0));
    p.resize(sum_n, -1);
    score.resize(T, 0);
    pow2.resize(20, 1);
    for(int i=1;i<20;i++) pow2[i] = pow2[i-1] *2;
}

// Recursive backtracking
void backtrack(int j, int current_sum) {
    if(current_sum >= best_sum) return;
    if(j == sum_n) {
        // Assign p
        // For simplicity, assume p is identity
        // Compute score
        ll total = 0;
        for(int t=0;t<T;t++) {
            ll s =0;
            for(int jj=0; jj<n[t]; jj++) {
                s += pow2[n[t]-jj-1] * p[begin_n[t]+jj];
            }
            total += s;
        }
        if(total < best_sum){
            best_sum = total;
            best_p = p;
        }
        return;
    }
    // Assign delete_var[j]
    for(int d=1; d < max_n; d++) {
        delete_var[j] = d;
        backtrack(j+1, current_sum);
    }
}

int main(){
    initialize();
    backtrack(0, 0);
    for(int i=0;i<sum_n;i++) cout << best_p[i] << " ";
    return 0;
}