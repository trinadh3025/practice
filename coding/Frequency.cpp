#include <iostream>
#include <vector>
#include <map>

using namespace std;

std::map<int,int> GetDict(std::vector<int> a, std::vector<int> b){
    int a_size = a.size();
    int b_size = b.size();
    std::map<int, int> frequency;
    for(int i=0;i<a_size; i++){
        frequency[a[i]]++;
    }
    for(int i=0;i<b_size; i++){
        frequency[b[i]]++;
    }

    return frequency;
}

int main(){

    std::vector<int> input1 = {1,5,1,1,3,9};
    std::vector<int> input2 = {1,3,5,4,6};

    std::map<int,int> result;
    result = GetDict(input1, input2);

    cout << "A: {1,5,1,1,3,9}" << endl;
    cout << "B: {1,3,5,4,6}" << endl;
    cout << "[";
    for(auto& pair: result){
    	cout  << pair.first << ":" << pair.second << ", "; 
    }
    cout << "]" << endl;
   

    return 0;
}
