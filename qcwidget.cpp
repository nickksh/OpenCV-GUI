#include "qcwidget.h"
#include "ui_qcwidget.h"
#include <QTimer>
#include <QDebug>


QCWidget::QCWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCWidget),imgProc(new ImgProc)
{
    ui->setupUi(this);
    ui->label->setScaledContents(true);
    ui->originalLabel->setScaledContents(true);
//    ui->label->hide();
    setup();
    filterSetup();
}

QCWidget::~QCWidget()
{
    thread->quit();
    while(!thread->isFinished());
    delete thread;
    imgProc->close();
    delete imgProc;
    delete ui;


}

void QCWidget::setup()
{
    thread = new QThread();
//    thread_ImgProc = new QThread();
    worker = new OpenCVWorker();
//    processing = new ImgProc();
    QTimer *timer = new QTimer();
    timer->setInterval(1);






    connect(this,SIGNAL(sendSetup(int)),worker,SLOT(recieveSetup(int)));

    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(recieveToggleStream()));
    connect(this,SIGNAL(sendToggleStream()),worker,SLOT(recieveToggleStream()));
    connect(ui->spinBox,SIGNAL(valueChanged(int)),ui->knobData,SLOT(setNum(int)));


    ////////Basic Processing connection ////////////
    connect(ui->checkEnabler,SIGNAL(toggled(bool)),worker,SLOT(recieveEnableBinaryThreshold()));
    connect(ui->checkBoxGrayScale,SIGNAL(toggled(bool)),worker,SLOT(recieveEnableGrayScale()));
    ////////Basic Processing connection ////////////


    connect(ui->spinBox,SIGNAL(valueChanged(int)),worker,SLOT(recieveBinaryThreshold(int)));


    ////////Image Processing connection ////////////
    connect(ui->imgprocToggle,SIGNAL(toggled(bool)),this,SLOT(recieveOpenImgProcWindow()));
    connect (ui->imgprocToggle,SIGNAL(toggled(bool)),worker,SLOT(recieveImageBlurEnabled()));

    ////////Image Processing connection ////////////


    ////////Show Image connection ////////////
    connect(timer,SIGNAL(timeout()),worker,SLOT(recieveGrabFrame()));
    connect(worker,SIGNAL(sendOriginalFrame(QImage)),this,SLOT(recieveOriginalFrame(QImage)));
    connect(worker,SIGNAL(sendFrames(QImage)),this,SLOT(recieveFrame(QImage)));
    ////////Show Image connection ////////////

    ////////brightness & contrast connection ////////////
    connect(ui->brightnessBox,SIGNAL(toggled(bool)),worker,SLOT(recieveControlBoxEnabled()));
    connect(ui->brightnessAlpha,SIGNAL(valueChanged(int)),worker,SLOT(recieveSliderAlpha(int)));
    connect(ui->brightnessBeta,SIGNAL(valueChanged(int)),worker,SLOT(recieveSliderBeta(int)));
    connect(ui->brightnessAlpha,SIGNAL(valueChanged(int)),ui->sliderAlphaDisplay ,SLOT(setNum(int)));
    connect(ui->brightnessBeta,SIGNAL(valueChanged(int)),ui->sliderBetaDisplay ,SLOT(setNum(int)));
    ////////brightness & contrast connection ////////////

    timer->start();
    worker->moveToThread(thread);
    timer->moveToThread(thread);
//    processing->moveToThread(thread_ImgProc);

    thread->start();
    emit sendSetup(0);
}

void QCWidget::filterSetup()
{

}

void QCWidget::recieveFrame(QImage frame)
{
    ui->label->setPixmap(QPixmap::fromImage(frame));
}

void QCWidget::recieveToggleStream()
{
    if(!ui->pushButton->text().compare(">")) ui->pushButton->setText("||");
    else if(!ui->pushButton->text().compare("||")) ui->pushButton->setText(">");
    emit sendToggleStream();

}

void QCWidget::recieveOpenImgProcWindow()
{
    if(!(ui->imgprocToggle->isChecked()))
    {
//        imgProc->hide();
//        thread_ImgProc->quit();
//        while(thread_ImgProc->isFinished());
//        delete thread_ImgProc;
        delete imgProc;
    }
    else
    {
//        thread_ImgProc->start();
//        connect(thread_ImgProc, SIGNAL(started()),processing,SLOT(show()));
//        imgProc->show();
        imgProc = new ImgProc();
        imgProc->show();
        connect(imgProc,SIGNAL(indexValue(int,int)),worker,SLOT(recieveFilterImage(int,int)));
    }


}

void QCWidget::recieveOriginalFrame(QImage frame1)
{

    ui->originalLabel->setPixmap(QPixmap::fromImage(frame1));
    ui->label->show();

}

void QCWidget::recieveFilterImage(int indexvalue)
{
qDebug() << "  Index ID: " <<indexvalue;


}


