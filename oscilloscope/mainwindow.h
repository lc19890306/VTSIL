#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QLabel>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void insertPoints(double *points, const int &dim);
    void paintEvent(QPaintEvent *event);
    
public slots:
    void textChanged_s(int v);
    void valueChanged_s(QString s);
    void textChanged_g(int v);
    void valueChanged_g(QString s);
    void doUpdate();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    double *points;
    int dim;
    size_t offset;
    int gain;
    QTimer timer;
};

#endif // MAINWINDOW_H
