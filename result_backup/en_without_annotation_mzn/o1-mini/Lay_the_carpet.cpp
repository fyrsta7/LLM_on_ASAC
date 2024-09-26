#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    struct Carpet{
        int x1, y1, w, h;
    };
    vector<Carpet> carpets(n);
    for(int i=0;i<n;i++) cin >> carpets[i].x1 >> carpets[i].y1 >> carpets[i].w >> carpets[i].h;
    int x, y;
    cin >> x >> y;
    int ans = -1;
    for(int i=0;i<n;i++){
        if(x >= carpets[i].x1 && y >= carpets[i].y1 && x <= carpets[i].x1 + carpets[i].w && y <= carpets[i].y1 + carpets[i].h){
            ans = i+1;
        }
    }
    cout << ans;
}