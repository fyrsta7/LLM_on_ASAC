#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 2000 + 10;

vector<int> adj[MAXN];     // adjacency list representation of the tree
int loc[MAXN];             // loc[i] is the node where number i is initially located
int result[MAXN];          // result array

void solve(int n) {
    // min-heap priority queue to process nodes in lexicographical order
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<bool> processed(n + 1, false); // keep track of processed nodes

    // Add all nodes to the priority queue
    for(int i = 1; i <= n; ++i) {
        pq.push(loc[i]);
    }

    // Perform n - 1 operations: always delete the edge connected to the smallest node available
    while(n > 1) {
        int minNode = pq.top();
        pq.pop();
        while(processed[minNode]) {
            minNode = pq.top();
            pq.pop();
        }
        
        // Find an unprocessed neighbor of minNode
        int neighbor = -1;
        for(int neighbour : adj[minNode]) {
            if(!processed[neighbour]) {
                neighbor = neighbour;
                break;
            }
        }

        if(neighbor == -1) break; // Should not happen in a valid tree

        // Swap locations
        swap(loc[minNode], loc[neighbor]);

        // Mark minNode as processed and remove corresponding adjacency
        processed[minNode] = true;
        adj[minNode].erase(remove(adj[minNode].begin(), adj[minNode].end(), neighbor), adj[minNode].end());
        adj[neighbor].erase(remove(adj[neighbor].begin(), adj[neighbor].end(), minNode), adj[neighbor].end());

        // Push neighbor back to the queue with its new value
        pq.push(neighbor);

        --n;
    }
}

int main() {
    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        for(int i = 1; i <= n; ++i) {
            adj[i].clear();
        }

        for(int i = 1; i <= n; ++i) {
            cin >> loc[i];
        }

        for(int i = 1; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            adj[x].emplace_back(y);
            adj[y].emplace_back(x);
        }

        solve(n);

        // Reorder the output array to print node numbers in order of values 1 to n
        for(int i = 1; i <= n; ++i) {
            result[loc[i]] = i;
        }

        for(int i = 1; i <= n; ++i) {
            cout << result[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
