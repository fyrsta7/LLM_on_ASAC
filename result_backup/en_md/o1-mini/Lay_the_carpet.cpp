#include <iostream>
#include <vector>
using namespace std;

struct Carpet {
    long long a, b, g, k;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<Carpet> carpets(n);
    for(int i=0;i<n;i++) cin >> carpets[i].a >> carpets[i].b >> carpets[i].g >> carpets[i].k;
    long long x, y;
    cin >> x >> y;
    for(int i=n-1;i>=0;i--){
        if(x >= carpets[i].a && x <= carpets[i].a + carpets[i].g &&
           y >= carpets[i].b && y <= carpets[i].b + carpets[i].k){
            cout << (i+1);
            return 0;
        }
    }
    cout << "-1";
} 