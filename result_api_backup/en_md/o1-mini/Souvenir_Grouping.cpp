#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    int w, n;
    std::cin >> w >> n;
    std::vector<int> p(n);
    for(int &x : p){
        std::cin >> x;
    }
    std::sort(p.begin(), p.end());
    int left = 0, right = n-1;
    int count = 0;
    while(left <= right){
        if(p[left] + p[right] <= w){
            left++;
        }
        right--;
        count++;
    }
    std::cout << count;
    return 0;
}