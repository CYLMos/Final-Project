#ifndef PARTICLE_H
#define PARTICLE_H
#include <iostream>

//int Dim = 3;

class Particle
{
    public:
        Particle();
        Particle(int dim);
        ~Particle();

        double* getBestLocation();
        double* getCurrentLocation();
        double* getVelocity();
        double getPoint();
        double getBestPoint();
        void setBestLocation(double*);
        void setCurrentLocation(double*);
        void setVelocity(double*);
        void setPoint(double);
        void setBestPoint(double);

        void setDim(int);

    private:
        double* bestLocation;
        double* currentLocation;
        double* velocity;
        double point;
        double bestPoint;
};

#endif // PARTICLE_H
