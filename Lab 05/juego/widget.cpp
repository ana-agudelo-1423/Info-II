#include "widget.h"
#include "ui_widget.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <QMessageBox>


#define UP     	72
#define DOWN    80
#define LEFT  	75
#define RIGHT   77
#define ESC		27
#define LIMITE_DERECHO (LIMITE_IZQUIERDO + COLUMNAS_MAPA - 1)
#define LIMITE_INFERIOR (LIMITE_SUPERIOR + FILAS_MAPA - 1)
#define LIMITE_IZQUIERDO   1
#define LIMITE_SUPERIOR    0


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);

    scene = new QGraphicsScene(0, 0, 800, 600, this); // Ancho: 800, Alto: 600

    // Configurar el graphicsView

    // Configurar un fondo temporal para debug
    scene->setBackgroundBrush(Qt::darkGray);

    // Añadir un texto de prueba
    QGraphicsTextItem *textItem = scene->addText("GraphicsView Funcionando!");
    textItem->setPos(50, 50);
    textItem->setDefaultTextColor(Qt::white);
    fondo.load("C:/Users/Usuario/Documents/Info-II/Lab 05/juego/build/Desktop_Qt_6_8_2_MinGW_64_bit-Debug/fondo.jpeg");

    if (!fondo.isNull()) {
        QPixmap fondoEscalado = fondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette paleta;
       paleta.setBrush(QPalette::Window, QBrush(fondoEscalado));
        this->setAutoFillBackground(true);
        this->setPalette(paleta);
    } else {
        QMessageBox::critical(this, "Error", "No se pudo cargar la imagen.");
    }
    // Añadir pacman
    pacman = new Pacman(this);
    pacman->setVelocity(5.0);
    pacman->setSceneBounds(scene->sceneRect());  // Establecer límites
    pacman->setPixmap(QPixmap("C:/Users/Usuario/Documents/Info-II/Lab 05/juego/build/Desktop_Qt_6_8_2_MinGW_64_bit-Debug/primero.png"));
    pacman->setPos(50, 150);
    pacman->setScale(0.07); // reducir el tamaño de la pacman
    scene->addItem(pacman);

    // Definir la señal de movimiento del fondo
    bgTimer = new QTimer(this);
    connect(bgTimer, SIGNAL(timeout()), this, SLOT(bgmov()));
    bgTimer->start(20);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (!fondo.isNull()) {
        QPixmap fondoEscalado = fondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette pal;
        pal.setBrush(QPalette::Window, fondoEscalado);
        this->setPalette(pal);
    }
}
void Widget::hmov()
{

}
/*void Widget::bgmov()
{
    bgImage1->moveBy(-moveSpeed, 0);
    bgImage2->moveBy(-moveSpeed, 0);

    if (bgImage1->x() + bgImage1->pixmap().width() <= 0)
        bgImage1->setX(bgImage2->x() + bgImage2->pixmap().width());

    if (bgImage2->x() + bgImage2->pixmap().width() <= 0)
        bgImage2->setX(bgImage1->x() + bgImage1->pixmap().width());
}
*/
//Funciones de movimiento
void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W)
        pacman->setBanUp(false);   // permitir moverse arriba
    else if (event->key() == Qt::Key_S)
        pacman->setBanDown(false);
    else if (event->key() == Qt::Key_A)
        pacman->setBanLeft(false);
    else if (event->key() == Qt::Key_D)
        pacman->setBanRight(false);
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W)
        pacman->setBanUp(true);   // bloquear movimiento arriba
    else if (event->key() == Qt::Key_S)
        pacman->setBanDown(true);
    else if (event->key() == Qt::Key_A)
        pacman->setBanLeft(true);
    else if (event->key() == Qt::Key_D)
        pacman->setBanRight(true);
}
