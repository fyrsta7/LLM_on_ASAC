#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int v;
    int p;
    int q;
};

int main(){
    int n, m;
    cin >> n >> m;
    vector<Item> items(m+1);
    for(int i=1;i<=m;i++) cin >> items[i].v >> items[i].p >> items[i].q;
    // Group main items
    struct Group {
        int v;
        int p;
        vector<pair<int, int>> accessories;
    };
    vector<Group> groups;
    for(int i=1;i<=m;i++){
        if(items[i].q == 0){
            Group g;
            g.v = items[i].v;
            g.p = items[i].p;
            groups.push_back(g);
        }
    }
    // Assign accessories
    for(int i=1;i<=m;i++){
        if(items[i].q !=0){
            int main_id = items[i].q -1;
            if(main_id >=0 && main_id < groups.size()){
                groups[main_id].accessories.emplace_back(items[i].v, items[i].p);
            }
        }
    }
    // Initialize DP
    vector<int> dp(n+1, 0);
    // Iterate over groups
    for(auto &g: groups){
        // Build possible options
        vector<pair<int, int>> opts;
        // Main alone
        opts.emplace_back(g.v, g.v * g.p);
        // Main + accessory1
        if(g.accessories.size() >=1){
            opts.emplace_back(g.v + g.accessories[0].first, g.v * g.p + g.accessories[0].first * g.accessories[0].second);
        }
        // Main + accessory2
        if(g.accessories.size() >=2){
            opts.emplace_back(g.v + g.accessories[1].first, g.v * g.p + g.accessories[1].first * g.accessories[1].second);
        }
        // Main + accessory1 + accessory2
        if(g.accessories.size() ==2){
            opts.emplace_back(g.v + g.accessories[0].first + g.accessories[1].first, g.v * g.p + g.accessories[0].first * g.accessories[0].second + g.accessories[1].first * g.accessories[1].second);
        }
        // Update DP
        for(int j = n; j >=0; j--){
            for(auto &opt: opts){
                if(j >= opt.first){
                    dp[j] = max(dp[j], dp[j - opt.first] + opt.second);
                }
            }
        }
    }
    // Output the result
    int res = 0;
    for(int i=0;i<=n;i++) res = max(res, dp[i]);
    cout << res;
}