#include <iostream>
#include <string>

using namespace std;

void removeCharacter(char* str, char charToRemove){
	int length, char_count=0;
	char temp;
	if(!str)
		return;

	for(length=0; str[length]!='\0';length++){
		if(str[length] == charToRemove)
			char_count++;
	}

	if(length == char_count){
		str[0] = '\0';
		return;
	}

	for(int j=0;j<length;j++){
		if(char_count == 0)
			break;

		if(str[j]==charToRemove && str[j+1]!=charToRemove && (j+1)!=length){
			temp = str[j];
			str[j]=str[j+1];
			str[j+1] = temp;
			
			char_count--;
				
			
		}
	}

}

int main(){
	char a[10] = "aa b c";
	removeCharacter(a,' ');

	cout << "Output: " << a << endl;

	return 0;
}
