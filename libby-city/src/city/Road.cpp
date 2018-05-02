#include "Road.h"

Road::Road(int blocksWide, int blocksLong) {
    this->blocksWide = blocksWide;
    this->blocksLong = blocksLong;
    this->width = blocksWide * CITY_BLOCK_WIDTH +
                  (blocksWide + 1) * ROAD_WIDTH;
    this->length = blocksLong * CITY_BLOCK_LENGTH +
                  (blocksLong + 1) * ROAD_WIDTH;

    initialized = false;
}

void Road::draw() {
    if (!initialized) {
        initialize(); 
        cout << width << endl;
        cout << length << endl;
    }
    
    float size = 2.0f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, roadTexture);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0);
        /* glTexCoord2f(0.0, 0.0); glVertex3f(-size,  size,  size); */
        /* glTexCoord2f(1.0, 0.0); glVertex3f( size,  size,  size); */
        /* glTexCoord2f(1.0, 1.0); glVertex3f( size, -size,  size); */
        /* glTexCoord2f(0.0, 1.0); glVertex3f(-size, -size,  size); */
        glTexCoord2f(0.0, 0.0); glVertex3f(-width / 2.0, 0,  length / 2.0);
        glTexCoord2f(1.0, 0.0); glVertex3f( width / 2.0, 0,  length / 2.0);
        glTexCoord2f(1.0, 1.0); glVertex3f( width / 2.0, 0, -length / 2.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-width / 2.0, 0, -length / 2.0);
    glEnd();
}

typedef unique_ptr<GLubyte[]> GLubyteArray;
typedef unique_ptr<GLubyteArray[]> GLubyteArray2D;

void Road::initialize() {
    //GLubyte*** roadBuffer = allocateRoadBuffer();
    auto roadBuffer = unique_ptr<GLubyteArray2D[]>(new GLubyteArray2D[length]);
    for (int i = 0; i < length; i++) {
        roadBuffer[i] = GLubyteArray2D(new GLubyteArray[width]);
        for (int j = 0; j < width; j++) {
            roadBuffer[i][j] = GLubyteArray(new GLubyte[3]); 
        }
    }

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                if (j % 2 == 1) {
                    roadBuffer[i][j][k] = 0x00;
                } else {
                    roadBuffer[i][j][k] = 0x33;
                }
            }
        }
    }

    int offset = 0;
    for (int i = 0; i < blocksWide + 1; i++) {
        for (int j = 0; j < ROAD_WIDTH; j++) {
            for (int k = 0; k < length; k++) {
                if (j < 2 || j == 5 || j >=9) {
                    roadBuffer[k][offset + j][0] = 0xA5;
                    roadBuffer[k][offset + j][1] = 0xA5;
                    roadBuffer[k][offset + j][2] = 0x9F;
                } else {
                    roadBuffer[k][offset + j][0] = 0x63;
                    roadBuffer[k][offset + j][1] = 0x63;
                    roadBuffer[k][offset + j][2] = 0x63;
                }
            } 
        } 
        offset += ROAD_WIDTH + CITY_BLOCK_WIDTH;
    }

    offset = 0;
    for (int i = 0; i < blocksLong + 1; i++) {
        for (int j = 0; j < ROAD_WIDTH; j++) {
            for (int k = 0; k < width; k++) {
                roadBuffer[offset + j][k][0] = 0xA5;
                roadBuffer[offset + j][k][1] = 0xA5;
                roadBuffer[offset + j][k][2] = 0x9F;
            } 
        } 
        offset += ROAD_WIDTH + CITY_BLOCK_LENGTH;
    }

    GLubyte* data = new GLubyte[width * length * 3];

    cout << width * length * 3 << endl;

    int count = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                data[count] = roadBuffer[i][j][k];
                count++;
            }
        }
    }

    cout << "count " << count << endl;

    for (int i = 0; i < width * length * 3; i++) {
        //data[i] = 0x33;
        /* int t = data[i]; */
        /* cout << t << endl; */ 
    }

    GLuint texture;

    glGenTextures  (1, &texture);
    glBindTexture  (GL_TEXTURE_2D, texture);
    glPixelStorei  (GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D   (
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        length,
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

    roadTexture = texture;

    initialized = true;
}

GLubyte*** Road::allocateRoadBuffer() {
    GLubyte*** roadBuffer = new GLubyte**[length];
    /* for (int i = 0; i < height; i++) { */
    /*     roadBuffer[i] = new GLubyte*[width]; */
    /*     for (int j = 0; j < width; j++) { */
    /*         roadBuffer[i][j] = new GLubyte[3]; */
    /*     } */ 
    /* } */
    return roadBuffer;
}

void freeRoadBuffer() {

}
