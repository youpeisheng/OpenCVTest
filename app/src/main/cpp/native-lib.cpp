#include "com_example_opencvtest_NativeActivity.h"
#include <android/bitmap.h>
#include <opencv2/opencv.hpp>

using namespace cv;

extern "C" JNIEXPORT void
JNICALL Java_com_example_opencvtest_NativeActivity_getEdge
        (JNIEnv *env, jobject obj, jobject bitmap) {
    AndroidBitmapInfo info;
    void *pixels;

    CV_Assert(AndroidBitmap_getInfo(env, bitmap, &info) >= 0);
    CV_Assert(info.format == ANDROID_BITMAP_FORMAT_RGBA_8888 ||
              info.format == ANDROID_BITMAP_FORMAT_RGB_565);
    CV_Assert(AndroidBitmap_lockPixels(env, bitmap, &pixels) >= 0);
    CV_Assert(pixels);
    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        Mat temp(info.height, info.width, CV_8UC4, pixels);
        Mat gray;
        cvtColor(temp, gray, COLOR_RGBA2GRAY);
        Canny(gray, gray, 45, 75);
        cvtColor(gray, temp, COLOR_GRAY2RGBA);
    } else {
        Mat temp(info.height, info.width, CV_8UC2, pixels);
        Mat gray;
        cvtColor(temp, gray, COLOR_RGB2GRAY);
        Canny(gray, gray, 45, 75);
        cvtColor(gray, temp, COLOR_GRAY2RGB);
    }
    AndroidBitmap_unlockPixels(env, bitmap);
}