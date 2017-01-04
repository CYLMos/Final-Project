#include "Behavior_BilateralFilterParams.h"
using namespace std;

Behavior_BilateralFilterParams::Behavior_BilateralFilterParams()
{
    this->dim = 3;

    this->upperBound = new double[this->dim];
    this->lowerBound = new double[this->dim];

    this->upperBound[0] = 9;
    this->upperBound[1] = 100;
    this->upperBound[2] = 100;

    this->lowerBound[0] = 1;
    this->lowerBound[1] = 0;
    this->lowerBound[2] = 0;
}

Behavior_BilateralFilterParams::~Behavior_BilateralFilterParams()
{
    //dtor
}

Particle* Behavior_BilateralFilterParams::initial(Particle* particleArray,int length,int &index){
    srand((unsigned)time(NULL));

    for(int i = 0; i < length; i++){
        double rand1 = rand() % 9 + 1;
        double rand2 = rand() % 101;
        double rand3 = rand() % 101;
        double randArray[3] = {rand1,rand2,rand3};
        double randArray_v[3] = {rand1/10,rand2/50,rand3/50};

        particleArray[i].setBestLocation(randArray);
        particleArray[i].setCurrentLocation(randArray);
        particleArray[i].setVelocity(randArray_v);

        particleArray[i].setPoint(computePoint(particleArray[i]));
    }

    double bestPoint;
    for(int i = 0; i < length; i++){
        if(i == 0){
            bestPoint = particleArray[i].getPoint();
            index = i;
        }
        else if(particleArray[i].getPoint() > bestPoint){
            bestPoint = particleArray[i].getPoint();
            index = i;
        }
    }
    this->bestIndex = index;

    return particleArray;
}

Particle* Behavior_BilateralFilterParams::iteration(int times,int count,Particle *particleArray){
    srand((unsigned)time(NULL));

    for(int i = 0; i < times; i++){
        double *socialBestLocation = particleArray[this->bestIndex].getCurrentLocation();
        for(int p_index = 0; p_index < count; p_index++){

            double *velocity = particleArray[p_index].getVelocity();
            double *currentLocation = particleArray[p_index].getCurrentLocation();
            double *bestLocation = particleArray[p_index].getBestLocation();

            for(int dim_index = 0; dim_index < 3; dim_index++){
                //std::cout << this->dim << std::endl;
                int r1 = rand() % 2;
                int r2 = rand() % 2;

                velocity[dim_index] = 1.0*velocity[dim_index] + 0.5*r1*(bestLocation[dim_index]-currentLocation[dim_index]) + 0.5*r2*(socialBestLocation[dim_index]-currentLocation[dim_index]);

                currentLocation[dim_index] = currentLocation[dim_index] + velocity[dim_index];
            }

            particleArray[p_index].setVelocity(velocity);
            particleArray[p_index].setCurrentLocation(currentLocation);
            double point = computePoint(particleArray[p_index]);
            particleArray[p_index].setPoint(point);

            delete [] velocity,currentLocation,bestLocation;
        }
        delete socialBestLocation;

        double bestPoint;
        int previousIndex = this->bestIndex;
        for(int i = 0; i < count; i++){
            if(i == 0){
                bestPoint = particleArray[i].getPoint();
                this->bestIndex= i;
            }
            else if(particleArray[i].getPoint() >= particleArray[previousIndex].getPoint() && particleArray[i].getPoint() > bestPoint){
                bestPoint = particleArray[i].getPoint();
                this->bestIndex = i;
            }
        }

    }
    return particleArray;
}

Particle Behavior_BilateralFilterParams::getBestParticle(Particle* particleArray){
    return particleArray[this->bestIndex];
}

/*void Behavior_BilateralFilterParams::choseBestSocialParticle(Particle* particleArray,int length,int &index){
    double* best;
    for(int i = 0; i < length; i++){
        if(i == 0){
            best = particleArray[i].getCurrentLocation();
            index = i;
        }
        else if(particleArray[i].getCurrentLocation() > best){
            best = particleArray[i].getCurrentLocation();
            index = i;
        }
    }
}

void Behavior_BilateralFilterParams::updateBestParticleSelf(Particle &particle){
    if(particle.getCurrentLocation() > particle.getBestLocation()){
        particle.setBestLocation(particle.getCurrentLocation());
    }
}*/

double Behavior_BilateralFilterParams::computePoint(Particle particle){
    double* currentLocation = particle.getCurrentLocation();
    double point = 0.5 * currentLocation[0] + 0.5 * currentLocation[1] + 0.5 * currentLocation[2];
    delete [] currentLocation;

    return point;
}
