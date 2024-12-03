#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<string> expr_str(n);
    for(auto &s: expr_str) cin >> s;
    // Convert to expr_int
    vector<int> expr_int(n);
    for(int i=0;i<n;i++){
        if(expr_str[i] == "+") expr_int[i] = 1;
        else if(expr_str[i] == "*") expr_int[i] = 2;
        else if(expr_str[i] == "(") expr_int[i] = 3;
        else expr_int[i] = 4;
    }
    // Count symbols
    int symbol_count=0;
    for(int i=0;i<n;i++) if(expr_int[i]==1 || expr_int[i]==2) symbol_count++;
    int num_count = symbol_count +1;
    if(num_count > 20){
        // Prevent too large
        cout << 0;
        return 0;
    }
    // Get symbol locations
    vector<int> symbol_loc;
    for(int i=0;i<n;i++) if(expr_int[i]==1 || expr_int[i]==2) symbol_loc.push_back(i);
    // Compute bracket_num for each symbol
    auto get_bracket_num = [&](int loc) -> int{
        int cnt=0;
        for(int i=0;i<loc;i++) {
            if(expr_int[i]==3) cnt++;
            if(expr_int[i]==4) cnt--;
        }
        return cnt;
    };
    vector<pair<int, int>> symbols; // pair of (bracket_num, index)
    for(int i=0;i<symbol_count;i++) symbols.emplace_back(get_bracket_num(symbol_loc[i]), i);
    // Assign priority: higher bracket_num -> lower priority number
    sort(symbols.begin(), symbols.end(), [&](pair<int,int> a, pair<int,int> b) -> bool{
        if(a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });
    vector<int> priority(symbol_count);
    for(int i=0;i<symbol_count;i++) priority[symbols[i].second] = i;
    // Now iterate over all possible plans
    int max_plans = 1 << num_count;
    int count_plans = 0;
    for(int mask=0; mask < max_plans; mask++){
        // Assign numbers
        vector<int> numbers(num_count);
        for(int j=0; j<num_count; j++) numbers[j] = (mask & (1<<j)) ? 1 : 0;
        // Apply operations in priority order
        // Create a copy of numbers
        vector<int> current = numbers;
        bool valid = true;
        for(int p=0; p<symbol_count; p++){
            // Find the symbol with priority p
            int s = -1;
            for(int i=0;i<symbol_count;i++) if(priority[i]==p){
                s = i;
                break;
            }
            if(s == -1){ valid = false; break;}
            // Apply operation at symbol_loc[s]
            // Operation between current[s] and current[s+1]
            if(s >= current.size()-1){ valid = false; break;}
            if(expr_int[symbol_loc[s]] ==1){
                // Add
                current[s] = (current[s] || current[s+1]);
            }
            else{
                // Multiply
                current[s] = (current[s] && current[s+1]);
            }
            // Remove the s+1 element
            current.erase(current.begin()+s+1);
        }
        if(valid && current.size()==1 && current[0]==0){
            count_plans++;
        }
    }
    cout << (count_plans % 10007);
}