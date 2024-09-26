#include <iostream>
#include <string>

using namespace std;

int main(){
    string isbn;
    cin >> isbn;
    string digits = "";
    for(char c: isbn){
        if(c != '-'){
            digits += c;
        }
    }
    int sum = 0;
    for(int i=0;i<9;i++){
        sum += (digits[i]-'0')*(i+1);
    }
    int mod = sum % 11;
    char identifier;
    if(mod == 10){
        identifier = 'X';
    }
    else{
        identifier = '0' + mod;
    }
    char input_id = isbn[isbn.size()-1];
    if(input_id == identifier){
        cout << "Right";
    }
    else{
        string correct_isbn = "";
        int pos = 0;
        for(int i=0;i<isbn.size()-1;i++){
            if(isbn[i] != '-'){
                correct_isbn += digits[pos++];
            }
            else{
                correct_isbn += '-';
            }
        }
        correct_isbn += '-';
        correct_isbn += identifier;
        cout << correct_isbn;
    }
}