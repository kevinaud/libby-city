#include "ParkCityBlock.h"
#include <iostream>

ParkCityBlock::ParkCityBlock() {
	numTrees = rand() % (70 - (30) + 1) + (30);
	for (int i = 0; i < numTrees; i++) {
		trees.push_back(Tree());
		float zTranslation = rand() % 120;
		float xTranslation = rand() % 20;
		zTranslations.push_back(zTranslation);
		xTranslations.push_back(xTranslation);
	}
}

void ParkCityBlock::draw() {
	for (int i = 0; i < numTrees; i++) {
		glPushMatrix();
		glTranslatef(xTranslations.at(i), 0, zTranslations.at(i));
		trees.at(i).draw();
		glPopMatrix();
	}
}