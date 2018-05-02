#include "CityBlock.h"
#include <iostream>

CityBlock::CityBlock(BuildingType buildingType) {
	if (buildingType == BuildingType::common) {
		for (int i = 0; i < 16; i++) {
			buildings.push_back(new CommonBuilding(50, &textures.building.striped));
		}
	}
	else {
		for (int i = 0; i < 16; i++) {
			buildings.push_back(new BasicBuilding(50, &textures.building.striped));
		}
	}
}

CityBlock::CityBlock(BuildingType buildingType, int maxBuildingHeight) {
	if (buildingType == BuildingType::common) {
		for (int i = 0; i < 16; i++) {
			buildings.push_back(new CommonBuilding(maxBuildingHeight, &textures.building.striped));
		}
	}
	else {
		for (int i = 0; i < 16; i++) {
			buildings.push_back(new BasicBuilding(maxBuildingHeight, &textures.building.striped));
		}
	}
}

void CityBlock::draw() {
	for (int i = 0; i < 8; i++) {
		glPushMatrix();
			glTranslatef(0, 0, BUILDING_LENGTH*i);
			buildings.at(i)->draw();
		glPopMatrix();
	}
	for (int i = 8; i < 16; i++) {
		glPushMatrix();
			glTranslatef(BUILDING_LENGTH, 0, BUILDING_LENGTH*(i-8));
			buildings.at(i)->draw();
		glPopMatrix();
	}
}
