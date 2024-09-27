#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> face(n);
    vector<string> person(n);
    for (int i = 0; i < n; ++i) {
        cin >> face[i] >> person[i];
    }
    
    vector<vector<int>> instruction(m, vector<int>(2));
    for (int i = 0; i < m; ++i) {
        cin >> instruction[i][0] >> instruction[i][1];
    }
    
    int current_position = 0;
    for (int i = 0; i < m; ++i) {
        if ((face[current_position] == 0 && instruction[i][0] == 0) || (face[current_position] == 1 && instruction[i][0] == 1)) {
            current_position = (current_position + n - instruction[i][1] - 1) % n;
        } else {
            current_position = (current_position + instruction[i][1]) % n;
        }
    }
    
    cout << person[current_position] << endl;
    
    return 0;
}
