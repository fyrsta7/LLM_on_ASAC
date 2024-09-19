#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef long long ll;

struct Node {
    int val;
    int left;
    int right;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> val(n + 1);
    for(int i=1;i<=n;i++) cin >> val[i];
    vector<int> left(n +1, -1);
    vector<int> right(n +1, -1);
    for(int i=1;i<=n;i++){
        cin >> left[i] >> right[i];
    }
    // Constants for hashing
    const ll A1 = 1000003;
    const ll B1 = 1000033;
    const ll C1 = 1000037;
    const ll A2 = 1000000007;
    const ll B2 = 1000003;
    const ll C2 = 1000033;
    // Arrays to store hashes and sizes
    vector<ll> hash1_normal(n+1, 0);
    vector<ll> hash1_mirror(n+1, 0);
    vector<ll> hash2_normal(n+1, 0);
    vector<ll> hash2_mirror(n+1, 0);
    vector<int> size_node(n+1, 1);
    // Stack for iterative post-order: pair(node, visited)
    stack<pair<int, bool>> st;
    st.emplace(1, false);
    // Initialize max_size
    int max_size =1;
    while(!st.empty()){
        pair<int, bool> current = st.top();
        st.pop();
        int node = current.first;
        bool visited = current.second;
        if(node == -1) continue;
        if(!visited){
            st.emplace(node, true);
            if(right[node]!=-1) st.emplace(right[node], false);
            if(left[node]!=-1) st.emplace(left[node], false);
        }
        else{
            // Process node
            int l = left[node];
            int r = right[node];
            // Compute size
            int size_l = (l != -1) ? size_node[l] : 0;
            int size_r = (r != -1) ? size_node[r] : 0;
            size_node[node] = size_l + size_r +1;
            // Compute hashes
            // For normal
            ll hn1 = val[node];
            ll hn2 = val[node];
            if(l != -1){
                hn1 = hn1 * A1 + hash1_normal[l] * B1 + hash1_normal[l] * C1;
                hn2 = hn2 * A2 + hash2_normal[l] * B2 + hash2_normal[l] * C2;
            }
            else{
                hn1 = hn1 * A1;
                hn2 = hn2 * A2;
            }
            if(r != -1){
                hn1 = hn1 + hash1_normal[r];
                hn2 = hn2 + hash2_normal[r];
            }
            hash1_normal[node] = hn1;
            hash2_normal[node] = hn2;
            // For mirror
            ll hm1 = val[node];
            ll hm2 = val[node];
            if(r != -1){
                hm1 = hm1 * A1 + hash1_mirror[r] * B1 + hash1_mirror[r] * C1;
                hm2 = hm2 * A2 + hash2_mirror[r] * B2 + hash2_mirror[r] * C2;
            }
            else{
                hm1 = hm1 * A1;
                hm2 = hm2 * A2;
            }
            if(l != -1){
                hm1 = hm1 + hash1_mirror[l];
                hm2 = hm2 + hash2_mirror[l];
            }
            hash1_mirror[node] = hm1;
            hash2_mirror[node] = hm2;
            // Check symmetry
            if(hash1_normal[node] == hash1_mirror[node] && hash2_normal[node] == hash2_mirror[node]){
                if(size_node[node] > max_size){
                    max_size = size_node[node];
                }
            }
        }
    }
    cout << max_size;
}
