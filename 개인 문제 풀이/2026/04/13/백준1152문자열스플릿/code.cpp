#include <bits/stdc++.h>
using namespace std;
string line;

vector<string> split(string& line, string delimeter){
    vector<string> result;
    int start = 0;
    int end = line.find(delimeter);
    while(end != string::npos){
        string tmp = line.substr(start, end-start);
        if(tmp.size()>0) result.push_back(tmp);
        start = end + delimeter.size();
        end = line.find(delimeter,start);
    }
    string tmp = line.substr(start, line.size());
    if(tmp.size()>0) result.push_back(tmp);
    return result;
}

int main(){
    getline(cin, line);
    vector<string> result = split(line, " ");
    cout <<result.size();
    return 0;
}
