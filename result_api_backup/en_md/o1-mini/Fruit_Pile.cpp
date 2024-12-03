#include <iostream>
#include <queue>
#include <vector>
#include <functional>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    if(n == 1){
        std::cout << 0;
        return 0;
    }
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for(int i=0;i<n;i++){
        int x;
        std::cin >> x;
        pq.push(x);
    }
    long long total = 0;
    while(pq.size() >1){
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        long long sum = (long long)a + (long long)b;
        total += sum;
        pq.push(sum);
    }
    std::cout << total;
}