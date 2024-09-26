#include <iostream>
#include <vector>

using namespace std;

int main() {
    int L, M;
    cin >> L >> M;
    vector<pair<int, int>> spot(M);
    for(int i = 0; i < M; ++i) {
        cin >> spot[i].first >> spot[i].second;
    }
    
    vector<bool> index(L + 1, true);

    for(int i = 0; i <= L; ++i) {
        for(int j = 0; j < M; ++j) {
            if(i >= spot[j].first && i <= spot[j].second) {
                index[i] = false;
                break;
            }
        }
    }

    int cnt = 0;
    for(int i = 0; i <= L; ++i) {
        if(index[i]) ++cnt;
    }

    cout << cnt << endl;

    return 0;
}