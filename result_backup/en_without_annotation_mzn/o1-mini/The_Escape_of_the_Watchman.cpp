#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long M, S, T;
    cin >> M >> S >> T;
    // Maximum possible mana
    long long max_mana = M + 4*T +10;
    // Initialize current state
    vector<long long> current(max_mana+1, -1);
    if(M <= max_mana)
        current[M] =0;
    // To track min_time
    long long min_time = -1;
    for(long long step=1; step<=T; step++){
        vector<long long> next(max_mana+1, -1);
        for(long long m=0; m<=max_mana; m++){
            if(current[m] == -1) continue;
            // Action run
            long long m_run = m;
            long long d_run = current[m] +17;
            if(d_run > next[m_run]){
                next[m_run]=d_run;
            }
            // Action flash
            if(m >=10){
                long long m_flash = m -10;
                long long d_flash = current[m] +60;
                if(d_flash > next[m_flash]){
                    next[m_flash]=d_flash;
                }
            }
            // Action rest
            long long m_rest = m +4;
            if(m_rest > max_mana) m_rest = max_mana;
            long long d_rest = current[m];
            if(d_rest > next[m_rest]){
                next[m_rest]=d_rest;
            }
        }
        // Check for reaching S
        bool reached = false;
        for(long long m=0; m<=max_mana; m++) {
            if(next[m] >= S){
                if(min_time == -1){
                    min_time = step;
                }
            }
        }
        current = move(next);
    }
    if(min_time != -1 && min_time <=T){
        cout << "Yes\n" << min_time;
    }
    else{
        // Find max_dis
        long long max_dis =0;
        for(auto d: current){
            if(d > max_dis){
                max_dis =d;
            }
        }
        cout << "No\n" << max_dis;
    }
}