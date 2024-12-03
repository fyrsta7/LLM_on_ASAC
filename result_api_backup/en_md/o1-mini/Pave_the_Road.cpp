#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    std::vector<int> d(n);
    for(int i=0;i<n;i++) std::cin >> d[i];
    long long ans=0;
    int prev=0;
    for(int i=0;i<n;i++){
        if(d[i] > prev){
            ans += (long long)(d[i] - prev);
        }
        prev = d[i];
    }
    std::cout << ans;
}