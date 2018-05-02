#ifndef CITY_BLOCK_H
#define CITY_BLOCK_H

#define CITY_BLOCK_WIDTH 32
#define CITY_BLOCK_LENGTH 128
#define BUILDING_LENGTH 16 

#include "../shapes/CommonBuilding.h"

using namespace std;

class CityBlock {
    public:
        CityBlock();
		CityBlock(int maxBuildingHeight);
		void draw();
	private:
		vector<CommonBuilding> buildings;

};

#endif
