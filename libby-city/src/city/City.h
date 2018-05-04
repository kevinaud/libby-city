#ifndef CITY_H
#define CITY_H

#include <vector>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../shapes/Skybox.h"
#include "../textures/textures.h"
#include "Road.h"
#include "CityBlock.h"
#include "BuildingCityBlock.h"
#include "ParkCityBlock.h"
#include "../shapes/Tree.h"

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

		//Tree* tree = new Tree();
		//CommonBuilding* commonBuilding = new CommonBuilding(30, &textures.building.striped);
		//BuildingCityBlock* cityBlock = new BuildingCityBlock(BuildingType::common);
		//Cone* cone = new Cone();
		//ParkCityBlock* parkCityBlock = new ParkCityBlock();

		vector<CityBlock*> cityBlocks;

        int getBuildingHeight(int row, int col);
        float gaussianDist(float x, float a, float b, float c);

        float getBuildingOffsetX(int row, int col);
        float getBuildingOffsetZ(int row, int col);
};

#endif
