#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsWidget>
#include "OOP/Shapes.hpp"

#include <QDoubleSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void _aXCoordValueChanged(double value);
    void _bXCoordValueChanged(double value);
    void _cXCoordValueChanged(double value);
    void _aYCoordValueChanged(double value);
    void _bYCoordValueChanged(double value);
    void _cYCoordValueChanged(double value);
private:
    void _updateInfo();
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Triangle *triangle;
};
#endif // MAINWINDOW_H
