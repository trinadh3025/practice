#include<iostream>
#include<string>
#include<cstring>

using namespace std;

class String{
private:
	char* source;
	int length;
public:
	String():source(nullptr),length(0){
		cout << "Empty String object created." << endl;
	}

	String(const char* s){
		int length_ = strlen(s);
		source = (char*)malloc(sizeof(char)*(length_+1));
		if(source != nullptr){
			strcpy(source, s);
			length = length_+1;
			source[length] = '\0';
		}
		else{
			cout << "Problem in creating object" << endl;
		}
		cout << "String object created thorugh constructor" << endl;
	}

	String(const String& s){
		if(s.length == 0 || s.source == nullptr){
			cout << "Object creation failed" << endl;

		}
		length = s.length;
		source = (char*)malloc(sizeof(char)*length);
		if(source!=nullptr){
			strcpy(source, s.getString());
		}
		cout << "String object created thorugh copy constructor" << endl;
	}

	String& operator = (const String& s){
		if(this == &s || s.length == 0 || s.source == nullptr){
			cout << "Object creation failed" << endl;
		}
		if(source != nullptr)
			free(source);
		source = (char*)malloc(sizeof(char)*(s.getLength()));
		strcpy(source, s.getString());
		length = s.getLength();
		cout << "String object copied through copy assignement operator" << endl;
		return *this;
	}

	String(const String&& s){
		if(s.length == 0 || s.source == nullptr){
			cout << "Object creation failed" << endl;

		}
		length = s.length;
		source = (char*)malloc(sizeof(char)*length);
		if(source!=nullptr){
			strcpy(source, s.getString());
		}
		cout << "String object created thorugh move copy constructor" << endl;
	}

	String& operator = (const String&& s){
		if(this == &s || s.length == 0 || s.source == nullptr){
			cout << "Object creation failed" << endl;
		}
		if(source != nullptr)
			free(source);
		source = (char*)malloc(sizeof(char)*(s.getLength()));
		strcpy(source, s.getString());
		length = s.getLength();
		cout << "String object moved through move copy assignement operator" << endl;
		return *this;
	}
	int getLength() const{
		return length;
	}

	char* getString () const{
		if(source != nullptr){
			return source;
		}
		cout << "Empty object" << endl;
	}

	bool isEmpty(){
		return (source == nullptr);
	}

	~String(){
		if(source != nullptr){
			free(source);
			length = 0;
			source = nullptr;
		}
	}

};

int main(){
	char s[10] = "hello";
	String str(s);
	cout << str.getString() << endl;
	cout << str.getLength() << endl;

	String str1(str);
	cout << str1.getLength() << endl;
	cout << str1.getString() << endl;

	String str2;
	str2 = str1;
	cout << str2.getLength() << endl;
	cout << str2.getString() << endl;

	String str3;
	cout << str3.isEmpty() << endl;
	str3 = std::move(str2);
	cout << str3.getLength() << endl;
	cout << str3.getString() << endl;
	cout << str3.isEmpty() << endl;
	return 0;
}
