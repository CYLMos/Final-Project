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

    this->param1 = NULL;
    this->param2 = NULL;
}

Behavior_BilateralFilterParams::~Behavior_BilateralFilterParams()
{
    delete this->upperBound;
    delete this->lowerBound;
    delete this->param1;
    delete this->param2;
}

void Behavior_BilateralFilterParams::initial(Particle *particleArray,int length){
    srand((unsigned)time(NULL));

    for(int i = 0; i < length; i++){
        double rand1 = rand() % 9 + 1;
        double rand2 = rand() % 141 + 10;
        double randArray[2] = {rand1,rand2};
        double randArray_v[2] = {rand1,rand2};


        particleArray[i].setBestLocation(randArray);
        particleArray[i].setCurrentLocation(randArray);
        particleArray[i].setVelocity(randArray_v);

        particleArray[i].setPoint(computePoint(randArray));
        particleArray[i].setBestPoint(computePoint(randArray));
    }

    double bestPoint;
    for(int i = 0; i < length; i++){
        if(i == 0){
            bestPoint = particleArray[i].getBestPoint();
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
        double *socialBestLocation = particleArray[this->bestIndex].getBestLocation();
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
            double point = computePoint(currentLocation);
            particleArray[p_index].setPoint(point);
            if(particleArray[p_index].getBestPoint() > point){
                particleArray[p_index].setBestPoint(point);
                particleArray[p_index].setBestLocation(currentLocation);
            }

            velocity = NULL;
            currentLocation = NULL;
            bestLocation = NULL;
        }
        socialBestLocation = NULL;

        double bestPoint = 1000.0;
        int previousIndex = this->bestIndex;
        for(int j = 0; j < count; j++){
            if(particleArray[j].getPoint() <= particleArray[previousIndex].getBestPoint() && particleArray[j].getPoint() < bestPoint){
                bestPoint = particleArray[j].getPoint();
                this->bestIndex = j;
            }
        }

    }
}

Particle Behavior_BilateralFilterParams::getBestParticle(Particle* particleArray){
    return particleArray[this->bestIndex];
}

double Behavior_BilateralFilterParams::computePoint(double *currentLocation){
    double level = 0.0;
    double w1 = 0.0,w2 = 0.0;
    switch(this->SMOOTH_LEVEL){
        case SMOOTH:
            level = 0.8;
            w1 = 0.45;
            w2 = 0.5;
            break;
        case LITTLE_SMOOTH:
            level = 0.65;
            w1 = 0.1;
            w2 = 0.68;
            break;
        case NOT_SMOOTH:
            level = 0.3;
            w1 = 0.1;
            w2 = 0.3;
            break;
        default:
            level = 0.65;
            break;
    }
    double point1 = this->param1[0] + currentLocation[0] * this->param1[1];
    double point2 = this->param2[0] + currentLocation[1] * this->param2[1];

    double variance = (w1*point1) + (w2*point2);
    double v = this->originVariance*level;
    double result = (v - variance) > 0 ? (v - variance) : (v - variance)*-1;

    currentLocation = NULL;

    return result;
}

void Behavior_BilateralFilterParams::setFittnessFunction(double *param1,double *param2,int size){
    this->param1 = new double[size];
    this->param2 = new double[size];

    for(int i = 0; i < size; i++){
        this->param1[i] = param1[i];
        this->param2[i] = param2[i];
    }
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
