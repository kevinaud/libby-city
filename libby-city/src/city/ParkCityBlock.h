#ifndef PARK_CITY_BLOCK_H
#define PARK_CITY_BLOCK_H

#include "CityBlock.h"
#include "../shapes/Cylinder.h"

using namespace std;

class ParkCityBlock : public CityBlock {
    public:
        ParkCityBlock();
		void draw();
	private:
        Cylinder* c;
};

#endif
