#ifndef CITY_H
#define CITY_H

#include "shapes/Skybox.h"
#include "textures/textures.h"
#include "Road.h"

using namespace std;

class City {
    public:
        City(int sizeX, int sizeY);
        ~City();

        void setSkybox(Skybox* skybox);

        void draw();

    private:
        // dimensions
        int sizeX;
        int sizeY;

        // skybox
        Skybox* skybox;

        // road
        Road* road;
};

#endif
