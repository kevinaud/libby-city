#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../util/bmpread.h"

#define NUM_WINDOWS 64
#define WINDOW_UNIT_SIZE 1.0/64.0

using namespace std;

/**
 * data types
 */
struct GlobalTextures {
    struct BuildingTextures {
        GLuint scatter;
        GLuint striped;
    };
    
    BuildingTextures building;
    bool initialized;
};

enum BuildingLighting {
   SCATTER,
   STRIPED
};

/**
 * global variables
 */
extern GlobalTextures textures;
extern bool texturesInitialized;

/**
 * function definitions
 */
void initTextures();

GLubyte* generateBuildingTextureData(BuildingLighting lighting);
GLuint getBuildingTexture(BuildingLighting lighting);

void lightOnColor(GLubyte* windowColor);
void lightOffColor(GLubyte* windowColor);


#endif
