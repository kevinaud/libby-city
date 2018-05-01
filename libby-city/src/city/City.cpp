#include "City.h"

City::City() {

}

City::~City() {

}

void City::setSkybox(Skybox* skybox) {
    this->skybox = skybox;
}

void City::draw() {
    skybox->draw();
}
