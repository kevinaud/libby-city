#include "City.h"

City::City(int blocksWide, int blocksLong) {
    this->blocksWide = blocksWide;
    this->blocksLong = blocksLong;
    this->width = blocksWide * CITY_BLOCK_WIDTH +
                  (blocksWide + 1) * ROAD_WIDTH;
    this->length = blocksLong * CITY_BLOCK_LENGTH +
                  (blocksLong + 1) * ROAD_WIDTH;

    this->road = new Road(blocksWide, blocksLong);
	//cityBlocks = new CityBlock[blocksWide * blocksLong];

    for (int i = 0; i < blocksLong; i++) {
        for (int j = 0; j < blocksWide; j++) {
            if (rand() % 8 != 1) {
                BuildingType type;

                /* if (rand() % 2 == 1) { */
                    type = BuildingType::common; 
                /* } else { */
                /*     type = BuildingType::basic; */ 
                /* } */

                cityBlocks.push_back(new BuildingCityBlock(type, getBuildingHeight(i, j)));
            } else {
                cityBlocks.push_back(new ParkCityBlock());
            }
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
            glTranslatef(translateX - 8.0, 0, (-1.0 * translateZ) + 13.0);
            cityBlocks[i*blocksWide + j]->draw();
            glPopMatrix();
        }
    }
	
	//commonBuilding->draw();
	//tree->draw();
	//cone->draw();
	//cityBlock->draw();
	//parkCityBlock->draw();

}

int City::getBuildingHeight(int row, int col) {
    float a = 55;
    float b = blocksWide / 2.0;
    float c = 2;

    float colResult = gaussianDist(col, a, b, c);

    b = blocksLong / 2.0;
    c *= blocksLong / (1.0 * blocksWide);
    float rowResult = gaussianDist(row, a, b, c);

    float result = min(colResult, rowResult);
    result += 10;

    return result;
}

float City::gaussianDist(float x, float a, float b, float c) {

    float e = 2.71828;

    float top = pow(x-b, 2);
    float bot = 2 * pow(c,2.0);
    float exp = -1.0 * (top / bot);
    float result = pow(e, exp);
    result = a * result;

    return result;
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
