#include "ParkCityBlock.h"
#include <iostream>

ParkCityBlock::ParkCityBlock() {
    int min = 100;
    int max = 200;
	numTrees = rand() % (max - (min) + 1) + (min);
	for (int i = 0; i < numTrees; i++) {
		trees.push_back(Tree());
		float zTranslation = rand() % 117;
		float xTranslation = rand() % 25;
		zTranslations.push_back(zTranslation);
		xTranslations.push_back(xTranslation);
	}
}

void ParkCityBlock::draw() {
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    for (int i = 0; i < numTrees; i++) {
        if (i % 3 == 0) {
            glColor3f(0.0, 0.1, 0.0);
        } else if (i % 3 == 1) {
            glColor3f(0.0, 0.075, 0.0);
        } else {
            glColor3f(0.0, 0.05, 0.0);
        }
        glPushMatrix();
        glTranslatef(xTranslations.at(i) + -4, 0, zTranslations.at(i));
        trees.at(i).draw();
        glPopMatrix();
    }
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}
