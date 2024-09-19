#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> xi(m);
    for(int i=0; i<m; ++i){
        cin >> xi[i];
    }

    // freq[x]: number of items with magic value x
    vector<int> freq(n+1,0);
    for(int i=0; i<m; ++i){
        freq[xi[i]]++;
    }

    // Initialize counts
    vector<long long> cntA(n+1, 0);
    vector<long long> cntB(n+1, 0);
    vector<long long> cntC(n+1, 0);
    vector<long long> cntD(n+1, 0);

    for(int xa=1; xa<=n; xa++){
        int Sa = freq[xa];
        if(Sa ==0 ) continue;
        for(int xb=xa+2; xb<=n; xb+=2){
            int Sb = freq[xb];
            if(Sb ==0 ) continue;
            int delta = (xb - xa)/2;
            long long lower_c_candidate = 4LL * xb - 3LL * xa +1;
            int lower_c = max(xb +1, (int)lower_c_candidate);
            int upper_c = n - delta;
            if(lower_c > upper_c) continue;
            for(int xc=lower_c; xc<=upper_c; xc++){
                int xd = xc + delta;
                if(xd >n) continue;
                int Sc = freq[xc];
                if(Sc ==0 ) continue;
                int Sd = freq[xd];
                if(Sd ==0 ) continue;
                cntA[xa] += (long long)Sb * Sc * Sd;
                cntB[xb] += (long long)Sa * Sc * Sd;
                cntC[xc] += (long long)Sa * Sb * Sd;
                cntD[xd] += (long long)Sa * Sb * Sc;
            }
        }
    }

    for(int i=0; i<m; ++i){
        int x = xi[i];
        cout << cntA[x] << ' ' << cntB[x] << ' ' << cntC[x] << ' ' << cntD[x] << '\n';
    }

    return 0;
}