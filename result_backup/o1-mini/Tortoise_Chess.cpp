#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX_C = 40;
const int INF = -1000000000;

int a[351];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    for(int i=1;i<=N;i++) cin >> a[i];
    vector<int> b(M);
    int c1_max=0, c2_max=0, c3_max=0, c4_max=0;
    for(int i=0;i<M;i++){
        cin >> b[i];
        if(b[i]==1) c1_max++;
        else if(b[i]==2) c2_max++;
        else if(b[i]==3) c3_max++;
        else if(b[i]==4) c4_max++;
    }
    // Initialize DP
    // dp[c1][c2][c3][c4]
    // To handle large memory, use a 1D array
    long long size = (long long)(c1_max+1)*(c2_max+1)*(c3_max+1)*(c4_max+1);
    vector<int> dp_table(size, INF);
    // Calculate base multipliers
    long long base1 =1;
    long long base2 = c1_max+1;
    long long base3 = base2*(c2_max+1);
    long long base4 = base3*(c3_max+1);
    // Function to compute index
    auto get_index = [&](int c1, int c2, int c3, int c4) -> long long{
        return c1 + c2 * base2 + c3 * base3 + c4 * base4;
    };
    // Initialize
    dp_table[get_index(0,0,0,0)] = a[1];
    // Iterate over counts
    for(int c4=0; c4 <=c4_max; c4++){
        for(int c3=0; c3 <=c3_max; c3++){
            for(int c2=0; c2 <=c2_max; c2++){
                for(int c1=0; c1 <=c1_max; c1++){
                    long long idx = get_index(c1, c2, c3, c4);
                    if(dp_table[idx]==INF) continue;
                    int pos = 1 + c1*1 + c2*2 + c3*3 + c4*4;
                    for(int s=1; s<=4; s++){
                        if(s==1 && c1 < c1_max){
                            int pos_new = pos +1;
                            if(pos_new >N) continue;
                            int new_c1 = c1 +1;
                            long long new_idx = get_index(new_c1, c2, c3, c4);
                            dp_table[new_idx] = max(dp_table[new_idx], dp_table[idx] + a[pos_new]);
                        }
                        if(s==2 && c2 < c2_max){
                            int pos_new = pos +2;
                            if(pos_new >N) continue;
                            int new_c2 = c2 +1;
                            long long new_idx = get_index(c1, new_c2, c3, c4);
                            dp_table[new_idx] = max(dp_table[new_idx], dp_table[idx] + a[pos_new]);
                        }
                        if(s==3 && c3 < c3_max){
                            int pos_new = pos +3;
                            if(pos_new >N) continue;
                            int new_c3 = c3 +1;
                            long long new_idx = get_index(c1, c2, new_c3, c4);
                            dp_table[new_idx] = max(dp_table[new_idx], dp_table[idx] + a[pos_new]);
                        }
                        if(s==4 && c4 < c4_max){
                            int pos_new = pos +4;
                            if(pos_new >N) continue;
                            int new_c4 = c4 +1;
                            long long new_idx = get_index(c1, c2, c3, new_c4);
                            dp_table[new_idx] = max(dp_table[new_idx], dp_table[idx] + a[pos_new]);
                        }
                    }
                }
            }
        }
    }
    // Find the maximum score where pos ==N and c1+c2+c3+c4 ==M
    int max_score = INF;
    for(int c4=0; c4 <=c4_max; c4++){
        for(int c3=0; c3 <=c3_max; c3++){
            for(int c2=0; c2 <=c2_max; c2++){
                for(int c1=0; c1 <=c1_max; c1++){
                    if(c1 + c2 + c3 + c4 != M) continue;
                    int pos = 1 + c1*1 + c2*2 + c3*3 + c4*4;
                    if(pos != N) continue;
                    long long idx = get_index(c1, c2, c3, c4);
                    if(dp_table[idx] > max_score){
                        max_score = dp_table[idx];
                    }
                }
            }
        }
    }
    cout << max_score;
}