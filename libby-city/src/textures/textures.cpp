#include "textures.h"

GlobalTextures textures;
bool texturesInitialized = false;

void initTextures() {
    GLubyte baseColor[3] = { 0xFF, 0xFF, 0xFF };
    GLubyte yellowBaseColor[3] = { 0xF7, 0xF6, 0xAA };
    textures.building.scatter = getBuildingTexture(baseColor, BuildingLighting::SCATTER, true);
    textures.building.striped = getBuildingTexture(baseColor, BuildingLighting::STRIPED, true);
    textures.building.yellowScatter = getBuildingTexture(yellowBaseColor, BuildingLighting::SCATTER, false);
    textures.building.yellowStriped = getBuildingTexture(yellowBaseColor, BuildingLighting::STRIPED, false);
    texturesInitialized = true;
}

GLuint getBuildingTexture(GLubyte* baseColor, BuildingLighting lighting, bool noise) {

    int imgSize = 512;
    int width = imgSize, height = imgSize;
    GLubyte* data = generateBuildingTextureData(baseColor, lighting, noise);
    GLuint texture;

    glGenTextures  (1, &texture);
    glBindTexture  (GL_TEXTURE_2D, texture);
    glPixelStorei  (GL_UNPACK_ALIGNMENT, 1);
    //glGenerateMipMap(GL_TEXTURE_2D);
    //glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexImage2D   (
        GL_TEXTURE_2D,    // target texture
        0,                // level-of-detail number
        GL_RGB,           // internal format
        width,            // width of the texture (pixels)
        height,           // height of the texture (pixels)
        0,                // border (must be 0) 
        GL_RGB,           // format of the pixel data
        GL_UNSIGNED_BYTE, // data type of the pixel data 
        data              // pointer to the image data in memory 
    );
    glTexEnvf      (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    free(data);

    return texture;
}

GLubyte* generateBuildingTextureData(GLubyte* baseColor, BuildingLighting lighting, bool noise) {
    int imgSize = 512;
    int width = imgSize, height = imgSize;

    GLubyte* data = new GLubyte[width * height * 3];

    int numWindows = 64;
    int windowSize = 8; // pixels
    int textureWidth = 512;
    int colorSize = 3;

    GLubyte windowColor[3] = { 0x00, 0x00, 0x00 };

    bool lightOn;
    int stripeLength = 0;

    // ITERATE OVER ALL WINDOWS
    for (int x = 0; x < numWindows; x++) {
        for (int y = 0; y < numWindows; y++) {

            // index of top left pixel for current window
            int ndx = (x * windowSize * textureWidth + y * windowSize) * colorSize;
            if (lighting == BuildingLighting::SCATTER) {
                lightOn = (rand() % 4) + 1 == 2; 
            } else if (lighting == BuildingLighting::STRIPED) {
                if (stripeLength > 0) {
                    lightOn = true; 
                    stripeLength--;
                } else if (stripeLength < 0) {
                    lightOn = false; 
                    stripeLength++;
                } else {
                    stripeLength = (rand() % 30) - 15;
                    lightOn = (stripeLength > 0);
                }
            }

            if (lightOn) {
                 lightOnColor(baseColor, windowColor);
            } else {
                 lightOffColor(windowColor);
            }

            // ITERATE OVER ALL PIXELS IN AN INDIVIDUAL WINDOW
            for (int t = 0; t < windowSize; t++) {
                for (int s = 0; s < windowSize; s++) {
                    if (s >= 7 || t >= 7 || s < 1 || t < 1) {
                        data[ndx++] = 0x00;
                        data[ndx++] = 0x00;
                        data[ndx++] = 0x00;
                    } else {
                        if (lightOn) {
                            GLubyte adjustedColor[3];
                            int fade = rand() % (30 * t);
                            for (int i = 0; i < 3; i++) {
                                if (windowColor[i] >= fade) {
                                    adjustedColor[i] = windowColor[i] - fade; 
                                } else {
                                    adjustedColor[i] = 0; 
                                }
                            }
                            /* for (int i = 0; i < 3; i++) { */
                            /*     int noise = ((rand() % 25) - 12); */
                            /*     if (noise > 0) { */
                            /*         if (adjustedColor[i] + noise < adjustedColor[i]) { */
                            /*             adjustedColor[i] = 0xFF; */ 
                            /*         } else { */
                            /*             adjustedColor[i] = adjustedColor[i] + noise; */
                            /*         } */
                            /*     } else if (noise < 0) { */
                            /*         cout << "noise: " << noise << ", adjustedColor: " << (int)adjustedColor[i] << " "; */
                            /*         int test = adjustedColor[i] + noise; */
                            /*         cout << "test: " << test << " "; */
                            /*         if (adjustedColor[i] + noise > adjustedColor[i]) { */
                            /*             adjustedColor[i] = 0x00; */ 
                            /*         } else { */
                            /*             adjustedColor[i] = adjustedColor[i] + noise; */
                            /*         } */
                            /*         cout << "result: " << (int)adjustedColor[i] << endl; */
                            /*     } */
                            /* } */
                            /* adjustedColor[0] = windowColor[0] - fade; */
                            /* adjustedColor[1] = windowColor[1] - fade; */
                            /* adjustedColor[2] = windowColor[2] - fade; */
                            if (noise) {
                                adjustedColor[0] = std::min(adjustedColor[0] + ((rand() % 25) - 12), 255);
                                adjustedColor[1] = std::min(adjustedColor[1] + ((rand() % 25) - 12), 255);
                                adjustedColor[2] = std::min(adjustedColor[2] + ((rand() % 25) - 12), 255);
                            }
                            data[ndx++] = adjustedColor[0];
                            data[ndx++] = adjustedColor[1];
                            data[ndx++] = adjustedColor[2];
                        } else {
                            int fade = rand() % (5 * t);
                            
                            GLubyte adjustedColor[3];
                            if (windowColor[0] > fade) {
                                adjustedColor[0] = windowColor[0] - fade;
                                adjustedColor[1] = windowColor[1] - fade;
                                adjustedColor[2] = windowColor[2] - fade;
                            } else {
                                adjustedColor[0] = 0;
                                adjustedColor[1] = 0;
                                adjustedColor[2] = 0;
                            }
                            data[ndx++] = std::max(adjustedColor[0] + ((rand() % 25) - 12), 0);
                            data[ndx++] = std::max(adjustedColor[1] + ((rand() % 25) - 12), 0);
                            data[ndx++] = std::max(adjustedColor[2] + ((rand() % 25) - 12), 0);
                        }
                    }
                }

                ndx += (textureWidth - windowSize) * 3;
            } 
        }
    }

    return data;
}


void lightOnColor(GLubyte* baseColor, GLubyte* windowColor) {
    int subtract = rand() % 50;
    for (int i = 0; i < 3; i++) {
        if (baseColor[i] > subtract) {
            windowColor[i] = baseColor[i] - subtract; 
        } else {
            windowColor[i] = 0; 
        }
    }
    /* if (baseColor[0] */
    /* windowColor[0] = baseColor[0] - subtract; */
    /* windowColor[1] = baseColor[1] - subtract; */
    /* windowColor[2] = baseColor[2] - subtract; */
}

void lightOffColor(GLubyte* windowColor) {
    int add = rand() % 50;
    windowColor[0] = 0x00 + add;
    windowColor[1] = 0x00 + add;
    windowColor[2] = 0x00 + add;
}

