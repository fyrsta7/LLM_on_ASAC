#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, m, q, u, v, t;
    cin >> n >> m >> q >> u >> v >> t;
    priority_queue<ll> heap;
    ll ai;
    for(ll i=0;i<n;i++){
        cin >> ai;
        heap.push(ai);
    }
    vector<ll> cut_results;
    ll add = 0;
    for(ll step=1; step<=m; step++){
        if(heap.empty()){
            // If no worms to cut, skip
            if(step % t == 0){
                // No cut, nothing to record
            }
            add += q;
            continue;
        }
        ll s = heap.top();
        ll x = s + add;
        if(step % t ==0){
            cut_results.push_back(x);
        }
        heap.pop();
        ll l = (u * x) / v;
        ll r = x - l;
        heap.push(l - add);
        heap.push(r - add);
        add += q;
    }
    // Collect all lengths
    vector<ll> all_lengths;
    all_lengths.reserve(n + m);
    while(!heap.empty()){
        ll s = heap.top();
        heap.pop();
        all_lengths.push_back(s + add);
    }
    // Sort descending
    sort(all_lengths.begin(), all_lengths.end(), [&](const ll a, const ll b) -> bool{
        return a > b;
    });
    // Collect output lengths
    vector<ll> output_lengths;
    if(t <= all_lengths.size()){
        for(ll i = t-1; i < all_lengths.size(); i += t){
            output_lengths.push_back(all_lengths[i]);
        }
    }
    // Output first line
    if(cut_results.empty()){
        cout << "\n";
    }
    else{
        for(ll i=0;i<cut_results.size();i++){
            if(i>0) cout << ' ';
            cout << cut_results[i];
        }
        cout << '\n';
    }
    // Output second line
    if(output_lengths.empty()){
        cout << "\n";
    }
    else{
        for(ll i=0;i<output_lengths.size();i++){
            if(i>0) cout << ' ';
            cout << output_lengths[i];
        }
        cout << '\n';
    }
}