#include <QtGui/QApplication>
#include "h5fileanalyzer.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    H5FileAnalyzer analyzer(app.argc(), app.arguments());
    MainWindow w;
    w.insertPoints(analyzer.getPoints(), analyzer.getDim());
    w.show();

    return app.exec();
}
