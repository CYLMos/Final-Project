#include "Particle.h"

Particle::Particle(){
    this->point = 0.0;
}

Particle::Particle(int dim)
{
    this->bestLocation = new double[dim];
    this->currentLocation = new double[dim];
    this->velocity = new double[dim];
    this->point = 0.0;
}

Particle::~Particle()
{
    //dtor
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

void Particle::setBestLocation(double* location){
    this->bestLocation = location;
}

void Particle::setCurrentLocation(double* location){
    this->currentLocation = location;
}

void Particle::setVelocity(double* velocity){
    this->velocity = velocity;
}

void Particle::setPoint(double point){
    this->point = point;
}
