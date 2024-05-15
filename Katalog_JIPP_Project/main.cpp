#include "Katalog_JIPP_Project.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Katalog_JIPP_Project w;
    w.show();
    return a.exec();
}
