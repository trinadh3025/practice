#include <stdio.h>
#include <stdlib.h>

typedef struct Point{
	int x;
	int y;

	void (*set)(struct Point* self, int x, int y);
	void (*print)(struct Point* self);
}Point;

void Point_set(Point* self, int x, int y){
	self->x = x;
	self->y = y;
}

void Point_print(Point* self){
	printf("Point(%d, %d)\n", self->x, self->y);
}

Point* Point_new(int x, int y){
	Point* p = (Point*)malloc(sizeof(Point));
	p->x = x;
	p->y = y;

	p->set = Point_set;
	p->print = Point_print;

	return p;
}

void Point_delete(Point* p){
	free(p);
}

int main(){
	Point* p1 = Point_new(10, 20);

	p1->print(p1);
	p1->set(p1, 30, 40);
	p1->print(p1);

	Point_delete(p1);

	return 0;
}
