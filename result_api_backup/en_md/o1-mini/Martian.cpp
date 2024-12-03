#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool next_perm(vector<int> &P) {
    int N = P.size();
    if(N <=1 ) return false;
    int i = N - 2;
    while(i >=0 && P[i] >= P[i+1]) i--;
    if(i <0) return false;
    int j = N -1;
    while(P[j] <= P[i]) j--;
    swap(P[i], P[j]);
    reverse(P.begin()+i+1, P.end());
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    int M;
    cin >> M;
    vector<int> P(N);
    for(int &x: P) cin >> x;
    for(int i=0;i<M;i++) {
        next_perm(P);
    }
    for(int i=0;i<N;i++){
        if(i>0) cout << ' ';
        cout << P[i];
    }
    return 0;
}