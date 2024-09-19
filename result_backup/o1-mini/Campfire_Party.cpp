#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    // Adjacency list
    vector<vector<int>> adj(n+1, vector<int>());
    for(int i=1;i<=n;i++){
        int a, b;
        cin >> a >> b;
        adj[i].push_back(a);
        adj[i].push_back(b);
    }
    // Check if the graph is a single cycle
    vector<bool> visited(n+1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int count =1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(auto &v: adj[u]){
            if(!visited[v]){
                visited[v]=true;
                q.push(v);
                count++;
            }
        }
    }
    if(count !=n){
        cout << "-1";
        return 0;
    }
    // Traverse the cycle to get seating order
    vector<int> seating;
    seating.reserve(n);
    // To traverse, need to choose a direction
    // Start from 1, choose one neighbor, traverse
    // To avoid ambiguity, choose the first neighbor
    int start =1;
    seating.push_back(start);
    // To track previous node to prevent going back
    int prev = -1;
    int current = start;
    while(seating.size() <n){
        for(auto &neighbor: adj[current]){
            if(neighbor != prev){
                seating.push_back(neighbor);
                prev = current;
                current = neighbor;
                break;
            }
        }
    }
    // Now seating has the order
    // Compute k_i = (s_i - (i+1)) modn
    // Use 0-based indexing
    vector<int> count_k(n, 0);
    for(int i=0;i<n;i++){
        int si = seating[i];
        int desired = i+1;
        int k = (si - desired) % n;
        if(k <0) k +=n;
        count_k[k]++;
    }
    // Find the maximum count and its corresponding k
    int max_c=0;
    int k_max=0;
    for(int k=0;k<n;k++){
        if(count_k[k] > max_c){
            max_c = count_k[k];
            k_max =k;
        }
    }
    // Determine the cost
    if(max_c ==n){
        if(k_max ==0){
            cout << "0";
        }
        else{
            cout << n;
        }
    }
    else{
        cout << (n - max_c);
    }
}
