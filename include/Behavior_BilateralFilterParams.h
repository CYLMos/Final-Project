#ifndef BEHAVIOR_BILATERALFILTERPARAMS_H
#define BEHAVIOR_BILATERALFILTERPARAMS_H

#include "PSO_Behavior.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

class Behavior_BilateralFilterParams : public PSO_Behavior
{
    public:
        Behavior_BilateralFilterParams();
        virtual ~Behavior_BilateralFilterParams();

        Particle* iteration(int,int,Particle *);
        Particle* initial(Particle *,int,int &);
        //void choseBestSocialParticle(Particle *,int,int &);
        //void updateBestParticleSelf(Particle &);
        double computePoint(Particle);
        Particle getBestParticle(Particle*);

    private:
        double w;
        double c1;
        double c2;
        int bestIndex;
        double* upperBound;
        double* lowerBound;
        int dim;
};

#endif // BEHAVIOR_BILATERALFILTERPARAMS_H
