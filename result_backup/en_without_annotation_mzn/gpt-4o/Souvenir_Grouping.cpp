#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int w, n;
vector<int> P;

int main() {
    cin >> w >> n;
    P.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> P[i];
    
    vector<int> indices(n), weight(n, 0), num(n, 0);
    iota(indices.begin(), indices.end(), 1);
    int min_object = n;

    do {
        fill(weight.begin(), weight.end(), 0);
        fill(num.begin(), num.end(), 0);
        int object = 0;
        
        for (int i = 0; i < n; ++i) {
            weight[indices[i] - 1] += P[i];
            num[indices[i] - 1]++;
        }

        bool valid = true;
        for (int i = 0; i < n; ++i) {
            if (num[i] > 2 || weight[i] > w) {
                valid = false;
                break;
            }
            if (num[i] > 0) object += 1;
        }

        if (valid)
            min_object = min(min_object, object);

    } while (next_permutation(indices.begin(), indices.end()));

    cout << min_object << endl;
    return 0;
}