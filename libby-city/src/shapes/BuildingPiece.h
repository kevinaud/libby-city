#ifndef BUILDINGPIECE_H
#define BUILDINGPIECE_H

#include "Shape.h"
#include <ctime>

#define WINDOW_SIZE 1

enum FaceType { XY, YZ, XZ, _XY, _YZ, _XZ };

struct TexturePoint {
	float x;
	float y;
};

struct Face {
	FaceType faceType;
	int floors;
	int columns;
	float height;
	float width;
	TexturePoint textureCoordinates[4];
};

class BuildingPiece : public Shape {
public:
	BuildingPiece() {
		srand(time(0));
		texture = 0;
	};

	BuildingPiece(int floors, int columns_width, int columns_length, GLuint textureInt) {
		srand(time(0));
		this->texture = textureInt;
		this->columns_length = (float)columns_length*WINDOW_SIZE;
		this->columns_width = (float)columns_width*WINDOW_SIZE;
		this->height = (float)floors*WINDOW_SIZE;
		
		faces[XY].faceType = XY;
		faces[XY].columns = columns_width;
		faces[XY].floors = floors;
		faces[XY].height = floors*WINDOW_SIZE;
		faces[XY].width = columns_width*WINDOW_SIZE;
		defineTextureCoordinates(faces[XY]);
		//faces[XY].textureCoordinates = ...

		faces[_XY].faceType = _XY;
		faces[_XY].columns = columns_width;
		faces[_XY].floors = floors;
		faces[_XY].height = floors*WINDOW_SIZE;
		faces[_XY].width = columns_width*WINDOW_SIZE;
		defineTextureCoordinates(faces[_XY]);

		faces[YZ].faceType = YZ;
		faces[YZ].columns = columns_length;
		faces[YZ].floors = floors;
		faces[YZ].height = floors*WINDOW_SIZE;
		faces[YZ].width = columns_length*WINDOW_SIZE;
		defineTextureCoordinates(faces[YZ]);

		faces[_YZ].faceType = _YZ;
		faces[_YZ].columns = columns_length;
		faces[_YZ].floors = floors;
		faces[_YZ].height = floors*WINDOW_SIZE;
		faces[_YZ].width = columns_length*WINDOW_SIZE;
		defineTextureCoordinates(faces[_YZ]);

		faces[XZ].faceType = XZ;
		faces[XZ].height = columns_length*WINDOW_SIZE;
		faces[XZ].width = columns_width*WINDOW_SIZE;

		faces[_XZ].faceType = _XZ;
		faces[_XZ].height = columns_length*WINDOW_SIZE;
		faces[_XZ].width = columns_width*WINDOW_SIZE;

	};

	~BuildingPiece() {};

	void draw() {
		glEnable(GL_TEXTURE_2D);
		glPushMatrix(); { // XY
			glTranslatef(0, 0, columns_length / 2);
			glTranslatef(0, height/2, 0);
			drawCubeFace(faces[XY]);
		}
		glPopMatrix();
		glPushMatrix(); { // -XY
			glRotatef(180, 0, 1, 0);
			glTranslatef(0, 0, columns_length / 2);
			glTranslatef(0, height / 2, 0);
			drawCubeFace(faces[_XY]);
		}
		glPopMatrix();
		glPushMatrix(); { // YZ
			glRotatef(90, 0, 1, 0);
			glTranslatef(0, 0, columns_width / 2);
			glTranslatef(0, height / 2, 0);
			drawCubeFace(faces[YZ]);
		}
		glPopMatrix();
		glPushMatrix(); { // -YZ
			glRotatef(270, 0, 1, 0);
			glTranslatef(0, 0, columns_width / 2);
			glTranslatef(0, height / 2, 0);
			drawCubeFace(faces[_YZ]);
		}
		glPopMatrix();
		glPushMatrix(); { // XZ
			glTranslatef(0, height / 2, 0);
			glRotatef(270, 1, 0, 0);
			glTranslatef(0, 0, height / 2);
			drawCubeFace(faces[XZ]);
		}
		glPopMatrix();
		glPushMatrix(); { // -XZ
			glTranslatef(0, height / 2, 0);
			glRotatef(90, 1, 0, 0);
			glTranslatef(0, 0, height / 2);
			drawCubeFace(faces[_XZ]);
		}
		glPopMatrix();
	};

private:

	GLuint texture;
	Face faces[6];
	float columns_length;
	float columns_width;
	float height;

	void defineTextureCoordinates(Face &face) {
		float originX = (rand() % (NUM_WINDOWS - face.columns))*WINDOW_UNIT_SIZE;
		float originY = (rand() % (NUM_WINDOWS - face.floors))*WINDOW_UNIT_SIZE;
		
		face.textureCoordinates[0].x = originX;
		face.textureCoordinates[0].y = originY;

		face.textureCoordinates[1].x = originX + face.columns*WINDOW_UNIT_SIZE;
		face.textureCoordinates[1].y = originY;

		face.textureCoordinates[2].x = originX + face.columns*WINDOW_UNIT_SIZE;
		face.textureCoordinates[2].y = originY + face.floors*WINDOW_UNIT_SIZE;

		face.textureCoordinates[3].x = originX;
		face.textureCoordinates[3].y = originY + face.floors*WINDOW_UNIT_SIZE;
	}

	void drawCubeFace(Face face) {
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);

		if (face.faceType == XZ || face.faceType == _XZ) {
			glVertex3f(-face.width / 2.0, face.height / 2.0, 0);
			glVertex3f(face.width / 2.0, face.height / 2.0, 0);
			glVertex3f(face.width / 2.0, -face.height / 2.0, 0);
			glVertex3f(-face.width / 2.0, -face.height / 2.0, 0);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexCoord2f(face.textureCoordinates[0].x, face.textureCoordinates[0].y); glVertex3f(-face.width / 2.0, face.height / 2.0, 0);
			glTexCoord2f(face.textureCoordinates[1].x, face.textureCoordinates[1].y); glVertex3f(face.width / 2.0, face.height / 2.0, 0);
			glTexCoord2f(face.textureCoordinates[2].x, face.textureCoordinates[2].y); glVertex3f(face.width / 2.0, -face.height / 2.0, 0);
			glTexCoord2f(face.textureCoordinates[3].x, face.textureCoordinates[3].y); glVertex3f(-face.width / 2.0, -face.height / 2.0, 0);
		}
		
		glEnd();
	}
};

#endif
