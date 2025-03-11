#include <iostream>
#include <cmath>

using namespace std;

class Shape{
public:
	virtual double area() const = 0;
	virtual void display() const = 0;
	virtual ~Shape(){}
};

class Rectangle : public Shape{
private:
	double length, width;

public:
	Rectangle(double l, double w):length(l), width(w){}

	double area() const override{
		return length*width;
	}

	void display() const override{
		cout << "Rectangle Area: " << area() << endl;
	}

	void setDimensions(double l, double w){
		length = l;
		width = w;
		cout << "Updated Rectangle Dimensions: " << length << " x " << width << endl;

	}
};

class Circle : public Shape{
private:
	double radius;
public:
	Circle(double r) : radius(r) {}

	double area() const override{
		return M_PI*radius*radius;
	}

	void display() const override{
		cout << "Circle Area: " << area() << endl;
	}

	void setRadius(double r){
		radius = r;
		cout << "Updated circle radius: " << radius << endl;
	}
};

int main(){
	Shape* shape1 = new Rectangle(10, 5);
	Shape* shape2 = new Circle(7);

	shape1->display();
	shape2->display();

	Rectangle* rect = dynamic_cast<Rectangle*>(shape1);
	
	if(rect){
		rect->setDimensions(20,10);
	}

	Circle* circ = dynamic_cast<Circle*>(shape2);
	if(circ){
		circ->setRadius(10);
	}
	
	shape1->display();
	shape2->display();

	delete shape1;
	delete shape2;

	return 0;
}


