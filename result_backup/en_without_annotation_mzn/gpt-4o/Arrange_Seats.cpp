#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int M, N, K, L, D;
vector<vector<int>> students;
vector<int> horizontal, vertical;
set<int> hSet, vSet;
vector<int> totalHorizontal, totalVertical;

// Function to check if a student pair is horizontally separated
bool horizontal_separate(int h, int i) {
    return (students[i][0] == h && students[i][2] == h + 1) || 
           (students[i][0] == h + 1 && students[i][2] == h);
}

// Function to check if a student pair is vertically separated
bool vertical_separate(int v, int i) {
    return (students[i][1] == v && students[i][3] == v + 1) || 
           (students[i][1] == v + 1 && students[i][3] == v);
}

// Function to count total separations
int count_total() {
    int total = 0;
    for (int i = 0; i < D; ++i) {
        bool h_sep = any_of(horizontal.begin(), horizontal.end(), [&](int h){ return horizontal_separate(h, i); });
        bool v_sep = any_of(vertical.begin(), vertical.end(), [&](int v){ return vertical_separate(v, i); });
        if (h_sep || v_sep) total++;
    }
    return total;
}

int main() {
    cin >> M >> N >> K >> L >> D;
    students.resize(D, vector<int>(4));
    for (int i = 0; i < D; ++i) 
        for (int j = 0; j < 4; ++j) 
            cin >> students[i][j];

    horizontal.resize(K);
    vertical.resize(L);

    for (int i = 0; i < M; ++i) {
        hSet.insert(i + 1);
    }

    for (int i = 0; i < N; ++i) {
        vSet.insert(i + 1);
    }

    int max_total = 0;

    for (int i = 1; i <= M; ++i) {
        for (int j = i + 1; j <= M; ++j) {
            if (hSet.find(i) != hSet.end() && hSet.find(j) != hSet.end()) {
                horizontal[0] = i;
                horizontal[1] = j;
                for (int k = 1; k <= N; ++k) {
                    for (int l = k + 1; l <= N; ++l) {
                        if (vSet.find(k) != vSet.end() && vSet.find(l) != vSet.end()) {
                            vertical[0] = k;
                            vertical[1] = l;
                            int total_count = count_total();
                            if (total_count > max_total) {
                                max_total = total_count;
                                totalHorizontal = horizontal;
                                totalVertical = vertical;
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < K; ++i) {
        cout << totalHorizontal[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < L; ++i) {
        cout << totalVertical[i] << " ";
    }
    cout << endl;

    return 0;
}