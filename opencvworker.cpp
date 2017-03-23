#include "opencvworker.h"
#include <QDebug>



OpenCVWorker::OpenCVWorker(QObject *parent) : QObject(parent),
    status(false),
    toggleStream(false),
    binaryThreshold(127),binaryThresholdEnabled(false),
    grayScaleEnable(false),
    controlBoxEnabled(false), imageBlurEnabled(false)
{
    _capture = new VideoCapture();

}


OpenCVWorker::~OpenCVWorker()
{
        if(_capture->isOpened())
        {
            _capture->release();
            delete _capture;
        }
}


void OpenCVWorker::recieveGrabFrame(){
    if(!toggleStream) return;

    (*_capture) >> _frameOriginal;
    if(_frameOriginal.empty())  return;


    if(controlBoxEnabled)
   {
       _sliderValue();
   }
    process();


    _origProcess();

    if(imageBlurEnabled)
    {
//        Mat tempvec;
//        _frameProcessed = tempvec;
        blurEffect();
//       return;
    }

    if(grayScaleEnable)
    {
        QImage _output((const unsigned char *)_frameProcessed.data, _frameProcessed.cols, _frameProcessed.rows,QImage::Format_Indexed8);
        emit sendFrames(_output);
    }
    else
    {
        QImage _output((const unsigned char *)_frameProcessed.data, _frameProcessed.cols, _frameProcessed.rows,QImage::Format_ARGB32);
        emit sendFrames(_output);
    }



}

void OpenCVWorker::recieveSetup(const int device)
{
        checkIfDeviceOpened(device);
        if(!_capture->isOpened())
        {
            status= false;
            return;
        }

        status = true;
}

void OpenCVWorker::recieveToggleStream()
{
    toggleStream = !toggleStream;

}

void OpenCVWorker::recieveEnableGrayScale()
{
    grayScaleEnable = !grayScaleEnable;

}

void OpenCVWorker::recieveSliderAlpha(int sliderValue)
{
    sliderAlphaValue = (double)sliderValue/4;
}

void OpenCVWorker::recieveSliderBeta(int sliderValue)
{
    sliderBetaValue = (double)sliderValue/4;
}

void OpenCVWorker::recieveControlBoxEnabled()
{
    controlBoxEnabled = !controlBoxEnabled;
}

void OpenCVWorker::recieveImageBlurEnabled()
{
    imageBlurEnabled = !imageBlurEnabled;
}

void OpenCVWorker::recieveFilterImage(int index, int kernellength)
{
    filterIndex = index;
    qDebug() << "Filer from recieve " << index;
    kernelLength = kernellength;

}


void OpenCVWorker::checkIfDeviceOpened(const int device)
{
        if(_capture->isOpened()) _capture->release();
        _capture->open(device);
}

void OpenCVWorker::process()
{

    if(grayScaleEnable)
        cvtColor(_frameOriginal,_frameProcessed,COLOR_BGR2GRAY);
    else
        cvtColor(_frameOriginal,_frameProcessed,COLOR_BGR2BGRA);

    if(binaryThresholdEnabled)
    {
        threshold(_frameProcessed,_frameProcessed,binaryThreshold,255,THRESH_BINARY );
    }

}

void OpenCVWorker::_origProcess()
{
    if(grayScaleEnable)
    {
        cvtColor(_frameOriginal,_frameOriginal,COLOR_BGR2GRAY);
        QImage _Originaloutput((const unsigned char *)_frameOriginal.data, _frameOriginal.cols, _frameOriginal.rows,QImage::Format_Indexed8);
         emit sendOriginalFrame(_Originaloutput);
    }
    else
    {
        cvtColor(_frameOriginal,_frameOriginal,COLOR_BGR2BGRA);
        QImage _Originaloutput((const unsigned char *)_frameOriginal.data, _frameOriginal.cols, _frameOriginal.rows,QImage::Format_ARGB32);
        emit sendOriginalFrame(_Originaloutput);
    }

}

void OpenCVWorker::_sliderValue()
{


    Mat new_Image = Mat::zeros(_frameOriginal.size(),_frameOriginal.type());


    for(int y =0; y< _frameOriginal.rows;y++)
    {
        for(int x =0;x<_frameOriginal.cols;x++)
        {
            for(int c =0;c<3;c++)
            {
                new_Image.at<Vec3b>(y,x)[c] =
                        saturate_cast<uchar> (sliderAlphaValue *(_frameOriginal.at<Vec3b>(y,x)[c]) + sliderBetaValue);
       //         qDebug() << "Slider Alpha Value: " <<sliderAlphaValue << "slider Beta Value: " << sliderBetaValue;
            }
        }
    }
 //   _frameOriginal.convertTo(new_Image,-1,sliderAlphaValue,sliderBetaValue);

    _frameOriginal = new_Image;

}

void OpenCVWorker::blurEffect()
{

    //    qDebug() << "filter Index" << filterIndex;
    for ( int i = 1; i < kernelLength; i = i + 2 )
    {
        if(filterIndex == 1)
            GaussianBlur( _frameOriginal, _frameProcessed, Size( i, i ), 0, 0 );
        if(filterIndex == 2)
            medianBlur(_frameOriginal, _frameProcessed,i );
        if(filterIndex == 3)
            blur(_frameOriginal, _frameProcessed, Size( i, i ), Point(-1,-1));
        if(filterIndex == 4)
            bilateralFilter(_frameOriginal, _frameProcessed, i, i*2, i/2 );
    }
}


void OpenCVWorker::recieveEnableBinaryThreshold()
{
    binaryThresholdEnabled = !binaryThresholdEnabled;

}

void OpenCVWorker::recieveBinaryThreshold(int Threshold)
{
    binaryThreshold = Threshold;
}


