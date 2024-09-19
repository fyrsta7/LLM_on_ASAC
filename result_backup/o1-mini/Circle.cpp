#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

// Function to compute n mod m, where m is a power of 2
unsigned long long mod_pow2(const string& n_str, int e) {
    unsigned long long mod = 0;
    unsigned long long limit = (e >= 64) ? ~0ULL : ((1ULL << e) - 1);
    for(char c : n_str){
        mod = (mod * 2 + (c - '0')) % (1ULL << min(e, 60));
    }
    if(e >= 64){
        // For e >=64, return mod as much as possible, though it won't hold full e bits
        return mod;
    }
    return mod & ((1ULL << e) -1);
}

// Function to compute n mod m, where m is a power of 5
unsigned long long mod_pow5(const string& n_str, int e){
    unsigned long long mod =0;
    unsigned long long power5=1;
    for(int i=0;i<e;i++) power5 *=5;
    for(char c : n_str){
        mod = (mod * 10 + (c - '0')) % power5;
    }
    return mod;
}

// Function to compute gcd of two numbers
unsigned long long gcd_func(unsigned long long a, unsigned long long b){
    while(b){
        unsigned long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Function to list all divisors of n, assuming n = 2^x *5^y
vector<unsigned long long> list_divisors_p5(int e){
    // phi = 4 * 5^(e-1)
    // divisors are 2^a *5^b where a=0,1,2 and b=0..e-1
    vector<unsigned long long> divisors;
    for(int a=0;a<=2;a++){
        unsigned long long factor2 = 1;
        for(int i=0;i<a;i++) factor2 *=2;
        for(int b=0;b<=e-1;b++){
            unsigned long long factor5 =1;
            for(int j=0;j<b;j++) factor5 *=5;
            divisors.push_back(factor2 * factor5);
        }
    }
    sort(divisors.begin(), divisors.end());
    return divisors;
}

// Function to list all divisors of phi=2^(e-1)
vector<unsigned long long> list_divisors_p2(int e){
    vector<unsigned long long> divisors;
    unsigned long long phi = 1ULL << (e-1);
    unsigned long long d =1;
    while(d <= phi){
        divisors.push_back(d);
        d *=2;
    }
    return divisors;
}

// Function to compute power mod for p=2^e using __int128
unsigned long long powmod_p2(unsigned long long base, unsigned long long exponent, int e){
    __int128 mask;
    if(e >=64){
        mask = ((__int128)1 << e) -1;
    }
    else{
        mask = ((1ULL << e) -1);
    }
    __int128 res =1;
    __int128 b = base;
    while(exponent >0){
        if(exponent &1){
            res = (res * b) & mask;
        }
        b = (b * b) & mask;
        exponent >>=1;
    }
    return res;
}

// Function to compare two strings representing numbers
bool is_equal(const string& a, const string& b){
    string a_trim = a;
    string b_trim = b;
    // Remove leading zeros
    a_trim.erase(0, min(a_trim.find_first_not_of('0'), a_trim.size()-1));
    b_trim.erase(0, min(b_trim.find_first_not_of('0'), b_trim.size()-1));
    return a_trim == b_trim;
}

// Function to multiply two strings representing numbers and mod m
string multiply_mod_p5(const string& a, const string& b, const string& m){
    // Convert a and b to numbers
    unsigned long long A = 0, B =0;
    // Since a and b are less than m=5^e, and e<=100, use unsigned long long if possible
    // Otherwise, use string multiplication
    // Here, e<=100, so implement string multiplication
    // Convert a and b to integers
    string res = "0";
    // Multiply a and b
    int len_a = a.size();
    int len_b = b.size();
    vector<int> product(len_a + len_b, 0);
    for(int i=len_a-1;i>=0;i--){
        for(int j=len_b-1;j>=0;j--){
            int p = (a[i]-'0') * (b[j]-'0');
            int pos = (len_a -1 -i) + (len_b -1 -j);
            product[pos] += p;
        }
    }
    // Handle carry
    for(int i=0;i<product.size();i++){
        if(product[i] >=10){
            if(i+1 >= product.size()) product.push_back(0);
            product[i+1] += product[i]/10;
            product[i] %=10;
        }
    }
    // Convert back to string
    string multiplied = "";
    for(int i=product.size()-1;i>=0;i--){
        multiplied += to_string(product[i]);
    }
    // Now compute multiplied mod m
    // Implement division mod
    string modulus = m;
    string dividend = multiplied;
    string remainder = "0";
    for(char c : dividend){
        // Shift remainder
        remainder += c;
        // Remove leading zeros
        size_t pos = remainder.find_first_not_of('0');
        if(pos != string::npos){
            remainder = remainder.substr(pos);
        }
        else{
            remainder = "0";
        }
        // While remainder >= modulus, subtract
        while(remainder.size() > modulus.size() || (remainder.size() == modulus.size() && remainder >= modulus)){
            // Subtract modulus
            string temp = "";
            int borrow =0;
            for(int i=modulus.size()-1;i>=0;i--){
                int sub = (remainder[remainder.size()-modulus.size()+i] - '0') - (modulus[i]-'0') - borrow;
                if(sub <0){
                    sub +=10;
                    borrow =1;
                }
                else{
                    borrow =0;
                }
                temp += (sub + '0');
            }
            // Now assign back
            string new_remainder = "";
            for(int i=modulus.size()-1;i>=0;i--){
                new_remainder += temp[i];
            }
            new_remainder += remainder.substr(0, remainder.size()-modulus.size());
            // Remove leading zeros
            size_t p = new_remainder.find_first_not_of('0');
            if(p != string::npos){
                remainder = new_remainder.substr(p);
            }
            else{
                remainder = "0";
            }
        }
    }
    return remainder;
}

// Function to compute power modulo for p=5^e
string power_mod_p5(const string& base, unsigned long long exponent, const string& m){
    string result = "1";
    string b = base;
    while(exponent >0){
        if(exponent &1){
            // result = (result * b) mod m
            result = multiply_mod_p5(result, b, m);
        }
        // b = (b * b) mod m
        b = multiply_mod_p5(b, b, m);
        exponent >>=1;
    }
    return result;
}

// Function to compute multiplicative order modulo 5^e
unsigned long long multiplicative_order_p5(unsigned long long n_mod5e, int e){
    // Compute phi=4*5^(e-1)
    // List all divisors of phi
    // 4*5^(e-1) has divisors 2^a *5^b where a=0,1,2 and b=0..e-1
    // Generate and sort them
    // Implement phi as string
    // Compute m=5^e
    string m = "1";
    for(int i=0;i<e;i++) m += "5";
    // But 5^e is not needed, just use multiply function
    // Instead, proceed to list divisors
    vector<unsigned long long> divisors = list_divisors_p5(e);
    // Convert n_mod5e to string
    string base = to_string(n_mod5e);
    for(auto d : divisors){
        // Compute base^d mod m
        string powm = power_mod_p5(base, d, m);
        if(is_equal(powm, "1")){
            return d;
        }
    }
    return -1;
}

int main(){
    string n_str;
    int k;
    cin >> n_str >> k;
    // Compute m=10^k, but we don't need it directly
    // Compute n mod2^k and n mod5^k
    unsigned long long n_mod2k = mod_pow2(n_str, k);
    unsigned long long n_mod5k = mod_pow5(n_str, k);
    // Compute v2: max x <=k s.t. n mod2^{x} ==0
    int v2=0;
    for(int x=1;x<=k;x++){
        if( (n_mod2k & ((1ULL <<x)-1)) ==0 ){
            v2 =x;
        }
        else{
            break;
        }
    }
    // Similarly compute v5: max y <=k s.t. n mod5^{y} ==0
    int v5=0;
    unsigned long long temp = n_mod5k;
    while(v5 <k){
        if(temp %5 ==0){
            v5++;
            temp /=5;
        }
        else{
            break;
        }
    }
    // Compute m’=2^{k -v2} *5^{k -v5}
    int a=k -v2;
    int b=k -v5;
    // If m’==1, cycle length=1
    if(a ==0 && b==0){
        cout << "1";
        return 0;
    }
    // Compute order_p2 and order_p5
    unsigned long long order_p2=1;
    if(a >0){
        // Compute n mod2^{a}
        unsigned long long n_mod2a = n_mod2k >> v2;
        // Compute phi=2^{a-1}
        // List divisors of phi: 1,2,4,...,2^{a-1}
        vector<unsigned long long> divisors_p2 = list_divisors_p2(a);
        // Find the smallest d in divisors_p2 s.t. n_mod2a ^d ≡1 mod2^a
        for(auto d : divisors_p2){
            unsigned long long res = powmod_p2(n_mod2a, d, a);
            if(res ==1){
                order_p2 =d;
                break;
            }
        }
    }
    unsigned long long order_p5=1;
    if(b >0){
        // Compute n mod5^{b}
        unsigned long long n_mod5b =0;
        unsigned long long power5=1;
        for(int i=0;i<b;i++) power5 *=5;
        // Recompute n mod5^b
        unsigned long long mod5b= power5;
        unsigned long long rem =0;
        for(char c : n_str){
            rem = (rem *10 + (c - '0')) % mod5b;
        }
        n_mod5b = rem;
        // Compute order_p5
        order_p5 = multiplicative_order_p5(n_mod5b, b);
    }
    // Compute lcm(order_p2, order_p5)
    unsigned long long lcm_val =1;
    if(a >0 && b >0){
        lcm_val = (order_p2 * order_p5) / gcd_func(order_p2, order_p5);
    }
    else if(a >0){
        lcm_val = order_p2;
    }
    else{
        lcm_val = order_p5;
    }
    cout << lcm_val;
}
