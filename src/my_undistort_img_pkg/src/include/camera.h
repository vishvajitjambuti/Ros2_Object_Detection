#pragma once
#include "macros.h"
#include <iostream>
#include <fstream>
#include <ctime>

#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/calib3d/calib3d.hpp>

class Camera{

    cv::Point3d coordinates;
public:
    std::string namePosition;
    std::string rstpAddress;


    int resolutionX;
    int resolutionY;
    bool isCalibrated;

    cv::Mat imageLive;
    cv::Mat imageLiveUndistorted;
    cv::Mat imageLiveTranformedPerspective;
    cv::Mat imageLiveBirdview;
    cv::VideoWriter video;

    void initializeCamera(bool record);
    clock_t checkFPS();
    //bool checkFPS
    cv::Mat getImage(bool checkFPS);
    cv::Mat undistort();
    void transformPerspective();

    void record(float fps);
    void showView(std::string& rstpAddress, cv::Mat& image);



    Camera(std::string _rstpAddress, int _resolutionX, int _resolutionY){
        rstpAddress = _rstpAddress;
        resolutionX= _resolutionX;
        resolutionY= _resolutionY;
        isRecording=false;
        initializeCamera(true);
    }
private:
    //Calibration Parameter
    std::vector<cv::Mat> instrExtrMatrix;
    cv::Mat perspTransParameter;

    //FPS Measurement
    clock_t fps = 0;
    std::chrono::high_resolution_clock::time_point t1 , t2;
    std::chrono::duration<double> time_span;
    int framesCaptured= 0;

    //Recording
    bool isRecording;
    cv::VideoCapture videoCapture;

    void readIntrinsicExtrinsic(std::string filePath);
    void readPerspTransParameter(std::string filePath);

};


