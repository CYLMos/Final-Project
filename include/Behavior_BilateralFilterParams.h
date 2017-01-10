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
        ~Behavior_BilateralFilterParams();

        void iteration(int,int,Particle *) override;
        void initial(Particle *,int) override;
        double computePoint(double *location) override;
        Particle getBestParticle(Particle*) override;
        void setFittnessFunction(double*,double*,int);
        void setOriginVariance(double);
        void setSmoothLevel(int);

        static const int SMOOTH;
        static const int LITTLE_SMOOTH;
        static const int NOT_SMOOTH;

    private:
        double w = 1.0;
        double c1 = 0.5;
        double c2 = 0.5;
        int bestIndex;
        double* upperBound;
        double* lowerBound;
        int dim;
        double *param1;
        double *param2;
        double originVariance;
        int SMOOTH_LEVEL = 1;
};

#endif // BEHAVIOR_BILATERALFILTERPARAMS_H
