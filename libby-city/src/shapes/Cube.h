#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

GLuint loadBMP(const char * imagepath);
/* GLuint back, front, left, right, up, down; */

class Cube : public Shape {
public:
	Cube() {
    };
	~Cube() {};

    void setTexture(GLuint texture) {
        this->texture = texture; 
    }

	void draw() {
		glPushMatrix(); {
			/* glTranslatef(0.0, 0.0, 0.5); */
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); {
			/* glTranslatef(0.5, 0.0, 0.0); */
			glRotatef(90, 0, 1, 0);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); {
			/* glTranslatef(0.0, 0.0, -0.5); */
			glRotatef(180, 0, 1, 0);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); {
			/* glTranslatef(-0.5, 0.0, 0.0); */
			glRotatef(270, 0, 1, 0);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); {
			/* glTranslatef(0, 0.5, 0.0); */
			glRotatef(270, 1, 0, 0);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); {
			/* glTranslatef(0.0, -0.5, 0.0); */
			glRotatef(90, 1, 0, 0);
			drawCubeFace();
		}
		glPopMatrix();
	};


	void drawNormal() {
		glPushMatrix(); {
			/* glTranslatef(0.0, 0.0, 0.5); */
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			/* glTranslatef(0.5, 0.0, 0.0); */
			glRotatef(90, 0, 1, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			/* glTranslatef(0.0, 0.0, -0.5); */
			glRotatef(180, 0, 1, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			/* glTranslatef(-0.5, 0.0, 0.0); */
			glRotatef(270, 0, 1, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			/* glTranslatef(0, 0.5, 0.0); */
			glRotatef(270, 1, 0, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			/* glTranslatef(0.0, -0.5, 0.0); */
			glRotatef(90, 1, 0, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
	};

private:

    GLuint texture;

	void drawCubeFace() {
		float width = 1.0f / (float)m_segmentsX;
		float height = 1.0f / (float)m_segmentsY;
		float startX = -0.5f;
		float startY = -0.5f;
        float size = 0.5f;

	    glColor3f(1,1,1);	
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, -1.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-size,  size,  size);
            glTexCoord2f(1.0, 0.0); glVertex3f( size,  size,  size);
            glTexCoord2f(1.0, 1.0); glVertex3f( size, -size,  size);
            glTexCoord2f(0.0, 1.0); glVertex3f(-size, -size,  size);
        glEnd();

		/* glBegin(GL_TRIANGLES); */
		/* for (int i = 0; i < m_segmentsX; i++) { */
		/* 	float xcoord = startX + (i*width); */
		/* 	for (int j = 0; j < m_segmentsY; j++) { */
		/* 		float ycoord = startY + (j*height); */
		/* 		glNormal3f(0, 0, 1); */
		/* 		glVertex3d(xcoord, ycoord, 0); */
		/* 		glVertex3d(xcoord + width, ycoord, 0); */
		/* 		glVertex3d(xcoord + width, ycoord + height, 0); */

		/* 		glNormal3f(0, 0, 1); */
		/* 		glVertex3d(xcoord + width, ycoord + height, 0); */
		/* 		glVertex3d(xcoord, ycoord + height, 0); */
		/* 		glVertex3d(xcoord, ycoord, 0); */
		/* 	} */
		/* } */
		glEnd();
	}

	void drawCubeFaceNormal() {
		float width = 1.0f / (float)m_segmentsX;
		float height = 1.0f / (float)m_segmentsY;
		float startX = -0.5f;
		float startY = -0.5f;

		glBegin(GL_LINES);
		for (int i = 0; i < m_segmentsX; i++) {
			float xcoord = startX + (i*width);
			for (int j = 0; j < m_segmentsY; j++) {
				float ycoord = startY + (j*height);
				glVertex3d(xcoord, ycoord, 0); glVertex3d(xcoord, ycoord, 0.1); 
				glVertex3d(xcoord + width, ycoord, 0); glVertex3d(xcoord + width, ycoord, 0.1);
				glVertex3d(xcoord + width, ycoord + height, 0); glVertex3d(xcoord + width, ycoord + height, 0.1);

				glVertex3d(xcoord + width, ycoord + height, 0); glVertex3d(xcoord + width, ycoord + height, 0.1);
				glVertex3d(xcoord, ycoord + height, 0); glVertex3d(xcoord, ycoord + height, 0.1); 
				glVertex3d(xcoord, ycoord, 0); glVertex3d(xcoord, ycoord, 0.1);
			}
		}
		glEnd();
	}
};

/* GLuint loadBMP(const char * imagepath) { */

/* 	GLuint texture; */
/* 	int width = 1024, height = 512; */
/* 	unsigned char * data; */

/* 	FILE * file; */
/* 	file = fopen(imagepath, "rb"); */

/* 	if (file == NULL) { */
/*         return 0; */
/* 	} */

/* 	data = (unsigned char *)malloc( width * height * 3); */
/* 	//int size = fseek(file,); */
/* 	fread(data, width * height * 3, 1, file); */
/* 	fclose(file); */

/* 	for (int i = 0; i < width * height ; ++i) { */
/* 		int index = i*3; */
/* 		unsigned char B,R; */
/* 		B = data[index]; */
/* 		R = data[index + 2]; */

/* 		data[index] = R; */
/* 		data[index + 2] = B; */
/* 	} */

/* 	glGenTextures(1, &texture); */
/* 	glBindTexture(GL_TEXTURE_2D, texture); */
/* 	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE); */
/* 	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); */


/* 	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR); */
/* 	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT); */
/* 	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT); */
/* 	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data); */
/* 	free(data); */

/* 	return texture; */
/* } */
#endif
