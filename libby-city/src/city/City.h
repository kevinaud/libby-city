#ifndef CITY_H
#define CITY_H

#include "../shapes/Skybox.h"
#include "../textures/textures.h"
#include "../shapes/CommonBuilding.h"
#include "Road.h"
#include "CityBlock.h"

using namespace std;

class City {
    public:
        City(int blocksWide, int blocksLong);
        ~City();

        void setSkybox(Skybox* skybox);

        void draw();

    private:
        // dimensions (units)
        int width;
        int length;

        // dimensions (city blocks)
        int blocksWide;
        int blocksLong;

        // skybox
        Skybox* skybox;

        // road
        Road* road;

		BuildingPiece* buildingPiece;
		CommonBuilding* commonBuilding;
};

#endif
