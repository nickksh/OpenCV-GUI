#ifndef IMGPROC_H
#define IMGPROC_H

#include <QGroupBox>

namespace Ui {
class ImgProc;
}

class ImgProc : public QGroupBox
{
    Q_OBJECT

public:
    explicit ImgProc(QWidget *parent = 0);
    ~ImgProc();

signals:
    void indexValue(int indexValue, int kernelLength);

private slots:
     void on_filterBox_currentIndexChanged(int index);

     void on_kernelLength_valueChanged(int arg1);

private:
    Ui::ImgProc *ui;
};

#endif // IMGPROC_H
