#include "Behavior_BilateralFilterParams.h"

using namespace std;

const int Behavior_BilateralFilterParams::SMOOTH = 0;
const int Behavior_BilateralFilterParams::LITTLE_SMOOTH = 1;
const int Behavior_BilateralFilterParams::NOT_SMOOTH = 2;

Behavior_BilateralFilterParams::Behavior_BilateralFilterParams()
{
    this->dim = 2;

    this->upperBound = new double[this->dim];
    this->lowerBound = new double[this->dim];

    this->upperBound[0] = 9;
    this->upperBound[1] = 150;

    this->lowerBound[0] = 1;
    this->lowerBound[1] = 10;
}

Behavior_BilateralFilterParams::~Behavior_BilateralFilterParams()
{
}

void Behavior_BilateralFilterParams::initial(Particle* particleArray,int length){
    srand((unsigned)time(NULL));

    for(int i = 0; i < length; i++){
        double rand1 = rand() % 9 + 1;
        double rand2 = rand() % 141 + 10;
        double randArray[2] = {rand1,rand2};
        double randArray_v[2] = {rand1,rand2};

        particleArray[i].setBestLocation(randArray);
        particleArray[i].setCurrentLocation(randArray);
        particleArray[i].setVelocity(randArray_v);

        particleArray[i].setPoint(computePoint(particleArray[i]));
    }

    double bestPoint;
    for(int i = 0; i < length; i++){
        if(i == 0){
            bestPoint = particleArray[i].getPoint();
            this->bestIndex = i;
        }
        else if(particleArray[i].getPoint() < bestPoint){
            bestPoint = particleArray[i].getPoint();
            this->bestIndex = i;
        }
    }
}

void Behavior_BilateralFilterParams::iteration(int times,int count,Particle *particleArray){
    srand((unsigned)time(NULL));

    for(int i = 0; i < times; i++){
        double *socialBestLocation = particleArray[this->bestIndex].getCurrentLocation();
        for(int p_index = 0; p_index < count; p_index++){

            double *velocity = particleArray[p_index].getVelocity();
            double *currentLocation = particleArray[p_index].getCurrentLocation();
            double *bestLocation = particleArray[p_index].getBestLocation();

            for(int dim_index = 0; dim_index < 2; dim_index++){
                int r1 = rand() % 2;
                int r2 = rand() % 2;

                velocity[dim_index] = this->w*velocity[dim_index] + this->c1*r1*(bestLocation[dim_index]-currentLocation[dim_index]) + this->c2*r2*(socialBestLocation[dim_index]-currentLocation[dim_index]);

                currentLocation[dim_index] = currentLocation[dim_index] + velocity[dim_index];
            }

            particleArray[p_index].setVelocity(velocity);
            if(currentLocation[0] > this->upperBound[0]){
                    currentLocation[0] = this->upperBound[0];
            }
            else if(currentLocation[0] <= this->lowerBound[0]){
                    currentLocation[0] = this->lowerBound[0];
            }
            if(currentLocation[1] > this->upperBound[1]){
                    currentLocation[1] = this->upperBound[1];
            }
            else if(currentLocation[1] <= this->lowerBound[1]){
                    currentLocation[1] = this->lowerBound[1];
            }
            particleArray[p_index].setCurrentLocation(currentLocation);
            double point = computePoint(particleArray[p_index]);
            particleArray[p_index].setPoint(point);

            velocity = NULL;
            currentLocation = NULL;
            bestLocation = NULL;
            delete velocity,currentLocation,bestLocation;
        }
        socialBestLocation = NULL;
        delete socialBestLocation;

        double bestPoint = 1000.0;
        int previousIndex = this->bestIndex;
        for(int j = 0; j < count; j++){
            if(particleArray[j].getPoint() <= particleArray[previousIndex].getPoint() && particleArray[j].getPoint() < bestPoint){
                bestPoint = particleArray[j].getPoint();
                this->bestIndex = j;
            }
        }

    }
}

Particle Behavior_BilateralFilterParams::getBestParticle(Particle* particleArray){
    return particleArray[this->bestIndex];
}

double Behavior_BilateralFilterParams::computePoint(Particle particle){
    double level = 0.0;
    switch(this->SMOOTH_LEVEL){
        case SMOOTH:
            level = 0.8;
            break;
        case LITTLE_SMOOTH:
            level = 0.65;
            break;
        case NOT_SMOOTH:
            level = 0.3;
            break;
        default:
            level = 0.65;
            break;
    }
    double* currentLocation = particle.getCurrentLocation();
    double point1 = this->param1[0] + currentLocation[0] * this->param1[1];
    double point2 = this->param2[0] + currentLocation[1] * this->param2[1];

    double variance = (0.1*point1) + (0.8*point2);
    double v = this->originVariance*level;
    double result = (v - variance) > 0 ? (v - variance) : (v - variance)*-1;

    currentLocation = NULL;
    delete currentLocation;

    return result;
}

void Behavior_BilateralFilterParams::setFittnessFunction(double *param1,double *param2){
    this->param1 = param1;
    this->param2 = param2;
}

void Behavior_BilateralFilterParams::setOriginVariance(double value){
    this->originVariance = value;
}

void Behavior_BilateralFilterParams::setSmoothLevel(int level){
    if(level > 2 || level < 0){
        return;
    }

    this->SMOOTH_LEVEL = level;
}
