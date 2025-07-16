#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "simcanvas.h"
#include "body.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_simulateButton_clicked();

    void on_addButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Body*> bodies;
    SimCanvas* canvas;
    void loadBodiesFromTable();
    void simulateStep();
    void saveResultsToFile(const QString& filename);
    QTimer* simTimer;
    QVector<QVector<QVector2D>> allPositions;
    int currentStep = 0;
    const int totalSteps = 1000;
    const double dt = 1.0;
};
#endif // MAINWINDOW_H
