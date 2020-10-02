#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include "capture.h"

using namespace cv;
using namespace std;


void init_video_capture()
{
    open_device();
    init_device();
    start_capturing();
}

void clear_video_capture()
{
    stop_capturing();
    uninit_device();
    close_device();
}

void set_frame_buffer() {

}

Mat get_frame_from_file()
{
    FILE *f = fopen("frame.bin", "rb");
    fread(my_frame, WIDTH * HEIGHT * 2, 1, f);
    Mat fr_test(HEIGHT, WIDTH, CV_8UC2, (void *)&my_frame);
    Mat bgr_img(HEIGHT, WIDTH, CV_8UC3);
    cvtColor(fr_test, bgr_img, COLOR_YUV2BGR_YUYV);
    fclose(f);
    return bgr_img;
}


Mat get_frame() {
    Mat fr_test(HEIGHT, WIDTH, CV_8UC2, (void *)&my_frame);
    Mat bgr_img(HEIGHT, WIDTH, CV_8UC3);
    cvtColor(fr_test, bgr_img, COLOR_YUV2BGR_YUYV);
    return bgr_img;
}

int main(int, char **)
{
    Mat frame(HEIGHT, WIDTH, CV_8UC3), frame1(512, 512, 0);

    //--- INITIALIZE VIDEOCAPTURE
    //VideoCapture cap;
    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;        // 0 = open default camera
    int apiID = cv::CAP_ANY; // 0 = autodetect default API

    // open selected camera using selected API
    //cap.open(deviceID, apiID);
    // check if we succeeded
    //if (!cap.isOpened()) {
    //    cerr << "ERROR! Unable to open camera\n";
    //    return -1;
    //}
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
         << "Press any key to terminate" << endl;
    init_video_capture();
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        // cap.read(frame);
        // check if we succeeded
        // if (frame.empty()) {
        //    cerr << "ERROR! blank frame grabbed\n";
        //    break;
        // }
        // show live and wait for a key with timeout long enough to show images
        main_step();
        //frame = get_frame_from_file();
        frame = get_frame();
        imshow("Live", frame);
        if (waitKey(10) >= 0)
            break;
    }
    clear_video_capture();
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}