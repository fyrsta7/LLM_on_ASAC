#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> number(n+1);
    for(int i=1;i<=n;i++) cin>>number[i];
    
    vector<vector<int>> colors(m+1);
    for(int i=1;i<=n;i++){
        int c;
        cin>>c;
        if(c >=1 && c <=m){
            colors[c].push_back(i);
        }
    }
    
    long long total =0;
    const int MOD =10007;
    for(int c=1; c<=m; c++){
        const vector<int> &list = colors[c];
        int k = list.size();
        if(k <2) continue;
        for(int j=0; j<k; j++){
            int y = list[j];
            for(int i=0; i<j; i++){
                int x = list[i];
                int z = 2*y -x;
                if(z > y && z <=n){
                    int pos = lower_bound(list.begin()+j+1, list.end(), z) - list.begin();
                    if(pos <k && list[pos] == z){
                        total = (total + ((long long)(x + z) * (number[x] + number[z])) ) % MOD;
                    }
                }
            }
        }
    }
    cout << total;
}