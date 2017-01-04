#ifndef PARTICLE_H
#define PARTICLE_H

//int Dim = 3;

class Particle
{
    public:
        Particle();
        Particle(int dim);
        virtual ~Particle();

        double* getBestLocation();
        double* getCurrentLocation();
        double* getVelocity();
        double getPoint();
        void setBestLocation(double*);
        void setCurrentLocation(double*);
        void setVelocity(double*);
        void setPoint(double);

        void setDim(int);

    private:
        double* bestLocation;
        double* currentLocation;
        double* velocity;
        double point;
};

#endif // PARTICLE_H
