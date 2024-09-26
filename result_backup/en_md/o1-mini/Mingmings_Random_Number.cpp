#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> nums(N);
    for(int i=0;i<N;i++) cin >> nums[i];
    sort(nums.begin(), nums.end());
    vector<int> unique_nums;
    if(N >0){
        unique_nums.push_back(nums[0]);
        for(int i=1;i<N;i++) {
            if(nums[i] != nums[i-1]){
                unique_nums.push_back(nums[i]);
            }
        }
    }
    int M = unique_nums.size();
    cout << M << endl;
    for(int i=0;i<M;i++){
        if(i>0) cout << " ";
        cout << unique_nums[i];
    }
    return 0;
}