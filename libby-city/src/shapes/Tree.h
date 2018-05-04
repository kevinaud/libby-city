#ifndef TREE_H
#define TREE_H

#include "Shape.h"
#include "Cone.h"

class Tree : public Shape {
public:
	Tree() {
		cone = Cone();
		numTiers = rand() % (3 - (1) + 1) + (1);
	};
	~Tree() {};

	void draw() {
        //glClearColor(1.0, 0.0, 0.0, 1.0);
		for (int i = 0; i < numTiers; i++) {
			glPushMatrix();
			glTranslatef(0, 0.5+i, 0);
			cone.draw();
			glPopMatrix();
		}
	};


private:
	Cone cone;
	int numTiers;

};

#endif
