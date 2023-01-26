#ifndef SOAS_MACROS_H
#define SOAS_MACROS_H

#pragma once

#define PR_DEBUG 1     //0 -> without std::cout and cv::imshow
#define PR_RECORD 1     //0 -> Don't record                         1 -> Record every single frame and save in data/videos
#define PR_IMSHOW 1


#if PR_DEBUG==1
#define LOG(x) std::cout << x << std::endl

#else
#define LOG(x) //std::cout << x << std::endl
#define IMSHOW(x,y) // cv::imshow(x,y)
#define WAITKEY(x) // cv::waitKey(x)
#endif

#if PR_IMSHOW==1
#define IMSHOW(x,y) cv::imshow( x, y)
#define WAITKEY(x) cv::waitKey(x)
#define DESTROYWINDOWS cv::destroyAllWindows()
#else
#define IMSHOW(x,y) //cv::imshow( x, y)
#define WAITKEY(x) //cv::waitKey(x)
#define DESTROYWINDOWS //cv::destroyAllWindows()
#endif

#if PR_RECORD==1
#define VIDEOWRITER(x) cv::VideoWriter x
#define RECORDING(x,y) x.write(y)
#define CLOSEVIDEO(x) x.release()

#else
#define VIDEOWRITER(x) //cv::VideoWriter x
#define RECORDING(x,y) //x.write(y)
#define CLOSEVIDEO(x) //x.release()
#endif

#endif //SOAS_MACROS_H
