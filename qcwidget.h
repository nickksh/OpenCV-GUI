#ifndef QCWIDGET_H
#define QCWIDGET_H

#include <QWidget>
#include <QThread>
#include "opencvworker.h"
#include "imgproc.h"

namespace Ui {
class QCWidget;
}

class QCWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QCWidget(QWidget *parent = 0);
    ~QCWidget();

private:
    Ui::QCWidget *ui;
    QThread *thread,*thread_ImgProc;
    ImgProc *imgProc, *processing;
    OpenCVWorker *worker;

    void setup();
    void filterSetup();

signals:
    void sendSetup(int device);
    void sendToggleStream();

private slots:
    void recieveFrame(QImage frame);
    void recieveToggleStream();
    void recieveOpenImgProcWindow();
    void recieveOriginalFrame(QImage frame1);

    void recieveFilterImage(int indexvalue);
};

#endif // QCWIDGET_H
