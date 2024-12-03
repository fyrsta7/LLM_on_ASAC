#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> X(n), Y(n);
    for (int i = 0; i < n; ++i) cin >> X[i];
    for (int i = 0; i < n; ++i) cin >> Y[i];
    
    vector<vector<int>> tube(k, vector<int>(3));
    for (int i = 0; i < k; ++i) {
        cin >> tube[i][0] >> tube[i][1] >> tube[i][2];
        tube[i][0]--; // Convert to 0-based index
    }
    
    sort(tube.begin(), tube.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    });
    
    vector<int> bird(n + 1, 1);
    vector<int> tap(n + 1, 0);
    vector<int> d(n, 0);
    
    int pass_tube = 0;
    int score = 0;
    
    for (int i = 0; i < n; ++i) {
        d[i] = (tap[i + 1] == 0) ? -Y[i + 1] : X[i + 1] * tap[i + 1];
        bird[i + 1] = (bird[i] + d[i] >= m) ? m : bird[i] + d[i];
        
        while (pass_tube < k && tube[pass_tube][0] == i) {
            if (bird[i + 1] > tube[pass_tube][1] && bird[i + 1] < tube[pass_tube][2]) {
                pass_tube++;
            } else {
                break;
            }
        }
    }
    
    score = accumulate(tap.begin(), tap.end(), 0) - pass_tube * m;
    
    if (pass_tube == k) {
        cout << "1\n" << accumulate(tap.begin(), tap.end(), 0) << endl;
    } else {
        cout << "0\n" << pass_tube << endl;
    }
    
    return 0;
}