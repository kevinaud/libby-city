#include "City.h"

City::City(int sizeX, int sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->road = new Road(sizeX, sizeY);
	buildingPiece = new BuildingPiece(25, 12, 12, &textures.building.striped);
	commonBuilding = new CommonBuilding(25, &textures.building.striped);
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
