#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    string s1, s2, sum;
    cin >> s1 >> s2 >> sum;
    
    map<char, int> mp;
    vector<int> num(n);
    string all = s1 + s2 + sum;
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    
    for (int i = 0; i < n; ++i) {
        mp[all[i]] = i;
    }
    
    int carry = 0;
    for (int i = n-1; i >= 0; --i) {
        int x = mp[s1[i]];
        int y = mp[s2[i]];
        int z = mp[sum[i]];
        int temp = x + y + carry;
        num[i] = temp % n;
        carry = temp / n;
    }
    
    for (int i = 0; i < n; ++i) {
        cout << num[i] << " ";
    }
    
    return 0;
}