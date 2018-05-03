#ifndef BUILDING_CITY_BLOCK_H
#define BUILDING_CITY_BLOCK_H

#include "../shapes/CommonBuilding.h"
#include "../shapes/BasicBuilding.h"
#include "CityBlock.h"

enum BuildingType { basic, common };

using namespace std;

class BuildingCityBlock : public CityBlock {
    public:
        BuildingCityBlock() : BuildingCityBlock(BuildingType::basic) {};
        BuildingCityBlock(BuildingType buildingType);
		BuildingCityBlock(BuildingType buildingType, int maxBuildingHeight);
		void draw();
	private:
		vector<Building*> buildings;

};

#endif
