#ifndef OPENCVWORKER_H
#define OPENCVWORKER_H

#include <QObject>
#include <QObject>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>

using namespace cv;
using namespace std;





class OpenCVWorker : public QObject
{
    Q_OBJECT
    Mat _frameOriginal,_frameProcessed;
    VideoCapture *_capture;

    bool status, toggleStream,binaryThresholdEnabled,grayScaleEnable, controlBoxEnabled,imageBlurEnabled;
    int binaryThreshold, filterIndex,kernelLength;
    double sliderAlphaValue = 1.0,sliderBetaValue = 1.0;

    void checkIfDeviceOpened(const int device);

    void process();
    void _origProcess();
    void _sliderValue();
    void blurEffect();
public:
    explicit OpenCVWorker(QObject *parent = 0);
    ~OpenCVWorker();

signals:
    void sendFrames(QImage frameProcessed);
    void sendStatus(QString msg, int code);
    void sendOriginalFrame(QImage originalOutput);



public slots:
    void recieveEnableBinaryThreshold();
    void recieveBinaryThreshold(int Threshold);
    void recieveGrabFrame();
    void recieveSetup(const int device);
    void recieveToggleStream();
    void recieveEnableGrayScale();
    void recieveSliderAlpha(int sliderValue);
    void recieveSliderBeta(int sliderValue);
    void recieveControlBoxEnabled();
    void recieveImageBlurEnabled();
    void recieveFilterImage(int index, int kernellength);
};

#endif // OPENCVWORKER_H
