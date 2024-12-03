#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int s, t, w;
    cin >> s >> t >> w;
    string current;
    cin >> current;
    int m = t - s +1;
    vector<int> indices(w);
    for(int i=0;i<w;i++){
        indices[i] = (current[i] - 'a') - (s -1);
    }
    int count=0;
    while(count <5){
        // Find the first position from the end that can be incremented
        int i = w-1;
        while(i >=0 && indices[i] == m - w + i){
            i--;
        }
        if(i <0){
            break;
        }
        // Increment this position
        indices[i]++;
        // Set the following positions
        for(int j=i+1;j<w;j++){
            indices[j] = indices[j-1]+1;
        }
        // Convert indices back to string
        string next_num = "";
        for(int j=0;j<w;j++){
            char c = 'a' + s -1 + indices[j];
            next_num += c;
        }
        cout << next_num << endl;
        count++;
    }
}