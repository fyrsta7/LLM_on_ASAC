#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> face(n);
    vector<string> person(n);
    vector<vector<int>> instruction(m, vector<int>(2));
    
    for (int i = 0; i < n; ++i) {
        cin >> face[i] >> person[i];
    }
    
    for (int i = 0; i < m; ++i) {
        cin >> instruction[i][0] >> instruction[i][1];
    }
    
    int current = 0; // Starting at position 1 (0-indexed)
    
    for (int i = 0; i < m; ++i) {
        if ((face[current] == 0 && instruction[i][0] == 0) || (face[current] == 1 && instruction[i][0] == 1)) {
            current = (current + n - instruction[i][1] - 1) % n;
        } else {
            current = (current + instruction[i][1]) % n;
        }
    }
    
    cout << person[current] << endl;
    
    return 0;
}
