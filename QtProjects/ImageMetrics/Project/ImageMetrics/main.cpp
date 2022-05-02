#include "imagemetrics.h"

#include <QApplication>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QTreeView>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QScreen>

int main(int argc, char *argv[])
{
    qDebug( "MAIN");
    QApplication a(argc, argv);

    ImageMetrics window;
    window.show();


    return a.exec();
}
