#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> data(n);
    for(int i = 0; i < n; i++) {
        cin >> data[i];
    }

    unordered_set<int> ans;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                if(j != k && data[i] == data[j] + data[k]) {
                    ans.insert(data[i]);
                }
            }
        }
    }

    cout << ans.size() << endl;
    return 0;
}