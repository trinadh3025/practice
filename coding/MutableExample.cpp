#include <iostream>

using namespace std;

class Customer{
	string name;
	mutable string placedorder;
	int tableno;
	mutable int bill;
public:
	Customer(string s, string m, int a, int p){
		name = s;
		placedorder = m;
		tableno = a;
		bill = p;
	}

	void changePlacedOrder(string p) const{
		placedorder = p;
	}

	void changeBill(int s) const{
		bill = s;
	}

	void display() const{
		cout << "Customer name is: " << name << endl;
		cout << "Food ordered by customer is: " << placedorder << endl;
		cout << "Table no is: " << tableno << endl;
		cout << "Total payable amount: " << bill << endl;
	}



};

class Test{
	public:
		int x;
		mutable int y;
		Test() {
			x=4;
			y=10;
		}
};

int main(){
	const Customer c1("Trinadh", "Idly", 3, 100);
	c1.display();
	c1.changePlacedOrder("Puri");
	c1.changeBill(150);
	c1.display();

	const Test t1;
	t1.y = 8;
	cout << t1.y << endl;
	return 0;
}
