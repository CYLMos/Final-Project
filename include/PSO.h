#ifndef PSO_H
#define PSO_H

#include "Particle.h"
#include "PSO_Behavior.h"
#include <iostream>

class PSO
{
    public:
        PSO(int);
        virtual ~PSO();
        void startOptimization(int);
        void setBehavior(PSO_Behavior* behavior);

    protected:

    private:
        Particle *particleArray;
        PSO_Behavior *behavior;
        int count;
        int index;
};

#endif // PSO_H
