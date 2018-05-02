#include "City.h"

City::City(int blocksWide, int blocksLong) {
    this->blocksWide = blocksWide;
    this->blocksLong = blocksLong;
    this->width = blocksWide * CITY_BLOCK_WIDTH +
                  (blocksWide + 1) * ROAD_WIDTH;
    this->length = blocksLong * CITY_BLOCK_LENGTH +
                  (blocksLong + 1) * ROAD_WIDTH;

    this->road = new Road(blocksWide, blocksLong);
	//commonBuilding = new CommonBuilding(24, &textures.building.striped);
	cityBlock = new CityBlock(BuildingType::basic);
}

City::~City() {

}

void City::setSkybox(Skybox* skybox) {
    this->skybox = skybox;
}

void City::draw() {
    if (!texturesInitialized) {
        initTextures(); 
    }
    skybox->draw();
    road->draw();
	cityBlock->draw();
}
