#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Function to map (a_i, b_i) to rank index
int map_a_b_to_rank(int a, int b){
    if(a == 0){
        if(b ==1) return 13; // black joker
        else return 14; // red joker
    }
    if(a ==1) return 11; // A
    if(a ==2) return 12; //2
    if(a >=3 && a <=10) return a-3; //3-10 mapped to 0-7
    if(a ==11) return 8; // J
    if(a ==12) return 9; // Q
    if(a ==13) return 10; // K
    // Should not reach here
    return -1;
}

// Function to encode counts to a unique index
ll encode_counts(int counts[15]){
    ll index =0;
    for(int i=0;i<=12;i++){
        index = index *5 + counts[i];
    }
    index = index *2 + counts[13];
    index = index *2 + counts[14];
    return index;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T, n;
    cin >> T >> n;
    
    // Precompute possible straight start and lengths
    // Straights can start from rank 0 to rank 11-4=7, lengths from5 to up to 12-start
    // But straights only include ranks 0 to10 (3 to K)
    // According to standard Doudizhu, straights do not include A,2, jokers
    // But sample includes A, so assume straights can include up to A (rank11)
    // So start from 0 to11-4=7, lengths from5 to up to12- start
    
    // To store all possible straights as pairs of (start, length)
    vector<pair<int, int>> straights;
    for(int start=0; start<=11-4; start++){
        for(int len=5; len<= (12 - start); len++){
            straights.emplace_back(make_pair(start, len));
        }
    }
    
    while(T--){
        int a, b;
        int counts[15];
        memset(counts, 0, sizeof(counts));
        for(int i=0;i<n;i++){
            cin >> a >> b;
            int rank = map_a_b_to_rank(a, b);
            if(rank != -1){
                counts[rank]++;
                // Ensure counts do not exceed limits
                if(rank <=12){
                    counts[rank] = min(counts[rank], 4);
                }
                else{
                    counts[rank] = min(counts[rank], 1);
                }
            }
        }
        // Encode initial state
        ll initial = encode_counts(counts);
        // BFS
        // Use unordered_set for visited
        // To speed up, use a bitmap with a precomputed size
        // 5^13 *4 ~ 4.89e9, use a bitmask stored in a vector<char>
        // Each byte has 8 bits
        // Total bytes needed: ceil(4.89e9 /8) = ~612MB
        // To avoid memory issues, use a hash set instead
        // Implement a visited hash using a vector<bool> with dynamic allocation
        // But it's too large, so use a std::unordered_set with a custom hash
        // Alternatively, use a bitset with limited size and accept some collisions
        // Here, use a std::unordered_set with reserve
        // But to speed up, use a queue and a bitmap stored as a vector of bytes
        // Allocate bitmap
        // To avoid using too much memory, use a bitset only for states visited in this test case
        // Implement a bitmap with dynamic allocation
        // Here, proceed with a std::vector<char>
        // Define maximum index
        // 5^13 *4 = 1220703125 *4 = 4882812500
        // Which requires 4882812500 /8 = 610351562 bytes
        // It is too much for C++ in practice, so use a hash set
        // Implement visited as an unordered_set
        unordered_set<ll> visited;
        queue<ll> q;
        q.push(initial);
        visited.insert(initial);
        int steps=0;
        bool found=false;
        while(!q.empty()){
            int sz = q.size();
            for(int i=0;i<sz;i++){
                ll current = q.front(); q.pop();
                // Decode current to counts
                int current_counts[15];
                ll tmp = current;
                for(int j=14; j>=0; j--){
                    if(j ==14 || j ==13){
                        current_counts[j] = tmp %2;
                        tmp /=2;
                    }
                    else{
                        current_counts[j] = tmp %5;
                        tmp /=5;
                    }
                }
                // Check if all counts are zero
                bool all_zero=true;
                for(int j=0; j<15; j++) if(current_counts[j]!=0){all_zero=false; break;}
                if(all_zero){
                    cout << steps << "\n";
                    found=true;
                    break;
                }
                // Generate all possible groupings
                // 1. Singles
                for(int r=0; r<15; r++) {
                    if(current_counts[r] >=1){
                        int new_counts[15];
                        memcpy(new_counts, current_counts, sizeof(current_counts));
                        new_counts[r] -=1;
                        ll new_state =0;
                        for(int k=0; k<=12; k++) new_state = new_state *5 + new_counts[k];
                        new_state = new_state *2 + new_counts[13];
                        new_state = new_state *2 + new_counts[14];
                        if(!visited.count(new_state)){
                            visited.insert(new_state);
                            q.push(new_state);
                        }
                    }
                }
                // 2. Pairs
                for(int r=0; r<15; r++) {
                    if(current_counts[r] >=2){
                        int new_counts[15];
                        memcpy(new_counts, current_counts, sizeof(current_counts));
                        new_counts[r] -=2;
                        ll new_state =0;
                        for(int k=0; k<=12; k++) new_state = new_state *5 + new_counts[k];
                        new_state = new_state *2 + new_counts[13];
                        new_state = new_state *2 + new_counts[14];
                        if(!visited.count(new_state)){
                            visited.insert(new_state);
                            q.push(new_state);
                        }
                    }
                }
                //3. Straights
                for(auto &[start, len_max]: straights){
                    for(int len =5; len<=len_max; len++){
                        bool can = true;
                        for(int s = start; s < start + len; s++) {
                            if(s >=15 || current_counts[s] <1){
                                can=false;
                                break;
                            }
                        }
                        if(can){
                            int new_counts[15];
                            memcpy(new_counts, current_counts, sizeof(current_counts));
                            for(int s = start; s < start + len; s++) new_counts[s] -=1;
                            ll new_state =0;
                            for(int k=0; k<=12; k++) new_state = new_state *5 + new_counts[k];
                            new_state = new_state *2 + new_counts[13];
                            new_state = new_state *2 + new_counts[14];
                            if(!visited.count(new_state)){
                                visited.insert(new_state);
                                q.push(new_state);
                            }
                        }
                    }
                }
            }
            if(found) break;
            steps++;
        }
    }
}