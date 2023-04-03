#include <iostream>
#include "fileReaderWriter.h"

int main() {
    std::string installedCameraAddress;
    FileReaderWriter::listDirsOfDirectory("../data");
    FileReaderWriter::readYMLFile("./data/perspTransMatrix.yml", installedCameraAddress, "Birdview");
    std::cout << installedCameraAddress << std::endl;
    return 0;
}
