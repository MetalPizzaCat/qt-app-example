#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(ui->graphicsView);
    scene->setSceneRect(-200, -200, 400, 400);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    triangle = new Triangle(QPointF(0, 0), QPointF(120, 100), QPointF(100, 0));
    scene->addItem(triangle);

    _updateInfo();

    connect(ui->aXEdit, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::_aXCoordValueChanged);
    connect(ui->bXEdit, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::_bXCoordValueChanged);
    connect(ui->cXEdit, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::_cXCoordValueChanged);
    connect(ui->aYEdit, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::_aYCoordValueChanged);
    connect(ui->bYEdit, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::_bYCoordValueChanged);
    connect(ui->cYEdit, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::_cYCoordValueChanged);
}

void MainWindow::_aXCoordValueChanged(double value)
{
    triangle->SetA(QPointF(value, triangle->GetA().y()));
    _updateInfo();
}
void MainWindow::_bXCoordValueChanged(double value)
{
    triangle->SetB(QPointF(value, triangle->GetB().y()));
    _updateInfo();
}
void MainWindow::_cXCoordValueChanged(double value)
{
    triangle->SetC(QPointF(value, triangle->GetC().y()));
    _updateInfo();
}
void MainWindow::_aYCoordValueChanged(double value)
{
    triangle->SetA(QPointF(triangle->GetA().x(), value));
    _updateInfo();
}

void MainWindow::_bYCoordValueChanged(double value)
{
    triangle->SetB(QPointF(triangle->GetB().x(), value));
    _updateInfo();
}
void MainWindow::_cYCoordValueChanged(double value)
{
    triangle->SetC(QPointF(triangle->GetC().x(), value));
    _updateInfo();
}

void MainWindow::_updateInfo()
{
    ui->labelAltAB->setText("Altitude AB: " + QString::number(triangle->GetAltitudeLengthForAB()));
    ui->labelAltBC->setText("Altitude BC: " + QString::number(triangle->GetAltitudeLengthForBC()));
    ui->labelAltCA->setText("Altitude CA: " + QString::number(triangle->GetAltitudeLengthForCA()));

    ui->labelBisAB->setText("Bisect AB: " + QString::number(triangle->GetBisectLengthForAB()));
    ui->labelBisBC->setText("Bisect BC: " + QString::number(triangle->GetBisectLengthForBC()));
    ui->labelBisCA->setText("Bisect CA: " + QString::number(triangle->GetBisectLengthForCA()));

    scene->update();
}
MainWindow::~MainWindow()
{
    delete ui;
}
