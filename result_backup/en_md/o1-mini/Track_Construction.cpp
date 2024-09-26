#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

struct Edge {
    int to;
    int length;
};

int n, m;
vector<vector<Edge>> adj;
ll total = 0;

int dfs(int u, int parent, ll target, int& count) {
    ll current = 0;
    for(auto &edge: adj[u]){
        int v = edge.to;
        if(v == parent) continue;
        ll res = dfs(v, u, target, count);
        if(res + edge.length >= target){
            count++;
        }
        else{
            current = max(current, res + edge.length);
        }
    }
    return current;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    adj.resize(n+1);
    for(int i=0;i<n-1;i++){
        int a, b, l;
        cin >> a >> b >> l;
        adj[a].push_back(Edge{b, (int)l});
        adj[b].push_back(Edge{a, (int)l});
        total += l;
    }
    ll left = 1, right = total, answer = 0;
    while(left <= right){
        ll mid = left + (right - left)/2;
        int cnt = 0;
        dfs(1, -1, mid, cnt);
        if(cnt >= m){
            answer = mid;
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    cout << answer;
}