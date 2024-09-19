#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int main(){
    int n;
    cin >> n;
    // Matchstick counts for digits 0-9
    int digit_match[10] = {6,2,5,5,4,5,6,3,7,6};
    
    // Function to compute matchsticks for a number
    auto get_match = [&](int num) -> int {
        if(num ==0) return digit_match[0];
        int cnt=0;
        while(num >0){
            cnt += digit_match[num%10];
            num /=10;
        }
        return cnt;
    };
    
    // Precompute matchsticks for all possible numbers
    // Max matchstick per number is up to 20, so max digits up to 10
    // But n<=24, so C = A + B <= some limit
    // Let's set max number to 10000
    int MAX = 10000;
    vector<int> match(MAX*2 +1, 0);
    for(int i=0;i<=MAX*2;i++) {
        if(i <= MAX){
            match[i] = get_match(i);
        }
    }
    
    // To store numbers by their matchstick counts
    unordered_map<int, vector<int>> match_map;
    for(int i=0;i<=MAX;i++){
        int m = get_match(i);
        if(m +4 >n) continue; // minimum to add + and =
        match_map[m].push_back(i);
    }
    
    int count =0;
    for(int a=0;a<=MAX;a++){
        int ma = get_match(a);
        if(ma +4 >n) continue;
        for(int b=0;b<=MAX;b++){
            int mb = get_match(b);
            if(ma + mb +4 >n) continue;
            int c = a + b;
            if(c > MAX*2) continue;
            int mc = match[c];
            if(ma + mb + mc +4 ==n){
                // Check no leading zeros
                auto valid = [&](int num) -> bool {
                    if(num ==0) return true;
                    string s = to_string(num);
                    return s[0] != '0';
                };
                if(valid(a) && valid(b) && valid(c)){
                    if(a != b){
                        count +=2;
                    }
                    else{
                        count +=1;
                    }
                }
            }
        }
    }
    cout << count;
}