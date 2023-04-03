#ifndef FILEREADERWRITER_FILEREADERWRITER_H
#define FILEREADERWRITER_FILEREADERWRITER_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/stat.h>
#include <dirent.h>

#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/mat.hpp>


struct FileReaderWriter {

    static void createDirectory(std::string path);

    static void saveFile(std::string path, cv::Mat &image);

    static bool isPathExisting(std::string path);

    static void listDirsOfDirectory(std::string path);

    static void readImage(std::string path, cv::Mat &image);

    template<typename T>
    static void readYMLFileWithoutParameterName(std::string filePath, std::vector<T> &parameter, std::vector<std::string>& parameterName) {
        if (isPathExisting(filePath)) {
            cv::FileStorage fs(filePath, cv::FileStorage::READ);
            cv::FileNode fn = fs.root();
            for (cv::FileNodeIterator fit = fn.begin(); fit != fn.end(); ++fit)
            {
                cv::FileNode item = *fit;
                std::string somekey = item.name();
                parameterName.push_back(somekey);
                parameter.push_back(fn[somekey]);
            }
            fs.release();
        } else {
            std::cout << filePath << " is not existing";
        }
    };

    template<typename T>
    static void readYMLFile(std::string filePath, T &parameter, std::string parameterName) {
        if (isPathExisting(filePath)) {
            cv::FileStorage fs(filePath, cv::FileStorage::READ);
            fs[parameterName] >> parameter;
            fs.release();
        } else {
            std::cout << filePath << " is not existing";
        }
    }

    template<typename T>
    static void readYMLFile(std::string filePath, std::vector<T> &parameter, std::vector<std::string> parameterName) {
        if (isPathExisting(filePath)) {
            cv::FileStorage fs(filePath, cv::FileStorage::READ);
            for (int i = 0; i < parameterName.size(); i++) {
                parameter.push_back({});
                fs[parameterName[i]] >> parameter[i];
            }
            fs.release();
        } else {
            std::cout << filePath << " is not existing";
        }
    };

    template<typename T>
    static void writeYMLFile(std::string filePath, std::vector<T> &parameter, std::vector<std::string> parameterName) {
        cv::FileStorage fs(filePath, cv::FileStorage::WRITE);
        for (int i = 0; i < parameterName.size(); i++) {
            fs << parameterName[i] << parameter[i];
        }
        fs.release();
    };

    template<typename T>
    static void writeYMLFile(std::string filePath, T &parameter, std::string parameterName) {
        cv::FileStorage fs(filePath, cv::FileStorage::WRITE);
        fs << parameterName << parameter;
        fs.release();
    };

    static const std::string currentDateTime();
};

#endif //FILEREADERWRITER_FILEREADERWRITER_H
