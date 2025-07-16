#ifndef BODY_H
#define BODY_H

#include <QVector>
#include <QVector2D>

class Body {
public:
    Body(double mass, double radius, QVector2D position, QVector2D velocity);

    void computeAcceleration(const QVector<Body*>& others);
    void update(double dt);

    QVector2D position;
    QVector2D velocity;
    QVector2D acceleration;

    double mass;
    double radius;
};


#endif // BODY_H
