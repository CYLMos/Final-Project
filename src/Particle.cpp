#include "Particle.h"

Particle::Particle(){
    this->point = 0.0;
    this->bestPoint = 0.0;
}

Particle::Particle(int dim)
{
    this->bestLocation = new double[dim];
    this->currentLocation = new double[dim];
    this->velocity = new double[dim];
    this->point = 0.0;
    this->bestPoint = 0.0;
}

Particle::~Particle()
{
    delete this->bestLocation;
    delete this->currentLocation;
    delete this->velocity;
}

void Particle::setDim(int dim){
    this->bestLocation = new double[dim];
    this->currentLocation = new double[dim];
    this->velocity = new double[dim];
}

double* Particle::getBestLocation(){
    return this->bestLocation;
}

double* Particle::getCurrentLocation(){
    return this->currentLocation;
}

double* Particle::getVelocity(){
    return this->velocity;
}

double Particle::getPoint(){
    return this->point;
}

double Particle::getBestPoint(){
    return this->bestPoint;
}

void Particle::setBestLocation(double* location){
    this->bestLocation[0] = location[0];
    this->bestLocation[1] = location[1];
}

void Particle::setCurrentLocation(double* location){
    this->currentLocation[0] = location[0];
    this->currentLocation[1] = location[1];
}

void Particle::setVelocity(double* velocity){
    this->velocity[0] = velocity[0];
    this->velocity[1] = velocity[1];
}

void Particle::setPoint(double point){
    this->point = point;
}

void Particle::setBestPoint(double point){
    this->bestPoint = point;
}
