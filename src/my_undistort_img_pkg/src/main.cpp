#include "include/camera.h"

int main(int argc, char **argv) {
    Camera* cam = new Camera("rtsp://192.168.73.11:8554/h264", 1280, 720 );
    cam->getImage(true);
    return 0;
}