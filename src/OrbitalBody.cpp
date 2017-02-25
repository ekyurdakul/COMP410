#include "OrbitalBody.h"

OrbitalBody::OrbitalBody(float dFromSun, float size, GLuint textureID, float inclination, float orbitalperiod, float rotationperiod)
{
    this->position = new Point(dFromSun, sin(inclination*3.14/180) * dFromSun ,0);
    this->size = size * 2.5;
    this->textureID = textureID;
    animationAngle = 0;
    this->orbitalperiod = orbitalperiod;
    this->rotationperiod = rotationperiod;
    foundTeapot = false;
    teapotLoc = new Point(dFromSun, this->size + 1, 0);
    currentPos = new Point(this->position->x, this->position->y, this->position->z);
}

void OrbitalBody::Draw()
{
    if(!foundTeapot)
    {
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textures[9]);
        glTranslatef(teapotLoc->x, teapotLoc->y, teapotLoc->z);
        glutSolidTeapot(0.1);
        glPopMatrix();
    }

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textures[textureID]);
    glRotatef(animationAngle, 0.0, 1.0, 0.0);

    glTranslatef(-position->x, -position->y, 0);
    glRotatef(selfRotAngle, 0,1,0);
    glTranslatef(position->x, position->y, 0);

    glTranslatef(position->x, position->y, 0);
    glutSolidSphere(size, sphereSlice, sphereStack);
    
    GLfloat matrix[16]; 
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    currentPos->x = matrix[12];
    currentPos->y = matrix[13];
    currentPos->z = matrix[14];
    glPopMatrix();
}

void OrbitalBody::Animate(double dt)
{
    if(orbitalperiod != 0)
        animationAngle += dt * 2 * 3.14 / orbitalperiod;
    if(selfRotAngle != 0)
        selfRotAngle += dt * 2 * 3.14 / rotationperiod;
}

OrbitalBody* sun = new OrbitalBody(0, 109, 0, 0, 0, 25.4);
OrbitalBody* mercury = new OrbitalBody(585, 0.4, 1, 3.38, 0.2, 58.6);
OrbitalBody* venus = new OrbitalBody(1080, 0.9, 2, 3.86, 0.6, -243);
OrbitalBody* earth = new OrbitalBody(1500, 1, 3, 7.155, 1,1);
OrbitalBody* mars = new OrbitalBody(2280, 0.5, 4, 5.65, 1.9, 1);
OrbitalBody* jupiter = new OrbitalBody(7800, 11.2, 5, 6.09, 11.9, 0.4);
OrbitalBody* saturn = new OrbitalBody(14310, 9.4, 6, 5.51, 29.4, 0.4);
OrbitalBody* uranus = new OrbitalBody(28785, 4, 7, 6.48, 84, -0.7);
OrbitalBody* neptun = new OrbitalBody(45105, 3.9, 8, 6.43, 164.8, 0.7);