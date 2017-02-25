#include "Textures.h"

GLuint textures[textureCount];
string textureFiles[textureCount] = 
{
	"Sun.png",
	"Mercury.png",
	"Venus.png",
	"Earth.png",
	"Mars.png",
	"Jupiter.png",
	"Saturn.png",
	"Uranus.png",
	"Neptune.png",
	"Nebula.png"
};

void Draw2DText(float x, float y, string text)
{
	glRasterPos2f(x,y);
	for(unsigned int i=0; i!=text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}