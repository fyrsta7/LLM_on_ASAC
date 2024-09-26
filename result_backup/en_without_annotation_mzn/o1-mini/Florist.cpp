#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> h;

// Case1: even positions are peaks
int m1_max = 0;
int m2_max = 0;

// DP memoization for case1
unordered_map<long long, int> memo1;

// Function key encoding
long long get_key1(int pos, int parity, int last, bool must_be_less){
    return ((long long)pos << 40) | ((long long)parity << 39) | ((long long)last << 1) | (must_be_less?1:0);
}

int dp_case1(int pos, int parity, int last, bool must_be_less){
    if(pos >= n){
        return 0;
    }
    long long key = get_key1(pos, parity, last, must_be_less);
    if(memo1.find(key)!=memo1.end()){
        return memo1[key];
    }
    int res =0;
    for(int i=pos;i<n;i++){
        if(must_be_less && h[i] >= last){
            continue;
        }
        if(parity ==1){ // odd position in subsequence
            res = max(res, 1 + dp_case1(i+1, 0, h[i], false));
        }
        else{ // even position in subsequence
            if(h[i] > last){
                res = max(res, 1 + dp_case1(i+1,1, h[i], true));
            }
        }
    }
    memo1[key]=res;
    return res;
}

// DP memoization for case2
unordered_map<long long, int> memo2;

long long get_key2(int pos, int parity, int last, bool must_be_greater){
    return ((long long)pos << 40) | ((long long)parity << 39) | ((long long)last << 1) | (must_be_greater?1:0);
}

int dp_case2(int pos, int parity, int last, bool must_be_greater){
    if(pos >= n){
        return 0;
    }
    long long key = get_key2(pos, parity, last, must_be_greater);
    if(memo2.find(key)!=memo2.end()){
        return memo2[key];
    }
    int res =0;
    for(int i=pos;i<n;i++){
        if(must_be_greater && h[i] <= last){
            continue;
        }
        if(parity ==1){ // odd position in subsequence
            res = max(res, 1 + dp_case2(i+1, 0, h[i], false));
        }
        else{ // even position in subsequence
            if(h[i] < last){
                res = max(res, 1 + dp_case2(i+1,1, h[i], true));
            }
        }
    }
    memo2[key]=res;
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    h.resize(n);
    for(int &x:h) cin>>x;
    // Case1
    m1_max = dp_case1(0,1, 0, false);
    // Case2
    // For case2, initial last is irrelevant, set to any value. Modify the dp_case2 function to handle initial state.
    // Implement similar to case1, but even positions are valleys
    // Modify dp_case2 to handle initial state without last constraint
    // Thus, in initial call, must_be_greater is false
    // Also, when parity is odd, no constraints
    // When parity is even, h[i] < last
    // To handle initial state where last is irrelevant, set last to a value that doesn't affect the first selection
    // Modify dp_case2 to ignore last when parity is odd
    // So initial last can be any, since parity=1 (odd), no constraint
    m2_max = dp_case2(0,1, 0, false);
    cout << max(m1_max, m2_max);
}