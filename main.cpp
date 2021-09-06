 #include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //open qss file
    QFile file(":/dark_orange/style.qss");
    file.open(QFile::ReadOnly);

    QString styleSheet { QLatin1String(file.readAll()) };

    //setup stylesheet
    w.setStyleSheet(styleSheet);
    w.show();
    return a.exec();
}
