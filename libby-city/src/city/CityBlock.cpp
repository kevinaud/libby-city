#include "CityBlock.h"

CityBlock::CityBlock() {
	for (int i = 0; i < 6; i++) {
		buildings.push_back(CommonBuilding(50, &textures.building.striped));
	}
}

CityBlock::CityBlock(int maxBuildingHeight) {
	for (int i = 0; i < 6; i++) {
		buildings.push_back(CommonBuilding(maxBuildingHeight, &textures.building.striped));
	}
}

void CityBlock::draw() {
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
			glTranslatef(0, 0, BUILDING_LENGTH*i);
			buildings.at(i).draw();
		glPopMatrix();
	}
	for (int i = 3; i < 6; i++) {
		glPushMatrix();
			glTranslatef(BUILDING_LENGTH, 0, BUILDING_LENGTH*(i-3));
			buildings.at(i).draw();
		glPopMatrix();
	}
}
