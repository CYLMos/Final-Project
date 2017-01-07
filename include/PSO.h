#ifndef PSO_H
#define PSO_H

#include "Particle.h"
#include "PSO_Behavior.h"
#include "Behavior_BilateralFilterParams.h"
#include <iostream>

class PSO
{
    public:
        PSO(int);
        ~PSO();
        void startOptimization(int);
        void setBehavior(PSO_Behavior* behavior);
        void getBestParticle(double*);

    protected:

    private:
        Particle *particleArray;
        PSO_Behavior *behavior;
        int count;
};

#endif // PSO_H
