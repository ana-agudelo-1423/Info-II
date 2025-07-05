#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Pacman : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Pacman(QObject *parent = nullptr);
    void setBanLeft(bool value) { banLeft = value; }
    void setBanRight(bool value) { banRight = value; }
    void setBanUp(bool value) { banUp = value; }
    void setBanDown(bool value) { banDown = value; }
    // Métodos inline pueden quedarse aquí
    void setVelocity(qreal vel) { velocity = vel; }
    void setMovementbans(bool left, bool right, bool up, bool down) {

        banLeft = left;
        banRight = right;
        banUp = up;
        banDown = down;
    }

    void setSceneBounds(const QRectF &bounds) { sceneBounds = bounds; }
    QRectF getSceneBounds() const { return sceneBounds; }

public slots:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

private:
    bool checkBounds(qreal newX, qreal newY) const;

    qreal velocity = 1.0;
    QRectF sceneBounds;
    bool banLeft;
    bool banRight;
    bool banUp;
    bool banDown;


};

#endif // PACMAN_H
