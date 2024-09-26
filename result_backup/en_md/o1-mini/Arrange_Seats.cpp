#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int M, N, K, L, D;
    cin >> M >> N >> K >> L >> D;
    // Initialize counts
    vector<int> H_counts(M, 0); // 1 to M-1
    vector<int> V_counts(N, 0); // 1 to N-1
    for(int i=0;i<D;i++){
        int Xi, Yi, Pi, Qi;
        cin >> Xi >> Yi >> Pi >> Qi;
        if(Xi == Pi){
            // Horizontal adjacency, between columns min(Yi,Qi)
            int y = min(Yi, Qi);
            V_counts[y]++;
        }
        else{
            // Vertical adjacency, between rows min(Xi, Pi)
            int x = min(Xi, Pi);
            H_counts[x]++;
        }
    }
    // Prepare horizontal channels
    vector<pair<int, int>> H_list;
    for(int b=1; b<=M-1; b++){
        H_list.emplace_back(-H_counts[b], b);
    }
    sort(H_list.begin(), H_list.end());
    vector<int> selected_H;
    for(int i=0; i<K && i < H_list.size(); i++) selected_H.push_back(H_list[i].second);
    sort(selected_H.begin(), selected_H.end());
    // Prepare vertical channels
    vector<pair<int, int>> V_list;
    for(int a=1; a<=N-1; a++){
        V_list.emplace_back(-V_counts[a], a);
    }
    sort(V_list.begin(), V_list.end());
    vector<int> selected_V;
    for(int i=0; i<L && i < V_list.size(); i++) selected_V.push_back(V_list[i].second);
    sort(selected_V.begin(), selected_V.end());
    // Output horizontal channels
    if(K >0){
        for(int i=0;i<selected_H.size();i++){
            if(i>0) cout << ' ';
            cout << selected_H[i];
        }
    }
    cout << '\n';
    // Output vertical channels
    if(L >0){
        for(int i=0;i<selected_V.size();i++){
            if(i>0) cout << ' ';
            cout << selected_V[i];
        }
    }
    cout << '\n';
}