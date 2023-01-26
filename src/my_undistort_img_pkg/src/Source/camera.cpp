#include "../include/camera.h"

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y_%m_%d_%H_%M", &tstruct);
    return buf;
}

void Camera::readIntrinsicExtrinsic(std::string filePath) {
    std::ifstream isFileExist;
    isFileExist.open(filePath);
    std::string keyWords[4]{"cameraMatrix","distCoeffs", "R", "T" };
    cv::Mat Matrix;
    if(isFileExist){
        cv::FileStorage fs(filePath, cv::FileStorage::READ);
        for(int i= 0; i<4; i++){
            fs[keyWords[i]] >> Matrix;
            instrExtrMatrix.push_back(Matrix);
        }
        fs.release();
        isCalibrated=true;
        for (int i=0; i<4; i++){
            if (!instrExtrMatrix[i].data){
                isCalibrated= false;
            }
        }
    }
    else{
        std::cout << "file is not existing" +filePath;
        isCalibrated= false;
    }
}

void Camera::readPerspTransParameter(std::string filePath) {
    bool isCalibrated= false;
    std::ifstream isFileExist;
    isFileExist.open(filePath);
    if(isFileExist){
        cv::FileStorage fs(filePath, cv::FileStorage::READ);
        fs["optimizedHomographyMatrixBirdview"] >> perspTransParameter;
        fs.release();
        isCalibrated=true;
        if (!perspTransParameter.data) {
            isCalibrated= false;}
    }
    else{
        std::cout << "file is not existing" +filePath;
        isCalibrated= false;
    }
}

// bool checkFPS
cv::Mat Camera::getImage(bool checkFPS){

    if (!(videoCapture.isOpened())) {
        std::cout << "[INTERACTION] : [Acquisition] : Cannot open camera" << std::endl;
        system("pause");
        std::exit(EXIT_FAILURE);
    }
    videoCapture.read(imageLive);
    this->framesCaptured++;
    return imageLive;
}

clock_t Camera::checkFPS(){
    if (framesCaptured==0){
        t1 = std::chrono::high_resolution_clock::now();
    }
    else {
        if(framesCaptured % 2 == 0) // frameCaputured gerade
        {   t1 = std::chrono::high_resolution_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t2);
        }
        else // frameCaputured ungerade
        {
            t2 = std::chrono::high_resolution_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        }
        if (time_span.count() != 0){
            fps = 1 / time_span.count();
        }
    }

    return fps;
}

cv::Mat Camera::undistort() {
    cv::undistort(imageLive, imageLiveUndistorted, instrExtrMatrix[0], instrExtrMatrix[1]);
    return imageLiveUndistorted;
}

void Camera::record(float fps){

    if (!isRecording){
        video = cv::VideoWriter("../data/videos/" + namePosition + "_" +currentDateTime() + ".avi",
                                cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),fps, imageLive.size());

    }
    RECORDING(video, imageLive);
    isRecording=true;
}

void Camera::initializeCamera(bool record) {
    readIntrinsicExtrinsic("/home/ROS2_yolo/src/my_undistort_img_pkg/src/Source/distortionMatrix.yml");

    if (record) {

    }
    this->videoCapture.open(rstpAddress);      //

    if(videoCapture.isOpened()) {
        LOG("Camera " + rstpAddress +  " initialized");
    }
    else{
        LOG("Connection to camera " + rstpAddress + " failed");
    }
}

void Camera::showView(std::string& rstpAddress, cv::Mat& image) {
    cv::imshow(rstpAddress, image);
    cv::waitKey(1);
}

void Camera::transformPerspective() {

    cv::warpPerspective(imageLiveUndistorted, imageLiveTranformedPerspective, perspTransParameter,
                        cv::Size());
}


void messagePathNotExits(std::string path){
    LOG("could not find " + path);
}

/*
void Camera::recordVideo(cv::Mat& image, std::string imagename, cv::VideoWriter& videowriter){
    cv::VideoWriter("../data/videos/Camera" + getCurrentTime() +".avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 5, imageLiveUndistorted[0].size(), true));
    while (true){
        RECORDING(videowriter, image);
        if (stopRecording) {
            CLOSEVIDEO(videowriter);
            return;
        }
    }
}*/
