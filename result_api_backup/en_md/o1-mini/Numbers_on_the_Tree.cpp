#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> number_on_node(n+1, 0); // node 1..n
        vector<int> node_of_number(n+1, 0); // number 1..n
        for(int i=1;i<=n;i++){
            int p;
            cin>>p;
            number_on_node[p]=i;
            node_of_number[i]=p;
        }
        vector<vector<int>> adj(n+1, vector<int>());
        for(int i=0;i<n-1;i++){
            int x,y;
            cin>>x>>y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        // Sort adjacency lists
        for(int i=1;i<=n;i++) sort(adj[i].begin(), adj[i].end());
        // DFS post-order
        vector<int> parent(n+1, 0);
        vector<int> order;
        // Stack for iterative DFS
        vector<pair<int, bool>> stack_dfs;
        stack_dfs.emplace_back(1, false);
        while(!stack_dfs.empty()){
            auto [u, processed] = stack_dfs.back();
            stack_dfs.pop_back();
            if(u == 0) continue;
            if(!processed){
                stack_dfs.emplace_back(u, true);
                for(auto it = adj[u].rbegin(); it != adj[u].rend(); it++) {
                    if(*it != parent[u]){
                        parent[*it]=u;
                        stack_dfs.emplace_back(*it, false);
                    }
                }
            }
            else{
                order.push_back(u);
            }
        }
        // Perform swaps
        for(auto u: order){
            if(u ==1) continue;
            int p = parent[u];
            // Swap number_on_node[u] and number_on_node[p]
            int num_u = number_on_node[u];
            int num_p = number_on_node[p];
            swap(number_on_node[u], number_on_node[p]);
            node_of_number[num_u] = p;
            node_of_number[num_p] = u;
        }
        // Now, create P array
        // P[i] is the node where number i is located
        for(int i=1;i<=n;i++){
            cout<<node_of_number[i];
            if(i!=n) cout<<' ';
            else cout<<'\n';
        }
    }
}
