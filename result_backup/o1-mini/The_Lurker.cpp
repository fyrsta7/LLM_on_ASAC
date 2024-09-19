#include <iostream>
#include <string>
using namespace std;

int main(){
    string encrypted1, original, encrypted2;
    cin >> encrypted1 >> original >> encrypted2;
    if(encrypted1.length() != original.length()){
        cout << "Failed";
        return 0;
    }
    int map_x_to_y[26];
    int map_y_to_x[26];
    for(int i=0;i<26;i++) {
        map_x_to_y[i] = -1;
        map_y_to_x[i] = -1;
    }
    int n = encrypted1.length();
    for(int i=0;i<n;i++){
        char x_char = original[i];
        char y_char = encrypted1[i];
        int x = x_char - 'A';
        int y = y_char - 'A';
        if(map_x_to_y[x] == -1){
            map_x_to_y[x] = y;
            if(map_y_to_x[y] == -1){
                map_y_to_x[y] = x;
            }
            else{
                if(map_y_to_x[y] != x){
                    cout << "Failed";
                    return 0;
                }
            }
        }
        else{
            if(map_x_to_y[x] != y){
                cout << "Failed";
                return 0;
            }
        }
    }
    for(int i=0;i<26;i++){
        if(map_x_to_y[i] == -1){
            cout << "Failed";
            return 0;
        }
    }
    string decrypted = "";
    for(char ch: encrypted2){
        if(ch < 'A' || ch > 'Z'){
            cout << "Failed";
            return 0;
        }
        int y = ch - 'A';
        if(map_y_to_x[y] == -1){
            cout << "Failed";
            return 0;
        }
        char x = 'A' + map_y_to_x[y];
        decrypted += x;
    }
    cout << decrypted;
}