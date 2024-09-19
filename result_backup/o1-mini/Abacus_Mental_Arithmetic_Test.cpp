#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int &x: arr) cin >> x;
    sort(arr.begin(), arr.end());
    int count=0;
    for(int i=0;i<n;i++){
        int target = arr[i];
        int left=0, right=n-1;
        while(left < right){
            if(left == i){
                left++;
                continue;
            }
            if(right == i){
                right--;
                continue;
            }
            if(left >= right) break;
            int sum = arr[left] + arr[right];
            if(sum == target){
                count++;
                break;
            }
            else if(sum < target){
                left++;
            }
            else{
                right--;
            }
        }
    }
    cout << count;
}