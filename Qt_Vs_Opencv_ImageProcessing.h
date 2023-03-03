#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_Vs_Opencv_ImageProcessing.h"
#include <QLabel>
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")// 该指令仅支持VS环境
#endif

namespace Ui {
    class Qt_Vs_Opencv_ImageProcessing;
    class qt_Vs_Opencv_ImageProcessingClass;
}

class Qt_Vs_Opencv_ImageProcessing : public QMainWindow
{
    Q_OBJECT

public:
    Qt_Vs_Opencv_ImageProcessing(QWidget *parent = nullptr);
    ~Qt_Vs_Opencv_ImageProcessing();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();


private:
    QImage MatToQImage(const cv::Mat& mat);              // Mat类型转为QImage类型；
    void display_MatInQT(QLabel* label, cv::Mat mat);    // Mat 对象 QT显示

private:
    Ui::Qt_Vs_Opencv_ImageProcessingClass *ui;   
    Mat image, Mat_Gaussian, gray, img_erode, img_dilate;
};






