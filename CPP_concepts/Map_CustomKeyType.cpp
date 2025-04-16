#include<iostream>
#include<map>
#include<string>

using namespace std;
struct Point{
	int x,y;
};

struct PointComparator{
	bool operator()(const Point& a, const Point& b) const{
		if(a.x != b.x){
			return (a.x < b.x);
		}

		return (a.y < b.y);
	}
};

std::ostream& operator<<(std::ostream& os, const Point& p){
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

struct PointA{
	int x,y;

	bool operator < (const PointA& other) const{
		if(x != other.x){
			return (x < other.x);
		}
		return (y < other.y);
	}
};

std::ostream& operator<<(std::ostream& os, const PointA& p){
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

int main(){

	std::map<PointA, std::string> pointMap;

	pointMap[{1,2}] = "Point A";
	pointMap[{3,4}] = "Point B";
	pointMap[{1,3}] = "Point C";

	std::map<Point, std::string, PointComparator> pointMap2;

	pointMap2[{1,2}] = "Point A";
	pointMap2[{3,4}] = "Point B";
	pointMap2[{1,3}] = "Point C";

	for (const auto& pair : pointMap){
		std::cout << pair.first << "=>" << pair.second << endl;
	}

	for (const auto& pair : pointMap2){
		std::cout << pair.first << "=>" << pair.second << endl;
	}
	return 0;
}
