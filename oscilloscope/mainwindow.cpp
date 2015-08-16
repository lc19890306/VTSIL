#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText(tr("Pause"));
    // offset = 0;
    offset = dim - 2000;
    gain = ui->horizontalSlider_g->value();
    timer.start(100);

    QMetaObject::connectSlotsByName(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(doUpdate()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->horizontalSlider_s, SIGNAL(valueChanged(int)), this, SLOT(textChanged_s(int)));
    connect(ui->lineEdit_s, SIGNAL(textChanged(QString)), this, SLOT(valueChanged_s(QString)));
    connect(ui->horizontalSlider_g, SIGNAL(valueChanged(int)), this, SLOT(textChanged_g(int)));
    connect(ui->lineEdit_g, SIGNAL(textChanged(QString)), this, SLOT(valueChanged_g(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::textChanged_s(int v)
{
    QString s = QString::number(v);
    ui->lineEdit_s->setText(s);
}

void
MainWindow::valueChanged_s(QString s)
{
    int v = s.toInt();
    ui->horizontalSlider_s->setValue(v);
}

void
MainWindow::textChanged_g(int v)
{
    QString s = QString::number(v);
    ui->lineEdit_g->setText(s);
}

void
MainWindow::valueChanged_g(QString s)
{
    int v = s.toInt();
    ui->horizontalSlider_g->setValue(v);
}

void
MainWindow::doUpdate()
{
    if (offset < 2000)
        offset = dim - 2000;
    offset -= ui->horizontalSlider_s->value();
    // if (offset >= dim - 2000)
    //     offset = 0;
    // offset += ui->horizontalSlider_s->value();
    gain = ui->horizontalSlider_g->value();
    update();
}

void
MainWindow::on_pushButton_clicked()
{
    if (timer.isActive())
    {
        timer.stop();
        ui->pushButton->setText(tr("Resume"));
    }
    else
    {
        timer.start(100);
        ui->pushButton->setText(tr("Pause"));
    }
}

void
MainWindow::insertPoints(double *points, const int &dim)
{
    this->points = points;
    this->dim = dim;
    this->offset = dim - 2000;
}

void
MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPoint upper_left(100, 200), low_right(1100, 700);
    QRect rect(upper_left, low_right);
    QBrush brush("#349D84");
    painter.setBrush(brush);
    brush.setColor("#349D84");
    painter.drawRect(rect);
    QPen pen;
    pen.setColor("#307867");
    pen.setWidth(3);
    painter.setPen(pen);
    int x = (low_right.x() + upper_left.x()) / 2.0;
    int y = (low_right.y() + upper_left.y()) / 2.0;
    painter.drawLine(upper_left.x(), y, low_right.x(), y);
    painter.drawLine(x, upper_left.y(), x, low_right.y());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect);

    painter.setPen(Qt::yellow);
    QPointF points[2000];
    for (size_t i(0); i != 2000; ++i)
        points[i] = QPointF(upper_left.x() + i * 0.5, gain * this->points[i + offset] + y);
    painter.drawPolyline(points, 2000);
}
