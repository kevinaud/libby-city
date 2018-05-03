#include "ParkCityBlock.h"

ParkCityBlock::ParkCityBlock() {
    c = new Cylinder();
}

void ParkCityBlock::draw() {
    c->draw();
}
