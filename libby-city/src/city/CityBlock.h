#ifndef CITY_BLOCK_H
#define CITY_BLOCK_H

#define CITY_BLOCK_WIDTH 32
#define CITY_BLOCK_LENGTH 128
#define BUILDING_LENGTH 16 

#include "../shapes/CommonBuilding.h"
#include "../shapes/BasicBuilding.h"

enum BuildingType { basic, common };

using namespace std;

class CityBlock {
    public:
        CityBlock(BuildingType buildingType);
		CityBlock(BuildingType buildingType, int maxBuildingHeight);
		void draw();
	private:
		vector<Building*> buildings;

};

#endif
