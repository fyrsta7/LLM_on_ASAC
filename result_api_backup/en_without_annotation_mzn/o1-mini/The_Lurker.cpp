#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<string> encrypt(n);
    for(auto &s: encrypt) cin>>s;
    vector<string> origin(n);
    for(auto &s: origin) cin>>s;
    int m;
    cin>>m;
    vector<string> translate(m);
    for(auto &s: translate) cin>>s;
    
    // Map from origin to encrypt
    unordered_map<char, char> mapping;
    // To check multiple mappings
    unordered_map<char, char> temp_map;
    bool condition2 = false;
    for(int i=0;i<n;i++){
        char o = origin[i][0];
        char e = encrypt[i][0];
        if(temp_map.find(o)!=temp_map.end()){
            if(temp_map[o]!=e){
                condition2 = true;
                break;
            }
        }
        else{
            temp_map[o]=e;
        }
    }
    // Count unique origin and encrypt
    unordered_set<char> unique_origin, unique_encrypt;
    for(int i=0;i<n;i++){
        unique_origin.insert(origin[i][0]);
        unique_encrypt.insert(encrypt[i][0]);
    }
    bool condition1 = (unique_origin.size() < 26) || (unique_encrypt.size() < 26);
    bool if_fail = condition1 || condition2;
    if(if_fail){
        cout<<"Failed";
    }
    else{
        // Build mapping
        for(int i=0;i<n;i++) mapping[origin[i][0]] = encrypt[i][0];
        string result = "";
        for(int i=0;i<m;i++){
            char t = translate[i][0];
            if(mapping.find(t)!=mapping.end()) result += mapping[t];
            else result += t;
        }
        cout<<result;
    }
}