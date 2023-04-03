#include "../include/camera_cpp/camera.h"

cv::Mat Camera::getImage(Imagetype cameraModus){
    cv::Mat* image;
    if (!isCameraInitialized){
        initializeCamera();}

    videoCapture.read(imageLive);
    this->framesCaptured++;
    if (!imageLive.empty()){
        switch (cameraModus) {
            case imagetype_raw:
                image=&imageLive;
                break;
            case imagetype_undistorted:
                undistort(); image=&imageLiveUndistorted;
                break;
            case imagetype_perspectiveTransformed:
                undistort();transformPerspective();
                image=&imageLiveTranformedPerspective;
                break;
        }
    }
    return *image;
}

void Camera::stream(Imagetype _imagetype) {
    if (!isCameraInitialized){
        initializeCamera();}
    if(videoCapture.isOpened()){
        if(!openCamera() || !isCameraInitialized){
            return;
        };
    }
    if (_imagetype>calibrationLevel){
        LOG("Camera '" << name << "' is not Calibrated for Imagetype " << getImagetype(_imagetype));
        _imagetype= static_cast<Imagetype>(calibrationLevel);
    }
    while (true){

        cv::Mat image = getImage( _imagetype);
        if (!image.empty()){
            IMSHOW("Livestream of Camera '" + name + "' (" + getImagetype(_imagetype) + ")", image, 1);
        }
        int keycode = cv::waitKey(10) & 0xff ;
        if (keycode==27) break;
        }
     }

/*################################  install functions ##############################*/

bool Camera::openCamera() {
    if(address=="0" || address== "1" || address== "2"){
        int addressLocal = std::stoi(address);
        this->videoCapture.open(addressLocal);
    }
    else{
        this->videoCapture.open(address);
    }
    if(videoCapture.isOpened()) {
        LOG("Camera " + address + " connected");
        return true;
    }
    else{
        LOG("Connection to camera " + address + " failed");
        return false;
    }
}

void Camera::initializeCamera() {
    if(isCameraInstalled()){
        std::string cameraType;
        std::vector<std::string> cameraParameter;

        FileReaderWriter::readYMLFile(pathData + name + "/address.yml",
                                      cameraParameter, parameternames);
        address = cameraParameter[0];
        setCameratype(cameraParameter[1]);
        isCameraInitialized= address.length()!=0 ? true : false ;}
    else {
        LOG("Camera "+ name + " is not installed. Install it before proceed.");
        isCameraInitialized=false;}

    if(isCameraInitialized) {
        readCalibrationParameter();
    }
    else {
        LOG("Cam " + name + " (" + address + ") coudn't be initialized");}
}

bool Camera::isCameraInstalled() {
    if(FileReaderWriter::isPathExisting(pathData + name))return true;
    else return false;
}

void Camera::readCalibrationParameter() {

    if(cameratype!=Cameratype::cameratype_normal){
        std::string pathDistortionParameter = pathData+name+"/distortionParameter.yml";
        std::vector<std::string> namesCalibrationParameter {"cameraMatrix", "distCoeffs", "R", "T"};
        FileReaderWriter::readYMLFile(pathDistortionParameter,distortionParameter,namesCalibrationParameter);
        calibrationLevel = distortionParameter.size() !=0 ? calibrationLevel_undistortionCalibrated : calibrationLevel_notCalibrated;
    }
    else{
        calibrationLevel=calibrationLevel_undistortionCalibrated;
    }
    if(calibrationLevel==calibrationLevel_undistortionCalibrated){
        std::string pathPerspTransformationParameter= pathData+name+"/perspectiveTransformationParameter.yml";
        FileReaderWriter::readYMLFile<cv::Mat>(pathPerspTransformationParameter,perspectiveTransformationParameter,
                                               "perspectiveTransformationParameter");
        calibrationLevel = perspectiveTransformationParameter.data!=0 ? calibrationLevel_perspTransformationCalibrated : calibrationLevel_undistortionCalibrated;
    }


}
/*##############################################################*/

void Camera::checkFPS(){
    if(framesCaptured % 20 ==0){
        if (framesCaptured==20){
            t1 = std::chrono::high_resolution_clock::now();
        }
        else {
            if(framesCaptured % 40 == 0) // frameCaputured gerade
            {
                t1 = std::chrono::high_resolution_clock::now();
                time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t2);
            }
            else // frameCaputured ungerade
            {
                t2 = std::chrono::high_resolution_clock::now();
                time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
            }
            if (time_span.count() != 0){
                fps = 20 / time_span.count();
                LOG("FPS=" + std::to_string(fps));
            }
        }
    }
}

cv::Mat Camera::transformPerspective() {

    cv::warpPerspective(imageLiveUndistorted, imageLiveTranformedPerspective, perspectiveTransformationParameter,
                        cv::Size());

    return imageLiveTranformedPerspective;
}

void Camera::record(float fps){

    if (!isRecording){
        videoWriter = cv::VideoWriter("../data/installedCameras/" + name + "/temp/videos/" + FileReaderWriter::currentDateTime() + ".avi",
                                      cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),fps, imageLive.size());
    }
    videoWriter.write(imageLive);
    isRecording=true;
}

void Camera::undistort() {
    cv::undistort(imageLive, imageLiveUndistorted, distortionParameter[0], distortionParameter[1]);
}

std::string Camera::getCameratype(Cameratype& cameratyp){
    return cameratyp == cameratype_normal ? "cameratype::Normal" : "cameratype::Fisheye";
};

void Camera::setCameratype(std::string& _cameratype){
    cameratype = _cameratype == "cameratype::Normal" ? cameratype_normal : cameratype_fisheye;
};

std::string Camera::getImagetype(Imagetype &imagetype) {
    return imagetype == imagetype_raw ? "imagetype_raw" : imagetype == imagetype_undistorted ?  "imagetype_undistorted" : "imagetype_perspectiveTransformed";
}

