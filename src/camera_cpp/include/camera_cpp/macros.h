#ifndef CAMERA_MACROS_H
#define CAMERA_MACROS_H

#define PR_DEBUG 1     //0 -> without std::cout
#define PR_IMSHOW 1

#if PR_DEBUG==1
#define LOG(x) std::cout << x << std::endl

#else
#define LOG(x) //std::cout << x << std::endl
#endif

#if PR_IMSHOW==1
#define IMSHOW(x,y,z) cv::imshow( x, y); cv::waitKey(z)
#define DESTROYWINDOWS cv::destroyAllWindows()
#else
#define IMSHOW(x,y) //cv::imshow( x, y); cv::waitKey(x)
#define DESTROYWINDOWS //cv::destroyAllWindows()
#endif

#endif //CAMERA_MACROS_H