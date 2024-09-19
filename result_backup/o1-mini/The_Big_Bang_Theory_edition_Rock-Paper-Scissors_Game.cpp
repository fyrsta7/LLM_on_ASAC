#include <iostream>
#include <vector>
using namespace std;

int main(){
    int N, NA, NB;
    cin >> N >> NA >> NB;
    vector<int> A(NA);
    for(int i=0;i<NA;i++) cin>>A[i];
    vector<int> B(NB);
    for(int i=0;i<NB;i++) cin>>B[i];
    int beats_table[5][2] = { {2,3}, {0,3}, {1,4}, {2,4}, {1,0} };
    int A_score=0, B_score=0;
    for(int i=0;i<N;i++){
        int a = A[i%NA];
        int b = B[i%NB];
        if(a == b) continue;
        if(b == beats_table[a][0] || b == beats_table[a][1]){
            A_score++;
        }
        else{
            B_score++;
        }
    }
    cout << A_score << " " << B_score;
}