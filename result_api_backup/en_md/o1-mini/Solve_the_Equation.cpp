#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct BigInt {
    bool negative;
    vector<int> digits; // least significant first, base 1e9

    BigInt() : negative(false), digits(1, 0) {}

    void fromString(const string &s) {
        negative = false;
        digits.clear();
        int pos = 0;
        if(s[0] == '-') {
            negative = true;
            pos = 1;
        }
        else if(s[0] == '+') {
            pos = 1;
        }
        string num = s.substr(pos);
        int len = num.length();
        for(int i = len; i > 0; i -= 9) {
            int start = max(0, i-9);
            int l = i - start;
            string part = num.substr(start, l);
            digits.push_back(stoi(part));
        }
        trim();
    }

    void trim() {
        while(digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
        if(digits.size() == 1 && digits[0] == 0)
            negative = false;
    }

    int abs_compare(const BigInt &other) const {
        if(digits.size() != other.digits.size())
            return digits.size() > other.digits.size() ? 1 : -1;
        for(int i = digits.size()-1; i >=0; i--) {
            if(digits[i] != other.digits[i])
                return digits[i] > other.digits[i] ? 1 : -1;
        }
        return 0;
    }

    BigInt abs_add(const BigInt &other) const {
        BigInt res;
        res.negative = false;
        int carry = 0;
        int n = max(digits.size(), other.digits.size());
        for(int i = 0; i < n; i++) {
            long long s = carry;
            if(i < digits.size()) s += digits[i];
            if(i < other.digits.size()) s += other.digits[i];
            res.digits.push_back(s % 1000000000);
            carry = s / 1000000000;
        }
        if(carry)
            res.digits.push_back(carry);
        return res;
    }

    BigInt abs_sub(const BigInt &other) const {
        BigInt res;
        res.negative = false;
        int carry = 0;
        for(int i = 0; i < digits.size(); i++) {
            long long s = digits[i] - carry - (i < other.digits.size() ? other.digits[i] : 0);
            if(s < 0) {
                s += 1000000000;
                carry = 1;
            }
            else {
                carry = 0;
            }
            res.digits.push_back(s);
        }
        res.trim();
        return res;
    }

    void add(const BigInt &other) {
        if(negative == other.negative) {
            BigInt sum = this->abs_add(other);
            *this = sum;
            this->negative = negative;
        }
        else {
            if(this->abs_compare(other) >= 0) {
                BigInt diff = this->abs_sub(other);
                *this = diff;
                this->negative = negative;
            }
            else {
                BigInt diff = other.abs_sub(*this);
                *this = diff;
                this->negative = other.negative;
            }
        }
    }

    void multiply(int x) {
        if(x < 0) {
            negative = !negative;
            x = -x;
        }
        long long carry = 0;
        for(int i = 0; i < digits.size(); i++) {
            long long tmp = (long long)digits[i] * x + carry;
            digits[i] = tmp % 1000000000;
            carry = tmp / 1000000000;
        }
        while(carry > 0) {
            digits.push_back(carry % 1000000000);
            carry /= 1000000000;
        }
        trim();
    }

    bool is_zero() const {
        return digits.size() ==1 && digits[0] ==0;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    long long m;
    cin >> n >> m;
    vector<string> a_str(n+1);
    for(int i=0;i<=n;i++) {
        cin >> a_str[i];
    }
    // Convert all a_i to BigInt
    vector<BigInt> a(n+1, BigInt());
    for(int i=0;i<=n;i++) {
        a[i].fromString(a_str[i]);
    }
    vector<int> solutions;
    for(long long x=1; x<=m; x++) {
        BigInt value = a[n];
        for(int i=n-1;i>=0;i--){
            value.multiply(x);
            value.add(a[i]);
        }
        if(value.is_zero()) {
            solutions.push_back(x);
        }
    }
    cout << solutions.size() << "\n";
    for(auto x: solutions)
        cout << x << "\n";
}