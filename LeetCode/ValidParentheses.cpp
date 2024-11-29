#include<iostream>
#include<unordered_map>
#include<string>
#include<stack>

using namespace std;

class Solution{
public:
	bool isValid(string& s){
		stack<char> stk;
		//Below map maintains the open paranthesis
		//corresponding to the closed paranthesis
		unordered_map<char,char> close2open = {{')','('},{']','['},{'}','{'}};
		
		for(char c:s){
			//we check for the character, which is closed paranthesis or not
			//if yes, then it supposed to have corresponding open paranthesis
			//in the stack, otherwise its not valid
			if(close2open.count(c)){
				if(!stk.empty() && stk.top()==close2open[c]){
					stk.pop();
				}else{
					return false;
				}
			} else{//if its a open paranthesis, we push it into stack
				stk.push(c);
			}

		}
		//by the time we traverse the full string, for a valid one, stack should be empty
		return stk.empty();	
	}
};

int main(){
	Solution s;
	string p = "([{]}])";
	cout << s.isValid(p) << endl;
	return 0;
}
