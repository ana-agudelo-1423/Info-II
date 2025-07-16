#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void moverFantasmas();
private:
    Ui::MainWindow *ui;

    // Constante para tamaño de las celdas
    static const int TAM = 32;

    // Mapa del laberinto: 0 = camino, 1 = pared
    int mapa[15][20] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,0,1},
        {1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1},
        {1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1},
        {1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1},
        {1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,0,1,0,1},
        {1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1},
        {1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    // Representación gráfica de cada celda
    QLabel* celdas[15][20];

    // Pac-Man
    QLabel* pacman;

    // Posición actual de Pac-Man
    int fila;
    int col;

    // Puntos acumulados
    int puntuacion = 0;
    int totalPuntos = 0;

    QLabel* fantasma[4];          // Etiquetas para los 4 fantasmas
    int filaFantasma[4];          // Fila actual de cada fantasma
    int colFantasma[4];           // Columna actual de cada fantasma
    QTimer* timerFantasmas;       // Temporizador para mover todos
};
#endif // MAINWINDOW_H
