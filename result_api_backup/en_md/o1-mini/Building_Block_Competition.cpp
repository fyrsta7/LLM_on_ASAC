#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> h(n);
    for(int &x: h) cin >> x;
    long long operations = h[0];
    for(int i=1;i<n;i++) {
        if(h[i] > h[i-1]) operations += h[i] - h[i-1];
    }
    cout << operations;
}