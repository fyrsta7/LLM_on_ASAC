#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> targets(n+1);
    vector<bool> visited(n+1, false);

    for(int i = 1; i <= n; i++) {
        cin >> targets[i];
    }

    int rounds = 0;
    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            int target = i;
            vector<int> path;
            while(!visited[target]) {
                visited[target] = true;
                path.push_back(target);
                target = targets[target];
            }
            if(find(path.begin(), path.end(), target) != path.end()) {
                rounds++;
            }
        }
    }

    cout << rounds;

    return 0;
}