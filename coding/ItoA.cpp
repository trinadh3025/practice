#include <iostream>
#include <memory>
using namespace std;
char* ItoA(int input_value, int base){
    if(base<2 || base>32){
    	return "Invalid base";
    }
    if(input_value == 0){
        return "0";
    }


    char* result = (char*)malloc(sizeof(char)*10);
    char* characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i=0;
    unsigned int input;
    if(input_value < 0){
        input = -input_value;
    }else{
        input = input_value;
    }
    while(input > 0){
        result[i++] = characters[input%base];
        input = input/base;
    }
    result[i] = '\0';
    char temp;
    for(int j=0;j<i/2;j++){
        temp = result[j];
        result[j] = result[i-j-1];
        result[i-j-1] = temp;
    }

    return result;
}
int main(){

    cout << "(1234, 2): " << ItoA(1234,2) << endl;
    cout << "(-1234, 16): " << ItoA(-1234,16) << endl;
    cout << "(0,16) : " << ItoA(0,16) << endl;
    cout << "(0,10) : " << ItoA(0,10) << endl;
    cout << "(0,2): " << ItoA(0,2) << endl;
    cout << "Invalid :" << ItoA(0,1) << endl;
    
    return 0;
}
