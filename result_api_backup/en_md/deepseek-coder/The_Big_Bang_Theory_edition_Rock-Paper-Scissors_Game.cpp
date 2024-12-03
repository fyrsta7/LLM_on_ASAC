#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, NA, NB;
    cin >> N >> NA >> NB;
    vector<int> A(NA), B(NB);
    for (int i = 0; i < NA; ++i) cin >> A[i];
    for (int i = 0; i < NB; ++i) cin >> B[i];

    vector<vector<int>> result = {
        {0, -1, 1, 1, -1},
        {1, 0, -1, -1, 1},
        {-1, 1, 0, 1, -1},
        {-1, 1, -1, 0, 1},
        {1, -1, 1, -1, 0}
    };

    int scoreA = 0, scoreB = 0;
    for (int i = 0; i < N; ++i) {
        int a = A[i % NA];
        int b = B[i % NB];
        if (result[a][b] == 1) scoreA++;
        else if (result[a][b] == -1) scoreB++;
    }

    cout << scoreA << " " << scoreB << endl;
    return 0;
}
