#ifndef CITY_H
#define CITY_H

#include "shapes/Skybox.h"
#include "textures/textures.h"

using namespace std;

class City {
    public:
        City();
        ~City();

        void setSkybox(Skybox* skybox);

        void draw();

    private:
        Skybox* skybox;
};

#endif
