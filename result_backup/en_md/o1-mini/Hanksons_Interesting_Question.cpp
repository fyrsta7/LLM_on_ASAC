#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

// Function to generate sieve of primes up to limit
vector<int> sieve(int limit) {
    vector<bool> is_prime(limit+1, true);
    is_prime[0] = is_prime[1] = false;
    for(int p=2; p*p <= limit; p++) {
        if(is_prime[p]){
            for(int multiple=p*p; multiple<=limit; multiple+=p){
                is_prime[multiple] = false;
            }
        }
    }
    vector<int> primes;
    for(int p=2; p<=limit; p++) if(is_prime[p]) primes.push_back(p);
    return primes;
}

// Function to factorize a number using precomputed primes
vector<pair<long long, int>> factorize(long long n, const vector<int>& primes){
    vector<pair<long long, int>> factors;
    for(auto p: primes){
        if(p*p > n) break;
        if(n % p ==0){
            int cnt =0;
            while(n %p ==0){
                cnt++;
                n /=p;
            }
            factors.emplace_back(make_pair((long long)p, cnt));
        }
    }
    if(n >1){
        factors.emplace_back(make_pair(n, 1));
    }
    return factors;
}

// Function to compute gcd of two numbers
long long compute_gcd(long long a, long long b){
    while(b){
        long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Precompute primes up to sqrt(2e9)
    vector<int> primes = sieve(45000);
    
    int n;
    cin >> n;
    while(n--){
        long long a0, a1, b0, b1;
        cin >> a0 >> a1 >> b0 >> b1;
        // Compute m and t
        if(a0 % a1 !=0 || b1 % b0 !=0){
            cout << "0\n";
            continue;
        }
        long long m = a0 / a1;
        long long t = b1 / b0;
        // Factorize b0 and b1
        vector<pair<long long, int>> factors_b0 = factorize(b0, primes);
        vector<pair<long long, int>> factors_b1 = factorize(b1, primes);
        // Check b0 divides b1
        bool valid = true;
        map<long long, int> exponents_b0;
        for(auto &[p, e]: factors_b0) exponents_b0[p] = e;
        map<long long, int> exponents_b1;
        for(auto &[p, e]: factors_b1) exponents_b1[p] = e;
        for(auto &[p, e]: exponents_b0){
            if(exponents_b1.find(p) == exponents_b1.end() || exponents_b1[p] < e){
                valid = false;
                break;
            }
        }
        if(!valid){
            cout << "0\n";
            continue;
        }
        // Prepare list of primes and their possible exponents for x
        vector<pair<long long, vector<int>>> primes_x;
        for(auto &[p, f_p]: exponents_b1){
            if(exponents_b0.find(p) != exponents_b0.end()){
                int e_p = exponents_b0[p];
                if(f_p > e_p){
                    primes_x.emplace_back(make_pair(p, vector<int>{(int)f_p}));
                }
                else{
                    vector<int> range_exps;
                    for(int k=0; k<=exponents_b0[p]; k++) range_exps.push_back(k);
                    primes_x.emplace_back(make_pair(p, range_exps));
                }
            }
            else{
                primes_x.emplace_back(make_pair(p, vector<int>{(int)f_p}));
            }
        }
        // Recursive enumeration
        long long count_x =0;
        // Factorize m for gcd checking
        vector<pair<long long, int>> factors_m = factorize(m, primes);
        // Function to recursively generate x
        // Using lambda with capture by reference
        function<void(int, long long)> dfs = [&](int idx, long long current_x)-> void{
            if(idx == primes_x.size()){
                if(current_x % a1 !=0) return;
                long long k = current_x / a1;
                if(k ==0) return;
                // Check gcd(k, m) ==1
                // Compute gcd(k, m)
                long long g = compute_gcd(k, m);
                if(g ==1){
                    count_x++;
                }
                return;
            }
            // Iterate through possible exponents for current prime
            long long p = primes_x[idx].first;
            for(auto exp: primes_x[idx].second){
                // Compute p^exp
                long long power =1;
                for(int i=0; i<exp; i++) {
                    if(power > (2e9 / p)) { power = -1; break;}
                    power *= p;
                }
                if(power == -1) continue;
                if(current_x > 2e9 / power) continue;
                long long new_x = current_x * power;
                dfs(idx+1, new_x);
            }
        };
        dfs(0, 1);
        cout << count_x << "\n";
    }
}
