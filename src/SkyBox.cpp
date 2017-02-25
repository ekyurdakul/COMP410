#include "SkyBox.h"

SkyBox::SkyBox() :
    draw(true)
{

}

void SkyBox::Draw()
{
    if(!draw)
        return;

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textures[9]);
    glTranslatef(c->position.x, c->position.y, c->position.z);
    glutSolidSphere(10000.0, sphereSlice, sphereStack);
    glPopMatrix();
}

SkyBox* sky = new SkyBox();