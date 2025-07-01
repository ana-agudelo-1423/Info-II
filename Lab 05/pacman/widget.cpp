#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    fondo.load("C:/Users/Usuario/Documents/Info-II/Lab 05/pacman/build/Desktop_Qt_6_8_2_MinGW_64_bit-Debug/fondo.jpg");

    if (!fondo.isNull()) {
        QPixmap fondoEscalado = fondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette paleta;
       paleta.setBrush(QPalette::Window, QBrush(fondoEscalado));
        this->setAutoFillBackground(true);
        this->setPalette(paleta);
    } else {
        QMessageBox::critical(this, "Error", "No se pudo cargar la imagen.");
    }
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
