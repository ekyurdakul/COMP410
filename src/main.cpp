#include "main.h"

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(g_WindowWidth, g_WindowHeight);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH)-g_WindowWidth)/2.0,
		(glutGet(GLUT_SCREEN_HEIGHT)-g_WindowHeight)/2.0
		);
	glutCreateWindow("COMP 410 Term Project");

	glutIdleFunc(IdleCallback);
	glutKeyboardFunc(KeyboardCallback);
	glutKeyboardUpFunc(KeyboardKeyUpCallback);
	glutSpecialFunc(SpecialKeysCallback);
	glutSpecialUpFunc(SpecialKeyUpCallback);
	glutReshapeFunc(ReshapeCallback);
	glutDisplayFunc(DisplayCallback);

	glutFullScreen();

	for(int i=0; i<256; i++)
	{
		NormalKeyboardKeys[i] = false;
		SpecialKeyboardKeys[i] = false;
	}

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	GLfloat global_ambient[] = { 2.0, 2.0, 2.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(textureCount, textures);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	for(int i=0; i<textureCount; i++)
	{
		vector<unsigned char> image;
		unsigned width, height;
		unsigned error = lodepng::decode(image, width, height, textureFiles[i]);
		if(error != 0)
			continue;

		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	}

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutMainLoop();

	return 0;
}

void DrawObjects()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	sky->Draw();

	GLfloat emission[] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	
	sun->Draw();
	mercury->Draw();
	venus->Draw();
	earth->Draw();
	mars->Draw();
	jupiter->Draw();
	saturn->Draw();
	uranus->Draw();
	neptun->Draw();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
}

void IdleCallback()
{
	float dt = animationDT;
	sun->Animate(dt);
	mercury->Animate(dt);
	venus->Animate(dt);
	earth->Animate(dt);
	mars->Animate(dt);
	jupiter->Animate(dt);
	saturn->Animate(dt);
	uranus->Animate(dt);
	neptun->Animate(dt);
	c->CheckForTeapotDiscovery();
	glutPostRedisplay();
}

void DisplayCallback()
{
	fps->StartCounting();
	ProcessInputKeys();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, g_WindowWidth, g_WindowHeight);
	gluPerspective(65.0, (float)g_WindowWidth/(float)g_WindowHeight, 0.001, 100000000.0);

	c->SetupProjection();


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DrawObjects();

	fps->StopCounting();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	Draw2DText(-1, 0.95, fps->GetFPSString());
	stringstream ss;
	ss << "Teapots found " << c->teapotsFound << " / 9";
	Draw2DText(-0.125, -0.95, ss.str());


	glutSwapBuffers();
}

void ReshapeCallback(int w, int h)
{
	g_WindowWidth = w;
	g_WindowHeight = h;
}

void ProcessInputKeys()
{
	if(NormalKeyboardKeys[27])
		exit(0);
	if(NormalKeyboardKeys['j'])
	{
		c->JumpToLightspeed();
		return;
	}
	if(SpecialKeyboardKeys[GLUT_KEY_F4])
		c->Teleport(1);
	if(SpecialKeyboardKeys[GLUT_KEY_F5])
		c->Teleport(2);
	if(SpecialKeyboardKeys[GLUT_KEY_F6])
		c->Teleport(3);
	if(SpecialKeyboardKeys[GLUT_KEY_F7])
		c->Teleport(4);
	if(SpecialKeyboardKeys[GLUT_KEY_F8])
		c->Teleport(5);
	if(SpecialKeyboardKeys[GLUT_KEY_F9])
		c->Teleport(6);
	if(SpecialKeyboardKeys[GLUT_KEY_F10])
		c->Teleport(7);
	if(SpecialKeyboardKeys[GLUT_KEY_F11])
		c->Teleport(8);

	if(NormalKeyboardKeys['1'])
		c->MoveUp();
	if(NormalKeyboardKeys['2'])
		c->MoveDown();
	if(NormalKeyboardKeys['a'])
		c->MoveLeft();
	if(NormalKeyboardKeys['d'])
		c->MoveRight();
	if(NormalKeyboardKeys['w'])
		c->MoveForward();
	if(NormalKeyboardKeys['s'])
		c->MoveBackward();
	if(NormalKeyboardKeys['q'])
		c->YawLeft();
	if(NormalKeyboardKeys['e'])
		c->YawRight();
	if(SpecialKeyboardKeys[GLUT_KEY_UP])
		c->PitchDown();
	if(SpecialKeyboardKeys[GLUT_KEY_DOWN])
		c->PitchUp();
	if(SpecialKeyboardKeys[GLUT_KEY_LEFT])
		c->RollLeft();
	if(SpecialKeyboardKeys[GLUT_KEY_RIGHT])
		c->RollRight();
	if(SpecialKeyboardKeys[GLUT_KEY_F1])
		animationDT += animationDTIncrement;
	if(SpecialKeyboardKeys[GLUT_KEY_F2])
		animationDT -= animationDTIncrement;
}

void KeyboardCallback(unsigned char key,int x, int y)
{
	if(key == 'j' && NormalKeyboardKeys['j'])
		NormalKeyboardKeys[key] = false;
	else
		NormalKeyboardKeys[key] = true;

	if(NormalKeyboardKeys['b'])
		sky->draw = !sky->draw;
}

void SpecialKeysCallback(int key,int x, int y)
{
	SpecialKeyboardKeys[key] = true;
}

void KeyboardKeyUpCallback(unsigned char key, int x, int y)
{  
	if(key!='j')
		NormalKeyboardKeys[key] = false;
}

void SpecialKeyUpCallback(int key, int x, int y)
{
	SpecialKeyboardKeys[key] = false;
}