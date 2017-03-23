#include "imgproc.h"
#include "ui_imgproc.h"
#include <QDebug>

ImgProc::ImgProc(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::ImgProc)
{
    ui->setupUi(this);

    ui->filterBox->addItem(" ");
    ui->filterBox->addItem("Gaussian Blur");
    ui->filterBox->addItem("Median Blur");
    ui->filterBox->addItem("Homogenous Blur");
    ui->filterBox->addItem("Bilateral Blur");


}

ImgProc::~ImgProc()
{
    delete ui;
}



void ImgProc::on_filterBox_currentIndexChanged(int index)
{
    emit indexValue(index, ui->kernelLength->value());
    qDebug() << "Index value on filterboxChanged" << index;
}

void ImgProc::on_kernelLength_valueChanged(int arg1)
{
    emit indexValue(ui->filterBox->currentIndex(), arg1);
}
