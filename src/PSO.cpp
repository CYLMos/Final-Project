#include "PSO.h"

PSO::PSO(int count)
{
    this->count = count;
    this->particleArray = new Particle[count];

    for(int i = 0; i < count; i++){
        this->particleArray[i].setDim(3);
    }
}

PSO::~PSO()
{
    delete this->behavior;
    delete this->particleArray;
}

void PSO::startOptimization(int times){
    this->particleArray = behavior->initial(this->particleArray,this->count,this->index);
    this->particleArray = behavior->iteration(times,this->count,this->particleArray);

    Particle best = behavior->getBestParticle(this->particleArray);
    double* location = best.getCurrentLocation();
    double* blocation = best.getBestLocation();
    double* v = best.getVelocity();
    double point = best.getPoint();

    std::cout << "current location: " << location[0] << " " << location[1] << " " << location[2] << std::endl;
    std::cout << "best location: " << blocation[0] << " " << blocation[1] << " " << blocation[2] << std::endl;
    std::cout << "v: " << v[0] << " " << v[1] << " " << v[2] << std::endl;
    std::cout << "point: " << point;

    delete [] location,blocation,v;
}

void PSO::setBehavior(PSO_Behavior *behavior){
    this->behavior = behavior;
}
