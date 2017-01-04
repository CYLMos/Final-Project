#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "PSO.h"
#include "Behavior_BilateralFilterParams.h"

using namespace std;
using namespace cv;

int main()
{
    PSO* pso = new PSO(3);
    Behavior_BilateralFilterParams* behavior = new Behavior_BilateralFilterParams();

    pso->setBehavior(behavior);
    pso->startOptimization(10);

    delete pso;
    delete behavior;

    return 0;
}
