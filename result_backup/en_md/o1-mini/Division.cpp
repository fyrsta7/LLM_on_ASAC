#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

// Function to convert unsigned __int128 to string
string uint128_to_string(unsigned __int128 num) {
    if (num == 0) return "0";
    string s = "";
    while (num > 0) {
        char c = '0' + (num % 10);
        s = c + s;
        num /= 10;
    }
    return s;
}

struct Segment {
    int p;
    int l;
    int r;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long n, type;
    cin >> n >> type;
    vector<long long> a;
    // We'll use a stack to store segment sums
    vector<unsigned long long> stack_segments;
    stack_segments.reserve(n); // Reserve space to avoid reallocations
    if(type == 0){
        // Read n a_i's
        for(long long i=0;i<n;i++){
            long long ai;
            cin >> ai;
            // Push ai to stack
            stack_segments.push_back(ai);
            // Merge while the last two segments are not non-decreasing
            while(stack_segments.size() >=2 ){
                unsigned long long last = stack_segments[stack_segments.size()-1];
                unsigned long long second_last = stack_segments[stack_segments.size()-2];
                if(second_last > last){
                    // Merge them
                    stack_segments.pop_back();
                    stack_segments.pop_back();
                    stack_segments.push_back(second_last + last);
                }
                else{
                    break;
                }
            }
        }
    }
    else{
        // type ==1
        long long x, y, z, b1, b2, m;
        cin >> x >> y >> z >> b1 >> b2 >> m;
        vector<Segment> segments(m);
        for(long long i=0;i<m;i++){
            cin >> segments[i].p >> segments[i].l >> segments[i].r;
        }
        // Now generate a_i's on the fly
        // Initialize b1 and b2
        unsigned long long b_prev2 = b1;
        unsigned long long b_prev1 = b2;
        long long current_segment =0;
        for(long long i=1;i<=n;i++){
            long long ai;
            if(current_segment < m && i <= segments[current_segment].p){
                if(i ==1){
                    ai = b_prev2;
                }
                else if(i ==2){
                    ai = b_prev1;
                }
                else{
                    unsigned long long b_i = (x * b_prev1 + y * b_prev2 + z) & ((1ULL<<30) -1);
                    b_prev2 = b_prev1;
                    b_prev1 = b_i;
                    ai = b_i;
                }
                ai = (ai % (segments[current_segment].r - segments[current_segment].l +1)) + segments[current_segment].l;
            }
            else{
                current_segment++;
                // Generate b_i
                unsigned long long b_i = (x * b_prev1 + y * b_prev2 + z) & ((1ULL<<30) -1);
                b_prev2 = b_prev1;
                b_prev1 = b_i;
                ai = (b_i % (segments[current_segment].r - segments[current_segment].l +1)) + segments[current_segment].l;
            }
            // Push ai to stack
            stack_segments.push_back(ai);
            // Merge while the last two segments are not non-decreasing
            while(stack_segments.size() >=2 ){
                unsigned long long last = stack_segments[stack_segments.size()-1];
                unsigned long long second_last = stack_segments[stack_segments.size()-2];
                if(second_last > last){
                    // Merge them
                    stack_segments.pop_back();
                    stack_segments.pop_back();
                    stack_segments.push_back(second_last + last);
                }
                else{
                    break;
                }
            }
        }
    }
    // Now compute the sum of squares
    unsigned __int128 total =0;
    for(auto &s: stack_segments){
        unsigned __int128 sq = (unsigned __int128)s * (unsigned __int128)s;
        total += sq;
    }
    // Output the total
    cout << uint128_to_string(total) << "\n";
}