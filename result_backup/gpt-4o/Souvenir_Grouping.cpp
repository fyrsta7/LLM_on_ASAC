#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int w, n;
    cin >> w >> n;
    vector<int> prices(n);
    for(int i = 0; i < n; i++){
        cin >> prices[i];
    }
    
    sort(prices.begin(), prices.end());

    int i = 0, j = n - 1;
    int groups = 0;

    while(i <= j){
        if(prices[i] + prices[j] <= w){
            i++;
            j--;
        } else {
            j--;
        }
        groups++;
    }

    cout << groups << endl;

    return 0;
}