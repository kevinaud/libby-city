#include "Road.h"

Road::Road(int sizeX, int sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    initialized = false;
}

void Road::draw() {
    if (!initialized) {
        initialize(); 
    }
}

void Road::initialize() {

}
