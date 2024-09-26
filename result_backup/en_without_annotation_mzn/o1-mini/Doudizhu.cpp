#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<pair<int, int>> cards(n);
        for(auto &p: cards) cin >> p.first >> p.second;
        // Precompute all valid subsets
        int N = n;
        int total = 1<<N;
        vector<bool> valid_subset(total, false);
        for(int mask=0; mask<total; mask++){
            int size = __builtin_popcount(mask);
            if(size ==0){
                valid_subset[mask] = true;
                continue;
            }
            // Collect ranks and types
            vector<int> ranks;
            vector<int> types;
            for(int i=0;i<N;i++) if(mask & (1<<i)){
                ranks.push_back(cards[i].first);
                types.push_back(cards[i].second);
            }
            // Count frequencies of ranks
            unordered_map<int, int> cnt;
            for(auto r: ranks) cnt[r]++;
            // Handle size 1
            if(size ==1){
                valid_subset[mask] = true;
                continue;
            }
            // Handle size 2
            if(size ==2){
                bool cond1 = false, cond2 = false;
                // Condition a: both have same rank and rank !=0
                if(ranks[0]==ranks[1] && ranks[0]!=0){
                    cond1 = true;
                }
                // Condition b: one has rank=0 and type=1, other rank=0 and type=2
                if((ranks[0]==0 && types[0]==1 && ranks[1]==0 && types[1]==2) ||
                   (ranks[1]==0 && types[1]==1 && ranks[0]==0 && types[0]==2)){
                    cond2 = true;
                }
                if(cond1 || cond2){
                    valid_subset[mask] = true;
                    continue;
                }
            }
            // Handle size 3
            if(size ==3){
                bool all_same = true;
                int first = ranks[0];
                for(auto r: ranks) if(r != first){
                    all_same = false;
                    break;
                }
                if(all_same){
                    valid_subset[mask] = true;
                    continue;
                }
            }
            // Handle size 4
            if(size ==4){
                // a. All four have same rank
                bool all_same = true;
                int first = ranks[0];
                for(auto r: ranks) if(r != first){
                    all_same = false;
                    break;
                }
                if(all_same){
                    valid_subset[mask] = true;
                    continue;
                }
                // b. Exists a rank with exactly three
                bool has_three = false;
                for(auto &[k,v]: cnt) if(v ==3){
                    has_three = true;
                    break;
                }
                if(has_three){
                    valid_subset[mask] = true;
                    continue;
                }
            }
            // Handle size 5
            if(size ==5){
                bool three = false, two = false;
                for(auto &[k,v]: cnt){
                    if(v ==3) three = true;
                    if(v ==2) two = true;
                }
                if(three && two){
                    valid_subset[mask] = true;
                    continue;
                }
            }
            // Handle size >=5 for straight
            if(size >=5){
                // Check for straight with count 1
                // Get unique ranks sorted
                vector<int> unique_ranks;
                for(auto &[k,v]: cnt) unique_ranks.push_back(k);
                sort(unique_ranks.begin(), unique_ranks.end());
                // Must have size unique_ranks and max - min +1 == size
                if((int)unique_ranks.size() == size){
                    int min_rank = unique_ranks[0];
                    int max_rank = unique_ranks.back();
                    if(max_rank - min_rank +1 == size){
                        bool straight = true;
                        for(int r = min_rank; r <= max_rank; r++) if(cnt[r]!=1){
                            straight = false;
                            break;
                        }
                        if(straight){
                            valid_subset[mask] = true;
                            continue;
                        }
                    }
                }
            }
            // Handle size >=6 and even for double straight
            if(size >=6 && size%2 ==0){
                int per =2;
                // Check if size/per is number of unique ranks and consecutive
                int groups = size / per;
                vector<int> unique_ranks;
                for(auto &[k,v]: cnt) unique_ranks.push_back(k);
                sort(unique_ranks.begin(), unique_ranks.end());
                if((int)unique_ranks.size() == groups){
                    int min_rank = unique_ranks[0];
                    int max_rank = unique_ranks.back();
                    if(max_rank - min_rank +1 == groups){
                        bool double_straight = true;
                        for(int r = min_rank; r <= max_rank; r++) if(cnt[r]!=per){
                            double_straight = false;
                            break;
                        }
                        if(double_straight){
                            valid_subset[mask] = true;
                            continue;
                        }
                    }
                }
            }
            // Handle size >=6 and divisible by3 for triple straight
            if(size >=6 && size%3 ==0){
                int per =3;
                int groups = size / per;
                vector<int> unique_ranks;
                for(auto &[k,v]: cnt) unique_ranks.push_back(k);
                sort(unique_ranks.begin(), unique_ranks.end());
                if((int)unique_ranks.size() == groups){
                    int min_rank = unique_ranks[0];
                    int max_rank = unique_ranks.back();
                    if(max_rank - min_rank +1 == groups){
                        bool triple_straight = true;
                        for(int r = min_rank; r <= max_rank; r++) if(cnt[r]!=per){
                            triple_straight = false;
                            break;
                        }
                        if(triple_straight){
                            valid_subset[mask] = true;
                            continue;
                        }
                    }
                }
            }
            // Handle size==6 for four of a kind
            if(size ==6){
                bool four = false;
                for(auto &[k,v]: cnt) if(v ==4){
                    four = true;
                    break;
                }
                if(four){
                    valid_subset[mask] = true;
                    continue;
                }
            }
            // Handle size==8 for 4,2,2
            if(size ==8){
                int cnt4=0, cnt2=0;
                for(auto &[k,v]: cnt){
                    if(v ==4) cnt4++;
                    if(v ==2) cnt2++;
                }
                if(cnt4 ==1 && cnt2 ==2){
                    valid_subset[mask] = true;
                    continue;
                }
            }
            valid_subset[mask] = false;
        }
        // DP to find minimal number of subsets
        int full = (1<<N)-1;
        vector<int> dp(full+1, N+1);
        dp[0] =0;
        for(int mask=0; mask<=full; mask++){
            if(dp[mask] == N+1) continue;
            // Iterate through all subsets
            for(int sub=mask^full; sub>0; sub = (sub-1) & (mask^full)){
                if(valid_subset[sub]){
                    if(dp[mask | sub] > dp[mask] +1){
                        dp[mask | sub] = dp[mask] +1;
                    }
                }
            }
        }
        cout << dp[full] << " ";
    }
    cout << "\n";
}
