#include "fileReaderWriter.h"

void FileReaderWriter::readImage(std::string path, cv::Mat& image){
    if(isPathExisting(path)){
        image= cv::imread(path);
    }
    else{
        std::cout <<"Path of the image is not existing";
    }
}

void FileReaderWriter::listDirsOfDirectory(std::string path) {

    DIR *dir = opendir(path.c_str());
    struct dirent *entry = readdir(dir);
    while (entry != NULL)
    {
        if (entry->d_type == DT_DIR)
            printf("%s\n", entry->d_name);
        entry = readdir(dir);
    }
    closedir(dir);

}

bool FileReaderWriter::isPathExisting(std::string fileName)
{
    std::ifstream isfileExist(fileName);
    return isfileExist.good();
}

void FileReaderWriter::createDirectory(std::string path){
    mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
};

void FileReaderWriter::saveFile(std::string parentpath, cv::Mat &image){
    std::string path = parentpath + currentDateTime() + ".png";
    int i=2;
    while(isPathExisting(path)){
        path = parentpath + currentDateTime() + "(" + std::to_string(i) + ").png";
        i++;
    }
    cv::imwrite(path, image);
}

const std::string FileReaderWriter::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y_%m_%d_%H_%M", &tstruct);
    return buf;
}

