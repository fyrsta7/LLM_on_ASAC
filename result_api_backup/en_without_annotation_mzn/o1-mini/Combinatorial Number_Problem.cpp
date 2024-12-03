#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T, K;
    cin >> T >> K;
    vector<pair<int, int>> test_cases(T);
    int max_n = 0;
    for(int i=0;i<T;i++){
        cin >> test_cases[i].first >> test_cases[i].second;
        max_n = max(max_n, test_cases[i].first);
    }
    // Factorize K
    vector<pair<int, int>> factors;
    int x = K;
    for(int p=2; p*p <= x; p++){
        if(x % p == 0){
            int cnt = 0;
            while(x % p == 0){
                cnt++;
                x /= p;
            }
            factors.emplace_back(p, cnt);
        }
    }
    if(x > 1) factors.emplace_back(x, 1);
    int num_factors = factors.size();
    // Precompute F[f][i] for each factor
    vector<vector<int>> F(num_factors, vector<int>(max_n+1, 0));
    for(int f=0; f<num_factors; f++){
        int p = factors[f].first;
        for(int i=1;i<=max_n;i++){
            F[f][i] = F[f][i/p] + i/p;
        }
    }
    // Process each test case
    vector<int> answers(T, 0);
    for(int t=0; t<T; t++){
        int n = test_cases[t].first;
        int m = min(test_cases[t].second, n);
        int cnt = 0;
        for(int i=1;i<=n;i++){
            int lim = min(m, i);
            for(int j=1;j<=lim;j++){
                bool ok = true;
                for(int f=0; f<num_factors; f++){
                    int power = F[f][i] - F[f][j] - F[f][i-j];
                    if(power < factors[f].second){
                        ok = false;
                        break;
                    }
                }
                if(ok) cnt++;
            }
        }
        answers[t] = cnt;
    }
    // Output the answers
    for(int t=0; t<T; t++) cout << answers[t] << (t < T-1 ? " " : "\n");
}