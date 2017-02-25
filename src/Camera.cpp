#include "Camera.h"

Camera::Camera() :
    speed(0.05),
    angle(0.01),
    lightspeedmult(50),
    followPlanet(false),
    following(nullptr),
    position(0,0,-1200),
    forward(0, 0, -1),
    normal(0, 1, 0),
    side(1, 0, 0),
    teapotsFound(0)
{
    planets.push_back(sun);
    planets.push_back(mercury);
    planets.push_back(venus);
    planets.push_back(earth);
    planets.push_back(mars);
    planets.push_back(jupiter);
    planets.push_back(saturn);
    planets.push_back(uranus);
    planets.push_back(neptun);
}

void Camera::PitchDown()
{
    forward = normalizeVector(forward * cos(angle) + normal * sin(angle));
    normal = crossProduct(side,forward);
    followPlanet = false;
}

void Camera::PitchUp()
{
    forward = normalizeVector(forward * cos(-angle) + normal * sin(-angle));
    normal = crossProduct(side,forward);
    followPlanet = false;
}

void Camera::RollLeft()
{
    side = normalizeVector(side * cos(-angle) + normal * sin(-angle));
    normal = crossProduct(side,forward);
    followPlanet = false;
}

void Camera::RollRight()
{
    side = normalizeVector(side * cos(angle) + normal * sin(angle));
    normal = crossProduct(side,forward);
    followPlanet = false;
}

void Camera::MoveLeft()
{
    position = position + (side * speed);
    followPlanet = false;
}

void Camera::MoveRight()
{
    position = position + (side * -speed);
    followPlanet = false;
}

void Camera::MoveForward()
{
    position = position + (forward * -speed);
    followPlanet = false;
}

void Camera::MoveBackward()
{
    position = position + (forward * speed);
    followPlanet = false;
}

void Camera::MoveUp()
{
    position = position + (normal * speed);
    followPlanet = false;
}

void Camera::MoveDown()
{
    position = position + (normal * -speed);
    followPlanet = false;
}

void Camera::JumpToLightspeed()
{
    position = position + (forward * -speed * lightspeedmult);
    followPlanet = false;
}

void Camera::YawLeft()
{
    side = normalizeVector(side * cos(angle) + forward * sin(angle));
    forward = crossProduct(normal, side);
    followPlanet = false;
}

void Camera::YawRight()
{
    side = normalizeVector(side * cos(-angle) + forward * sin(-angle));
    forward = crossProduct(normal, side);
    followPlanet = false;
}

void Camera::CheckForTeapotDiscovery()
{
    for(unsigned int i=0; i!=planets.size(); i++)
    {
        Point* tpos = planets[i]->teapotLoc;
        Vector3D diff(position.x - tpos->x,
            position.y - tpos->y,
            position.z - tpos->z);
        if(vectorSize(diff) <= 5.0 && !planets[i]->foundTeapot)
        {
            planets[i]->foundTeapot = true;
            teapotsFound++;
        }
    }
}

void Camera::Teleport(int planetIndex)
{
    OrbitalBody* p = planets[planetIndex];
    following = p;
    followPlanet = true;
}

void Camera::SetupProjection()
{
    if(followPlanet)
    {
        Vector3D v1(following->currentPos->x, following->currentPos->y, following->currentPos->z);
        Vector3D nv1 = normalizeVector(v1) * 4*following->size;
        Vector3D tempPos(v1.x + nv1.x, v1.y + nv1.y, v1.z + nv1.z);

        gluLookAt(tempPos.x, tempPos.y, tempPos.z,
                    0, 0, -1,
                    0, 1, 0);
    }
    else
    {
        gluLookAt(position.x, position.y, position.z,
                    position.x-forward.x, position.y-forward.y, position.z-forward.z,
                    normal.x, normal.y, normal.z);
    }
}

Camera* c = new Camera();