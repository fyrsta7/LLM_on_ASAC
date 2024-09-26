#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// Function to add two numeric strings
string add_strings(const string& a, const string& b) {
    string res = "";
    int carry = 0;
    int n = a.size();
    int m = b.size();
    int i = n -1;
    int j = m -1;
    while(i >=0 || j >=0 || carry) {
        int digit_a = (i >=0) ? a[i]-'0' : 0;
        int digit_b = (j >=0) ? b[j]-'0' : 0;
        int total = digit_a + digit_b + carry;
        carry = total /10;
        res += (total %10) + '0';
        i--;
        j--;
    }
    reverse(res.begin(), res.end());
    // Remove leading zeros
    size_t start = res.find_first_not_of('0');
    if(start == string::npos) return "0";
    return res.substr(start);
}

int main(){
    int k;
    long long w;
    cin>>k>>w;
    int max_n = (1<<k) -1;
    // Initialize C[n][m]
    int N = max_n;
    vector<vector<string>> C(N+1, vector<string>(N+1, "0"));
    for(int n=0;n<=N;n++) {
        C[n][0] = "1";
        C[n][n] = "1";
    }
    for(int n=1;n<=N;n++) {
        for(int m=1;m<n;m++) {
            C[n][m] = add_strings(C[n-1][m], C[n-1][m-1]);
        }
    }
    // Initialize total sum
    string total = "0";
    // Iterate over l
    for(int l=1;l<=k;l++) {
        // Check if 2^(l-1) fits in k bits
        if(l<1 || l>k) continue;
        // Compute 2^(l-1) and 2^l
        int lower = 1 << (l-1);
        int upper = (l < k) ? (1<<l) -1 : (1<<k)-1;
        // Iterate over m
        // m >=2
        // l + (m-1)*k <=w
        long long max_m = (w >= l) ? ((w - l)/k +1) : 1;
        max_m = min((long long)N, max_m);
        for(long long m=2; m<=max_m; m++) {
            if(l + (m-1)*((long long)k) >w) break;
            // Sum over d1=lower to upper
            string sum = "0";
            for(int d1=lower; d1<=upper; d1++) {
                int remaining = max_n - d1;
                if(remaining >= m-1) {
                    sum = add_strings(sum, C[remaining][m-1]);
                }
            }
            // Add sum to total
            total = add_strings(total, sum);
        }
    }
    cout<<total;
}
