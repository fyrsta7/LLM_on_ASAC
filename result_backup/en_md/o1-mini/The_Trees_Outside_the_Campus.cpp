#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int l, m;
    cin >> l >> m;
    vector<bool> removed(l+1, false);
    for(int i=0;i<m;i++){
        int u, v;
        cin >> u >> v;
        int start = min(u, v);
        int end = max(u, v);
        if(start <0) start=0;
        if(end > l) end=l;
        for(int j=start; j<=end; j++) {
            removed[j] = true;
        }
    }
    int count =0;
    for(int i=0;i<=l;i++) if(!removed[i]) count++;
    cout << count;
}