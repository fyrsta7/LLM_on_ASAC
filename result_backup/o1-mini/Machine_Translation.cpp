#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(){
    int M, N;
    cin >> M >> N;
    queue<int> cache;
    vector<bool> present(1001, false);
    int count = 0;
    for(int i=0;i<N;i++){
        int word;
        cin >> word;
        if(!present[word]){
            count++;
            if(cache.size() == M){
                int old = cache.front();
                cache.pop();
                present[old] = false;
            }
            cache.push(word);
            present[word] = true;
        }
    }
    cout << count;
}