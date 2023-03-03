#include "Qt_Vs_Opencv_ImageProcessing.h"
#include <QMessageBox>
#include "ui_Qt_Vs_Opencv_ImageProcessing.h"


Qt_Vs_Opencv_ImageProcessing::Qt_Vs_Opencv_ImageProcessing(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Qt_Vs_Opencv_ImageProcessingClass)

{
    // setMinimumSize(600, 600); setMaximumSize(12000, 12000);
    ui->setupUi(this);
    ui->pushButton_1->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
}


Qt_Vs_Opencv_ImageProcessing::~Qt_Vs_Opencv_ImageProcessing()
{
}

void Qt_Vs_Opencv_ImageProcessing::on_pushButton_clicked()
{
    //调用窗口打开文件
    ui->label->clear();

    ui->label_2->clear();
    QString filename = QFileDialog::getOpenFileName(this,
        tr("open image"),
        ".",
        tr("Image file(*.png *.jpg *.bmp)"));
    image = imread(filename.toLocal8Bit().data());

    if (image.data) {
        ui->pushButton_1->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        // 通过 lable 方式显示图片
        display_MatInQT(ui->label, image);
    }
    else
    {
        QMessageBox::information(this, tr("Warning"), tr("The picture was not loaded successfully！"), QMessageBox::Ok);
    }
}

void Qt_Vs_Opencv_ImageProcessing::display_MatInQT(QLabel* label, Mat mat)
{

    label->setPixmap(QPixmap::fromImage(MatToQImage(mat)).scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

QImage Qt_Vs_Opencv_ImageProcessing::MatToQImage(const cv::Mat& mat)
{

    // 8-bits unsigned, NO. OF CHANNELS = 1
    if (mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for (int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar* pSrc = mat.data;
        for (int row = 0; row < mat.rows; row++)
        {
            uchar* pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if (mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar* pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, (int)mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if (mat.type() == CV_8UC4)
    {
        //qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar* pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, (int)mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        //qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

void Qt_Vs_Opencv_ImageProcessing::on_pushButton_1_clicked()
{
    ui->label_2->clear();

    if (image.data)
    {
        // 灰度化
        cvtColor(image, gray, COLOR_BGR2GRAY);
        display_MatInQT(ui->label_2, gray);
    }
    else
    {
        QMessageBox::information(this, tr("Warning"), tr("The picture was not loaded successfully！"), QMessageBox::Ok);
    }

}

void Qt_Vs_Opencv_ImageProcessing::on_pushButton_2_clicked()
{
    ui->label_2->clear();

    if (image.data)
    {
        // 高斯模糊
        GaussianBlur(image, Mat_Gaussian, Size(19, 19), 0, 0);
        display_MatInQT(ui->label_2, Mat_Gaussian);
    }
    else
    {
        QMessageBox::information(this, tr("Warning"), tr("The picture was not loaded successfully！"), QMessageBox::Ok);
    }

}



void Qt_Vs_Opencv_ImageProcessing::on_pushButton_3_clicked()
{
    ui->label_2->clear();

    if (image.data)
    {
        // 边缘检测

        Canny(image, gray, 125, 100, 3);
        display_MatInQT(ui->label_2, gray);
    }
    else
    {
        QMessageBox::information(this, tr("Warning"), tr("The picture was not loaded successfully！"), QMessageBox::Ok);
    }

}

void Qt_Vs_Opencv_ImageProcessing::on_pushButton_4_clicked()
{
    ui->label_2->clear();

    if (image.data)
    {
        // 腐蚀
        
        //获取自定义核
        Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));

        erode(image, img_erode,element); 
        display_MatInQT(ui->label_2, img_erode);
    }
    else
    {
        QMessageBox::information(this, tr("Warning"), tr("The picture was not loaded successfully！"), QMessageBox::Ok);
    }

}

void Qt_Vs_Opencv_ImageProcessing::on_pushButton_5_clicked()
{
    ui->label_2->clear();

    if (image.data)
    {
        // 膨胀
        //获取自定义核
        Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
        dilate(image, img_dilate, element); // 膨胀
        display_MatInQT(ui->label_2, img_dilate);
    }
    else
    {
        QMessageBox::information(this, tr("Warning"), tr("The picture was not loaded successfully！"), QMessageBox::Ok);
    }

}