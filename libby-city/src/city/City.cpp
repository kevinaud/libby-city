#include "City.h"

City::City(int blocksWide, int blocksLong) {
    this->blocksWide = blocksWide;
    this->blocksLong = blocksLong;
    this->width = blocksWide * CITY_BLOCK_WIDTH +
                  (blocksWide + 1) * ROAD_WIDTH;
    this->length = blocksLong * CITY_BLOCK_LENGTH +
                  (blocksLong + 1) * ROAD_WIDTH;

    this->road = new Road(blocksWide, blocksLong);
	cityBlocks = new CityBlock[blocksWide * blocksLong];

    for (int i = 0; i < blocksLong; i++) {
        for (int j = 0; j < blocksWide; j++) {
            cout << i*blocksLong + j << endl;
            cityBlocks[i*blocksWide + j] = CityBlock(/*getBuildingHeight(i, j)*/);
        }
    }
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
    for (int i = 0; i < blocksLong; i++) {
        for (int j = 0; j < blocksWide; j++) {
            glPushMatrix();
            int translateX = getBuildingOffsetX(i, j);
            int translateZ = getBuildingOffsetZ(i, j);
            glTranslatef(translateX - 8.0, 0, (-1.0 * translateZ) + 8.0);
            cityBlocks[i*blocksWide + j].draw();
            glPopMatrix();
        }
    }
}

int City::getBuildingHeight(int row, int col) {
    return 20;
}

float City::getBuildingOffsetX(int row, int col) {
    int blockOffset = ROAD_WIDTH + CITY_BLOCK_WIDTH;
    int halfMaxOffset = ((blocksWide - 1) / 2) * blockOffset;
    return col * blockOffset - halfMaxOffset; 
}

float City::getBuildingOffsetZ(int row, int col) {
    int blockOffset = ROAD_WIDTH + CITY_BLOCK_LENGTH;
    int halfMaxOffset = ((blocksLong - 1) / 2) * blockOffset;
    return row * blockOffset - halfMaxOffset; 
}
