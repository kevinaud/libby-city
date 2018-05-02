#ifndef ROAD_H
#define ROAD_H

#include <memory>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "CityBlock.h"

#define ROAD_WIDTH 11

using namespace std;

class Road {
    public:
        Road(int blocksWide, int blocksLong);
        void initialize();
        void draw();

    private:
        // dimensions (units)
        int width;
        int length;

        // dimensions (city blocks)
        int blocksWide;
        int blocksLong;

        bool initialized;

        GLubyte*** allocateRoadBuffer();
        GLuint roadTexture;
};

#endif
