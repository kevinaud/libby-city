#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "../util/bmpread.h"

enum BuildingLighting {
   SCATTER,
   STRIPED
};

void lightOnColor(GLubyte* windowColor) {
    int subtract = rand() % 50;
    windowColor[0] = 0xFF - subtract;
    windowColor[1] = 0xFF - subtract;
    windowColor[2] = 0xFF - subtract;
}

void lightOffColor(GLubyte* windowColor) {
    int add = rand() % 50;
    windowColor[0] = 0x00 + add;
    windowColor[1] = 0x00 + add;
    windowColor[2] = 0x00 + add;
}

GLubyte* generateBuildingTexture(BuildingLighting lighting) {
    int imgSize = 512;
    int width = imgSize, height = imgSize;

    GLubyte* data = new GLubyte[width * height * 3];
    GLubyte *loc;
    int s, t;

    int numWindows = 64;
    int windowSize = 8; // pixels
    int textureWidth = 512;
    int colorSize = 3;

    int wndx = 0;
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
                    std::cout << stripeLength << std::endl;
                    lightOn = (stripeLength > 0);
                }
            }

            if (lightOn) {
                 lightOnColor(windowColor);
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
                            adjustedColor[0] = windowColor[0] - fade;
                            adjustedColor[1] = windowColor[1] - fade;
                            adjustedColor[2] = windowColor[2] - fade;
                            data[ndx++] = std::min(adjustedColor[0] + ((rand() % 25) - 12), 255);
                            data[ndx++] = std::min(adjustedColor[1] + ((rand() % 25) - 12), 255);
                            data[ndx++] = std::min(adjustedColor[2] + ((rand() % 25) - 12), 255);
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

GLuint getSideTexture(BuildingLighting lighting) {

    int imgSize = 512;
    int width = imgSize, height = imgSize;
    GLubyte* data = generateBuildingTexture(lighting);
    GLuint texture;

    glGenTextures  (1, &texture);
    glBindTexture  (GL_TEXTURE_2D, texture);
    glPixelStorei  (GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D   (
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        data
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf      (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    free(data);

    return texture;
}
