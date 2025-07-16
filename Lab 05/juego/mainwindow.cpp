#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QTransform>
#include <QDebug>

const int TAM = 32; // tamaño de cada celda

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 20; ++j) {
            QLabel* celda = new QLabel(this);
            celda->setGeometry(j * TAM, i * TAM, TAM, TAM);
            if (mapa[i][j] == 1) {
                celda->setPixmap(QPixmap("C:/Users/Usuario/Documents/Info-II/Lab 05/juego/imagenes/pared.png").scaled(TAM, TAM));
            } else {
                celda->setPixmap(QPixmap("C:/Users/Usuario/Documents/Info-II/Lab 05/juego/imagenes/punto.png").scaled(TAM, TAM));
                totalPuntos++;
            }
            celdas[i][j] = celda;
            celda->show();
            celda->raise();
        }
    }

    // Crear Pac-Man
    pacman = new QLabel(this);
    QPixmap px("C:/Users/Usuario/Documents/Info-II/Lab 05/juego/imagenes/pacman.png");
    if (px.isNull()) {
        qDebug() << "Error: no se pudo cargar pacman.png";
    }
    pacman->setPixmap(px.scaled(TAM, TAM));
    fila = 1;
    col = 1;
    pacman->move(col * TAM, fila * TAM);
    pacman->show();
    pacman->raise();

    filaFantasma[0] = 7; colFantasma[0] = 10; // Rojo
    filaFantasma[1] = 7; colFantasma[1] = 9;  // Rosa
    filaFantasma[2] = 7; colFantasma[2] = 11; // Azul
    filaFantasma[3] = 6; colFantasma[3] = 10; // Naranja

    QStringList imagenes = {
        "C:/Users/Usuario/Documents/Info-II/Lab 05/juego/imagenes/fantasma1.png",
        "C:/Users/Usuario/Documents/Info-II/Lab 05/juego/imagenes/fantasma2.png",
        "C:/Users/Usuario/Documents/Info-II/Lab 05/juego/imagenes/fantasma3.png",
        "C:/Users/Usuario/Documents/Info-II/Lab 05/juego/imagenes/fantasma4.png"
    };

    for (int i = 0; i < 4; ++i) {
        fantasma[i] = new QLabel(this);
        QPixmap img(imagenes[i]);
        if (img.isNull()) {
            qDebug() << "Error: no se pudo cargar" << imagenes[i];
        }
        fantasma[i]->setPixmap(img.scaled(TAM, TAM, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        fantasma[i]->move(colFantasma[i] * TAM, filaFantasma[i] * TAM);
        fantasma[i]->show();
        fantasma[i]->raise();
    }

    timerFantasmas = new QTimer(this);
    connect(timerFantasmas, &QTimer::timeout, this, &MainWindow::moverFantasmas);
    timerFantasmas->start(300);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int nuevaFila = fila;
    int nuevaCol = col;

    QPixmap original("C:/Users/Usuario/Documents/Info-II/Lab 05/juego/imagenes/pacman.png");
    QPixmap rotada;

    if (original.isNull()) {
        qDebug() << "Error: no se pudo cargar pacman.png al mover";
        return;
    }

    if (event->key() == Qt::Key_W) { // arriba
        nuevaFila -= 1;
        QTransform rotar;
        rotar.rotate(270); // 270° = arriba
        rotada = original.transformed(rotar);
    }
    else if (event->key() == Qt::Key_S) { // abajo
        nuevaFila += 1;
        QTransform rotar;
        rotar.rotate(90); // 90° = abajo
        rotada = original.transformed(rotar);
    }
    else if (event->key() == Qt::Key_A) { // izquierda
        nuevaCol -= 1;
        QTransform rotar;
        rotar.rotate(180); // 180° = izquierda
        rotada = original.transformed(rotar);
    }
    else if (event->key() == Qt::Key_D) { // derecha
        nuevaCol += 1;
        rotada = original; // sin rotación
    }

    // Aplicar imagen rotada
    pacman->setPixmap(rotada.scaled(TAM, TAM, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Verificar colisiones con paredes
    if (mapa[nuevaFila][nuevaCol] == 0) {
        fila = nuevaFila;
        col = nuevaCol;
        pacman->move(col * TAM, fila * TAM);

        if (!celdas[fila][col]->pixmap().isNull()) {
            celdas[fila][col]->clear();
            puntuacion++;

            // Verificar si ganó
            if (puntuacion == totalPuntos) {
                QMessageBox::information(this, "¡Ganaste!", "Has comido todos los puntos.");
                close(); // o reiniciar el nivel
            }
        }
    }
}

void MainWindow::moverFantasmas() {
    for (int i = 0; i < 4; ++i) {
        QVector<QPair<int, int>> direccionesValidas;

        // Validar direcciones dentro de rango y sin pared
        if (filaFantasma[i] > 0 && mapa[filaFantasma[i] - 1][colFantasma[i]] == 0)
            direccionesValidas.append({-1, 0}); // arriba
        if (filaFantasma[i] < 14 && mapa[filaFantasma[i] + 1][colFantasma[i]] == 0)
            direccionesValidas.append({+1, 0}); // abajo
        if (colFantasma[i] > 0 && mapa[filaFantasma[i]][colFantasma[i] - 1] == 0)
            direccionesValidas.append({0, -1}); // izquierda
        if (colFantasma[i] < 19 && mapa[filaFantasma[i]][colFantasma[i] + 1] == 0)
            direccionesValidas.append({0, +1}); // derecha

        if (!direccionesValidas.isEmpty()) {
            int index = QRandomGenerator::global()->bounded(direccionesValidas.size());
            int dx = direccionesValidas[index].first;
            int dy = direccionesValidas[index].second;

            filaFantasma[i] += dx;
            colFantasma[i] += dy;
            fantasma[i]->move(colFantasma[i] * TAM, filaFantasma[i] * TAM);
        }

        // Verificar colisión con Pac-Man
        if (filaFantasma[i] == fila && colFantasma[i] == col) {
            QMessageBox::information(this, "¡Perdiste!", "Uno de los fantasmas te atrapó.");
            close();
            return;
        }
    }
}
