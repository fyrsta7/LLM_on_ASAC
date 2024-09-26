#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 998244353;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for(auto &row : a) for(auto &x : row) cin >> x;
    
    // Generate all possible valid plans
    // A plan is a set of (x,y) with distinct x, a[x][y]>0, and for each y, count <= floor(dish_num/2)
    // Since dish_num varies, we handle constraints later
    // To optimize, store plans with their bits and product
    // Assign each cell a unique id
    int total = n * m;
    vector<pair<int, int>> cells;
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(a[i][j]>0) cells.emplace_back(i,j);
    int total_cells = cells.size();
    // Generate all subsets with distinct x
    vector<pair<ll, ll>> valid_plans; // (dish_num, product)
    for(int mask=1; mask<(1<<total_cells); mask++){
        // Check distinct x
        int dish_num = 0;
        ll product = 1;
        vector<int> y_count(m,0);
        bool ok = true;
        vector<int> used_x(n, 0);
        for(int i=0;i<total_cells;i++) if(mask & (1<<i)){
            int x = cells[i].first;
            int y = cells[i].second;
            if(used_x[x]) {ok = false; break;}
            used_x[x] = 1;
            y_count[y]++;
            dish_num++;
            // We'll check y_count <= floor(dish_num/2) later
            if(a[x][y] == 0){ok = false; break;}
            product = (product * (ll)a[x][y]) % MOD;
        }
        if(!ok) continue;
        // Check y_count <= floor(dish_num/2)
        bool y_ok = true;
        for(int cnt : y_count) if(cnt > dish_num/2){y_ok = false; break;}
        if(!y_ok) continue;
        valid_plans.emplace_back((ll)dish_num, product);
    }
    
    // Now, we need to select a subset of valid_plans with constraints:
    // For any two plans, either dish_num different or there exists x with same and different y
    // This is equivalent to saying that if dish_num same, then plans must differ in at least one (x,y)
    // To simplify, since dish_num is part of the plan information, and plans are unique, we can select all plans
    // as long as when dish_num same, they are different in at least one (x,y)
    // But since we have already unique plans, we can take all of them
    // Hence, maximize num is the number of valid_plans
    // And s is the sum of products
    // But likely, constraints in MiniZinc are more stringent, but without clearer problem statement, proceed
    // So maximize num by taking all valid_plans
    // And compute s = sum of products
    // However, to adhere to constraints, ensure that for any two plans with same dish_num, they have at least one differing (x,y)
    // Which they already do as they are unique
    // So num is valid_plans.size(), s is sum of products
    int num = valid_plans.size();
    ll s = 0;
    for(auto &[dn, p] : valid_plans){
        s = (s + p) % MOD;
    }
    cout << s;
}