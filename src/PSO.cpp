#include "PSO.h"

PSO::PSO(int count)
{
    this->count = count;
    this->particleArray = new Particle[count];

    for(int i = 0; i < count; i++){
        this->particleArray[i].setDim(2);
    }
}

PSO::~PSO()
{
    delete this->behavior;
    delete this->particleArray;
}

void PSO::startOptimization(int times){
    behavior->initial(this->particleArray,this->count);
    behavior->iteration(times,this->count,this->particleArray);

    std::cout << "the points of the particles: " << std::endl;
    for(int i = 0; i < this->count; i++){
        std::cout << "index " << i << ": " << particleArray[i].getBestPoint() << std::endl;
    }
    std::cout << std::endl;
}

void PSO::setBehavior(PSO_Behavior *behavior){
    this->behavior = behavior;
}

void PSO::getBestParticle(double *location){
    Particle p = behavior->getBestParticle(this->particleArray);
    double* bestLocation = p.getBestLocation();
    location[0] = bestLocation[0];
    location[1] = bestLocation[1];
    std::cout << "Point:" << p.getBestPoint() << std::endl;
    bestLocation = NULL;
}
