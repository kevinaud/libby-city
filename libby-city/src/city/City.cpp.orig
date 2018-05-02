#include "City.h"

<<<<<<< HEAD
City::City(int blocksWide, int blocksLong) {
    this->blocksWide = blocksWide;
    this->blocksLong = blocksLong;
    this->width = blocksWide * CITY_BLOCK_WIDTH +
                  (blocksWide + 1) * ROAD_WIDTH;
    this->length = blocksLong * CITY_BLOCK_LENGTH +
                  (blocksLong + 1) * ROAD_WIDTH;

    this->road = new Road(blocksWide, blocksLong);
=======
City::City(int sizeX, int sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->road = new Road(sizeX, sizeY);
	buildingPiece = new BuildingPiece(25, 12, 12, &textures.building.striped);
	commonBuilding = new CommonBuilding(25, &textures.building.striped);
>>>>>>> 01e8039... I think i finished CommonBuilding
}

City::~City() {

}

void City::setSkybox(Skybox* skybox) {
    this->skybox = skybox;
}

void City::draw() {
    if (!texturesInitialized) {
        initTextures(); 
		cout << "test" << endl;
    }
    //skybox->draw();
    //road->draw();
	//buildingPiece->draw();
	commonBuilding->draw();
}
