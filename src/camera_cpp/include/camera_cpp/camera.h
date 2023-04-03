#ifndef CAMERA_CAMERA_H
#define CAMERA_CAMERA_H

//local libraries
#include "../../../submodule/filereaderwriter/include/fileReaderWriter.h"
#include "macros.h"

//openSource libraries
#include <iostream>
#include <fstream>

#include "opencv2/aruco.hpp"
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <opencv4/opencv2/calib3d.hpp>


enum Cameratype{cameratype_normal, cameratype_fisheye};

enum Imagetype {imagetype_raw, imagetype_undistorted, imagetype_perspectiveTransformed};

enum CalibrationLevel{calibrationLevel_notCalibrated,
    calibrationLevel_undistortionCalibrated,
    calibrationLevel_perspTransformationCalibrated};

class Camera{

public:

    std::string name;
    std::string address;
    Cameratype cameratype= Cameratype::cameratype_normal;
    CalibrationLevel calibrationLevel= CalibrationLevel::calibrationLevel_undistortionCalibrated;
    bool isCameraInitialized;

    cv::Mat imageLive;
    cv::Mat imageLiveUndistorted;
    cv::Mat imageLiveTranformedPerspective;

    cv::VideoCapture videoCapture;

    const std::string pathData = "./src/camera_cpp/data/installedCameras/";
    std::vector<std::string> parameternames= {"Address", "Cameratype"};
    bool openCamera();
    void checkFPS();
    cv::Mat getImage(Imagetype imagetype=imagetype_raw);
    void stream(Imagetype imagetype=imagetype_raw);

    void record(float fps);
    void initializeCamera();

    std::string getCameratype(Cameratype& cameratype);
    std::string getImagetype(Imagetype & imagetype);

    Camera(std::string cameraName)
            : name(cameraName){}

    Camera(){}

private:
    void undistort();
    cv::Mat transformPerspective();
    void readCalibrationParameter();
    bool isCameraInstalled();
    void setCameratype(std::string& _cameratype);

    //Calibration Parameter
    std::vector<cv::Mat> distortionParameter;
    cv::Mat perspectiveTransformationParameter;

    //FPS Measurement
    clock_t fps = 0;
    std::chrono::high_resolution_clock::time_point t1 , t2;
    std::chrono::duration<double> time_span;
    int framesCaptured= 0;

    bool isRecording= false;
    cv::VideoWriter videoWriter;

};


namespace CameraHandling{
    static void listInstalledCameras() {
        FileReaderWriter::listDirsOfDirectory("../include/");}

    static void installCamera(std::string cameraName, std::string cameraAddress, Cameratype cameratype) {
        Camera cam(cameraName);
        cam.address=cameraAddress;
        std::vector<std::string> installParameter= {cameraAddress, cam.getCameratype(cameratype)};
        if(cam.openCamera()){
            std::string path= cam.pathData + cameraName;
            while(FileReaderWriter::isPathExisting(path)){
                FileReaderWriter::readYMLFile<std::string>(path+"/address.yml", installParameter, cam.parameternames);
                if(cameraAddress==installParameter[0]){
                    LOG("Camera is already installed");
                    return;
                }
                else{
                    LOG("Camera with Address " + installParameter[0] +" has the same name. \n Type a other name and press enter..... "
                                                                      "To cancel the calibration press enter without a letter");
                    std::cin >> cameraName;
                    path= cam.pathData + cameraName;

                    if(cameraName==""){LOG("Installation canceled") ; return;} }
            }

            FileReaderWriter::createDirectory(path);
            FileReaderWriter::createDirectory(path+"/temp");
            FileReaderWriter::createDirectory(path+"/temp/images");
            FileReaderWriter::createDirectory(path+"/temp/videos");
            FileReaderWriter::writeYMLFile<std::string>(path+"/address.yml", installParameter,
                                                        cam.parameternames);
            LOG("Installation of camera" << cam.name << "was successful");
            return;
        }
        else{ LOG("Installation failed, could not connect with Camera");
            false;}
    }

    static cv::Mat captureImage(std::string cameraName, Imagetype _imagetype, const bool saveImage) {
        Camera cam(cameraName);
        cam.initializeCamera();
        cam.openCamera();
        cv::Mat image;
        if (!cam.isCameraInitialized && !cam.videoCapture.isOpened()){
            return image;}
        else if (_imagetype>cam.calibrationLevel){
            LOG("Camera is not Calibrated for Imagetype: " << _imagetype);
            _imagetype= static_cast<Imagetype>(cam.calibrationLevel);
            LOG(cam.calibrationLevel);
            LOG(_imagetype);
        }
        image = cam.getImage(_imagetype);
        if(saveImage){
            FileReaderWriter::saveFile(cam.pathData + cam.name + "/temp/images/", image);
        }
        return image;
    }

    static void stream(std::string cameraName, Imagetype _imagetype, bool isCheckFPS=false, bool isRecord=false) {
        Camera cam(cameraName);
        cam.initializeCamera();
        cam.openCamera();
        if (!cam.isCameraInitialized && !cam.videoCapture.isOpened()){
            return;}

        else if (_imagetype>cam.calibrationLevel){
            LOG("Camera is not Calibrated for Imagetype " << cam.getImagetype(_imagetype));
            _imagetype= static_cast<Imagetype>(cam.calibrationLevel);
        }
        while (true){
            cv::Mat image = cam.getImage( _imagetype);
            if (!image.empty()){
                IMSHOW("Livestream of Camera '" + cameraName + "' (" + cam.getImagetype(_imagetype) + ")", image, 1);
                if (isCheckFPS){
                    cam.checkFPS();
                }
                if (isRecord){
                    cam.record(5);}
            }
        }}
};

#endif //CAMERA_CAMERA_H