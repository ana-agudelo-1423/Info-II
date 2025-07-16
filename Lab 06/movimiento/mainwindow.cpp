#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "body.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    canvas = new SimCanvas(this);

    // Crear layout si no existe
    if (!ui->canvas->layout()) {
        QVBoxLayout* layout = new QVBoxLayout(ui->canvas);
        layout->setContentsMargins(0, 0, 0, 0); // opcional
        layout->addWidget(canvas);
    }
    simTimer = new QTimer(this);
    connect(simTimer, &QTimer::timeout, this, &MainWindow::simulateStep);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadBodiesFromTable() {
    bodies.clear();

    int rowCount = ui->tableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        bool valid = true;
        QList<double> values;

        for (int j = 0; j < 6; ++j) {
            QTableWidgetItem* item = ui->tableWidget->item(i, j);
            if (!item) {
                valid = false;
                break;
            }
            bool ok;
            double val = item->text().toDouble(&ok);
            if (!ok) {
                valid = false;
                break;
            }
            values.append(val);
        }

        if (valid) {
            Body* b = new Body(values[2], values[3],
                               QVector2D(float(values[0]), float(values[1])),
                               QVector2D(float(values[4]), float(values[5])));
            bodies.append(b);
        }
    }
}

void MainWindow::on_simulateButton_clicked() {
    loadBodiesFromTable();
    if (bodies.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "No hay cuerpos válidos para simular.");
        return;
    }

    QFile file("resultados.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "No se pudo abrir resultados.txt.");
        return;
    }

    QTextStream out(&file);
    const int steps = 100000;
    const double dt = 1.0;
    QVector<QVector<QVector2D>> allPositions;

    for (int step = 0; step < steps; ++step) {
        for (Body* b : bodies) b->computeAcceleration(bodies);
        for (Body* b : bodies) b->update(dt);

        QVector<QVector2D> snapshot;
        for (Body* b : bodies) {
            snapshot.append(b->position);
            out << b->position.x() << '\t' << b->position.y() << '\t';
        }
        out << '\n';
        allPositions.append(snapshot);
    }

    simTimer->start(10);
    file.close();
    canvas->setPositions(allPositions);
    QMessageBox::information(this, "Simulación completa", "Resultados guardados en resultados.txt");
}
void MainWindow::simulateStep() {
    if (currentStep >= totalSteps) {
        simTimer->stop();
        QMessageBox::information(this, "Simulación finalizada", "La simulación ha terminado.");
        return;
    }

    for (Body* b : bodies)
        b->computeAcceleration(bodies);
    for (Body* b : bodies)
        b->update(dt);

    QVector<QVector2D> snapshot;
    for (Body* b : bodies)
        snapshot.append(b->position);

    allPositions.append(snapshot);
    canvas->setPositions(allPositions);
    currentStep++;
}

void MainWindow::on_addButton_clicked()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    for (int col = 0; col < 6; ++col) {
        ui->tableWidget->setItem(row, col, new QTableWidgetItem(""));
    }
}

