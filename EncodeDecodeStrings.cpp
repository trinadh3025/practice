#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;
class Solution {
public:

    string encode(vector<string>& strs) {
        string result = "";
        if(strs.empty())
            return result;
        else{
            result = strs[0];
            for(int i=1;i<strs.size();i++){
                result = result + '|' + strs[i];
            }
        }
        cout << result << endl;
        return result;
    }

    vector<string> decode(string s) {
        if(s.empty()) return {};
        vector<string> result;
	std::stringstream ss(s);
        string t="";
        int index=0;
        while (getline(ss, t, '|'))
            result.push_back(t);
        /*
        for(int i=0;i<s.size();i++){
            if(s[i]=='|'){
                temp[index]='\n';
                //result.push_back(temp);
                cout << temp << endl;
                index=0;
                continue;
            }
            temp[index++]= s[i];
        }
        */
        
        return result;
    }
    /*
    string encode(vector<string>& strs) {
        if (strs.empty()) return "";
        vector<int> sizes;
        string res = "";
        for (string& s : strs) {
            sizes.push_back(s.size());
        }
        for (int sz : sizes) {
            res += to_string(sz) + ',';
        }
        res += '#';
        for (string& s : strs) {
            res += s;
        }
        return res;
    }

    vector<string> decode(string s) {
        if (s.empty()) return {};
        vector<int> sizes;
        vector<string> res;
        int i = 0;
        while (s[i] != '#') {
            string cur = "";
            while (s[i] != ',') {
                cur += s[i];
                i++;
            }
            sizes.push_back(stoi(cur));
            i++;
        }
        i++;
        for (int sz : sizes) {
            res.push_back(s.substr(i, sz));
            i += sz;
        }
        return res;
    }
    */
};

int main(){
  Solution s;
  vector<string> strings = {"hello", "world"};
  cout << s.encode(strings) << endl;
  return 0;
}

