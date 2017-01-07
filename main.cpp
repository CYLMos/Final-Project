#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <iomanip>

#include "PSO.h"
#include "Behavior_BilateralFilterParams.h"

using namespace std;
using namespace cv;

double getVariance(Mat);
void getLinearRegression(double*, double*, double*, int);
void cannyThreshold(int, void*);
void cannyThreshold2(int, void*);

double NOT_SMOOTH = 400.0;
double SMOOTH = 100.0;

Mat src;
Mat src_gray;
Mat src_smooth;
Mat dst;
Mat dst2;
int lowThreshold;
int lowThreshold2;

int main()
{
    string imagePath;
    cin >> imagePath;
    src = imread(imagePath,CV_LOAD_IMAGE_COLOR);

    dst.create(src.size(),src.type());
    dst2.create(src.size(),src.type());

    cvtColor(src,src_gray,CV_BGR2GRAY);

    double variance = getVariance(src_gray);
    cout << "origin variance: " << variance << endl;

    double p[9] = {1,2,3,4,5,6,7,8,9};
    double r[9];

    for(int i = 0; i < sizeof(p)/sizeof(p[0]); i++){
        Mat mat;
        bilateralFilter(src_gray,mat,p[i],1,10);
        //double v = getVariance(mat);
        r[i] = getVariance(mat);
        cout << "d_variance:" << r[i] << endl;
    }
    cout << endl;

    double a1[2] = {0,0};
    getLinearRegression(p,r,a1,sizeof(p)/sizeof(p[0]));
    cout << "the param of the d function is : " << a1[0] << "   " << a1[1] << endl;
    cout << endl;

    double p2[12] = {10,20,30,40,50,60,70,80,90,100,110,120};
    double r2[12];

    for(int i = 0; i < sizeof(p2)/sizeof(p2[0]); i++){
        Mat mat;
        bilateralFilter(src_gray,mat,1,p2[i],100);
        //double v = getVariance(mat);
        r2[i] = getVariance(mat);
        cout << "sc_variance: " << r2[i] << endl;
    }
    cout << endl;

    double a2[2] = {0,0};
    getLinearRegression(p2,r2,a2,sizeof(p2)/sizeof(p2[0]));
    cout << "the param of the sigmaColor function is : " << a2[0] << "   " << a2[1] << endl;
    cout << endl;

    PSO *pso = new PSO(15);
    Behavior_BilateralFilterParams behavior; //= new Behavior_BilateralFilterParams();
    behavior.setFittnessFunction(a1,a2);
    behavior.setOriginVariance(variance);

    if(variance < SMOOTH){
        behavior.setSmoothLevel(Behavior_BilateralFilterParams::SMOOTH);
    }
    else if(variance > NOT_SMOOTH){
        behavior.setSmoothLevel(Behavior_BilateralFilterParams::NOT_SMOOTH);
    }
    else{
        behavior.setSmoothLevel(Behavior_BilateralFilterParams::LITTLE_SMOOTH);
    }

    pso->setBehavior(&behavior);
    pso->startOptimization(80);

    double *location = new double[2];
    pso->getBestParticle(location);

    cout << location[0] << " " << location[1] << endl;

    bilateralFilter(src_gray,src_smooth,location[0],location[1],10);
    cout << "smooth variance: " << getVariance(src_smooth) << endl;
    cout << "d function result: " << a2[0] + location[1]*a2[1] << endl;
    cout << "sigmaColor function result: " << a1[0] + location[0]*a1[1] << endl;

    namedWindow("smooth",WINDOW_AUTOSIZE);
    namedWindow("origin",WINDOW_AUTOSIZE);
    createTrackbar("Threshold","smooth",&lowThreshold,100,cannyThreshold);
    createTrackbar("Threshold","origin",&lowThreshold2,100,cannyThreshold2);

    cannyThreshold(0,0);
    cannyThreshold2(0,0);

    waitKey(0);

    delete pso;
    delete location;

    return 0;
}

void cannyThreshold(int, void*){
    Mat canny_mat;
    Canny(src_smooth,canny_mat,lowThreshold,lowThreshold*3 ,3);

    dst = Scalar::all(0);
    src.copyTo(dst,canny_mat);
    imshow("smooth",dst);
}

void cannyThreshold2(int, void*){
    Mat canny_mat;
    Canny(src_gray,canny_mat,lowThreshold2,lowThreshold2*3 ,3);

    dst2 = Scalar::all(0);
    src.copyTo(dst2,canny_mat);
    imshow("origin",dst2);
}

void getLinearRegression(double *param,double *result,double *r,int length){
    double ave_param = 0.0;
    double ave_result = 0.0;


    for(int i = 0; i < length; i++){
        ave_param += param[i];
        ave_result += result[i];
    }

    ave_param /= length;
    ave_result /= length;

    double molecular = 0.0;
    double denominator = 0.0;

    for(int i = 0; i < length; i++){
        molecular += (param[i] - ave_param)*(result[i] - ave_result);
    }
    for(int j = 0; j < length; j++){
        denominator += pow((param[j] - ave_param),2);
    }

    r[1] = molecular / denominator;
    r[0] = ave_result - r[1]*ave_param;
}

double getVariance(Mat mat){
    int h = mat.rows/4;
    int w = mat.cols/4;
    double variance[h][w];

    int index_h = 0,index_w = 0;
    for(int i = 0; i < mat.rows; i+=4){
        for(int j = 0; j < mat.cols; j+=4){
            double ave = 0.0;
            for(int sub_i = i; sub_i < i + 4;sub_i++){
                for(int sub_j = j; sub_j < j + 4;sub_j++){
                    ave += (double)mat.at<uchar>(sub_i,sub_j);
                }
            }

            ave /= 16.0;
            int diff_total = 0.0;

            for(int sub_i = i; sub_i < i + 4;sub_i++){
                for(int sub_j = j; sub_j < j + 4;sub_j++){
                    diff_total += pow(((double)mat.at<uchar>(sub_i,sub_j) - ave),2.0);
                }
            }

            diff_total /= 16.0;
            variance[index_h][index_w] = diff_total;
            index_w++;
        }
        index_h++;
        index_w = 0;
    }

    double total = 0.0;
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            total += variance[i][j];
        }
    }
    total /= h*w;

    return total;
}
