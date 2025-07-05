#include "Pacman.h"
#include <QTimer>
#include <QGraphicsScene>

Pacman::Pacman(QObject *parent) : QObject(parent), QGraphicsPixmapItem()
{
    banLeft = false;
    banRight = false;
    banUp = false;
    banDown = false;

    QTimer *timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(moveLeft()));
    timer1->start(20);

    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(moveRight()));
    timer2->start(20);

    QTimer *timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(moveUp()));
    timer3->start(20);

    QTimer *timer4 = new QTimer(this);
    connect(timer4, SIGNAL(timeout()), this, SLOT(moveDown()));
    timer4->start(20);
}

bool Pacman::checkBounds(qreal newX, qreal newY) const
{
    // Consideramos el tamaño del boundingRect
    return (newX >= sceneBounds.left()) &&
           (newX + boundingRect().width() * scale() <= sceneBounds.right()) &&
           (newY >= sceneBounds.top()) &&
           (newY + boundingRect().height() * scale() <= sceneBounds.bottom());
}

void Pacman::moveLeft()
{
    if (!banLeft)
    {
        qreal newX = x() - velocity;
        if (checkBounds(newX, y()))
            setPos(newX, y());
    }
}

void Pacman::moveRight()
{
    if (!banRight)
    {
        qreal newX = x() + velocity;
        if (checkBounds(newX, y()))
            setPos(newX, y());
    }
}

void Pacman::moveUp()
{
    if (!banUp)
    {
        qreal newY = y() - velocity;
        if (checkBounds(x(), newY))
            setPos(x(), newY);
    }
}

void Pacman::moveDown()
{
    if (!banDown)
    {
        qreal newY = y() + velocity;
        if (checkBounds(x(), newY))
            setPos(x(), newY);
    }
}
