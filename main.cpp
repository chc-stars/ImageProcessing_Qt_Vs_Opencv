#include "Qt_Vs_Opencv_ImageProcessing.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt_Vs_Opencv_ImageProcessing w;
    w.show();
    return a.exec();
}

