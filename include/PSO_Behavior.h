#ifndef PSO_BEHAVIOR_H
#define PSO_BEHAVIOR_H

#include "Particle.h"


class PSO_Behavior
{
    /*public:
        virtual void iteration(int) = 0;

        virtual int choseBestSocialParticle(Particle *) = 0;

        virtual void updateBestParticleSelf(Particle &) = 0;*/

    public:
        virtual Particle* initial(Particle *,int,int &) = 0;

        virtual Particle* iteration(int,int,Particle *) = 0;

        virtual Particle getBestParticle(Particle *) = 0;

        //virtual void choseBestSocialParticle(Particle *,int,int &) = 0;

        //virtual void updateBestParticleSelf(Particle &) = 0;

        virtual double computePoint(Particle) = 0;
};

#endif // PSO_BEHAVIOR_H
