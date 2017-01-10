#ifndef PSO_BEHAVIOR_H
#define PSO_BEHAVIOR_H

#include "Particle.h"


class PSO_Behavior
{
    public:
        virtual void initial(Particle *,int) = 0;

        virtual void iteration(int,int,Particle *) = 0;

        virtual Particle getBestParticle(Particle *) = 0;

        virtual double computePoint(double* location) = 0;
};

#endif // PSO_BEHAVIOR_H
