#include<bits/stdc++.h>
using namespace std;

int main(){
    int s, t, w;
    cin >> s >> t >> w;
    string str;
    cin >> str;
    // Convert str to numeric
    vector<int> initial(w);
    for(int i=0;i<w;i++) initial[i] = str[i]-'a'+1;
    // Available numbers
    int n = t - s +1;
    vector<int> available;
    for(int i=0;i<n;i++) available.push_back(s + i);
    // Generate combinations in order
    vector<int> comb(w, 0);
    for(int i=0;i<w;i++) comb[i] = available[i];
    // Function to compare two combinations
    auto cmp = [&](const vector<int>& a, const vector<int>& b)->bool{
        for(int i=0;i<w;i++) {
            if(a[i] != b[i]) return a[i] < b[i];
        }
        return false;
    };
    // Find initial combination
    bool found=false;
    // Iterate through combinations
    // Calculate total combinations C(n,w)
    // Implement combination generator
    // Initialize first combination
    comb.assign(w, 0);
    for(int i=0;i<w;i++) comb[i] = available[i];
    // Iterate until find initial
    while(true){
        if(cmp(comb, initial)==false && cmp(initial, comb)==false){
            found=true;
            break;
        }
        // Generate next combination
        int i;
        for(i=w-1;i>=0;i--){
            if(comb[i] < available[n - w + i]){
                comb[i]++;
                for(int j=i+1;j<w;j++) comb[j] = comb[j-1]+1;
                break;
            }
            if(i==0){
                break;
            }
        }
        if(i <0) break;
    }
    // Now generate next 5 combinations
    vector<vector<int>> results;
    for(int count=0; count<5; count++){
        // Generate next combination
        int i;
        for(i=w-1;i>=0;i--){
            if(comb[i] < available[n - w + i]){
                comb[i]++;
                for(int j=i+1;j<w;j++) comb[j] = comb[j-1]+1;
                break;
            }
            if(i==0){
                break;
            }
        }
        if(i <0){
            break;
        }
        results.push_back(comb);
    }
    // Output results
    for(auto &c : results){
        string out="";
        for(auto num : c){
            out += ('a' + num -1);
        }
        cout << out << "\n";
    }
}