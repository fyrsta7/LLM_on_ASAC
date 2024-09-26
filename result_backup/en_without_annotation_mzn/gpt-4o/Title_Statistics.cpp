#include <iostream>
#include <string>
using namespace std;

int main() {
    string title;
    getline(cin, title);
    int title_length = title.length();
    int answer = 0;
    
    for(int i = 0; i < title_length; ii++) {
        if(title[i] != ' ') {
            answer++;
        }
    }
    
    cout << answer << endl;

    return 0;
}