#include "body.h"
#include <cmath>

const double G = 1.0;

Body::Body(double m, double r, QVector2D pos, QVector2D vel)
    : mass(m), radius(r), position(pos), velocity(vel), acceleration(0, 0) {}

void Body::computeAcceleration(const QVector<Body*>& others) {
    acceleration = QVector2D(0, 0);
    for (auto* other : others) {
        if (other == this) continue;

        QVector2D r = other->position - position;
        double distSq = r.lengthSquared() + 1e-5;
        acceleration += G * other->mass / distSq * r.normalized();
    }
}

void Body::update(double dt) {
    velocity += acceleration * dt;
    position += velocity * dt + 0.5 * acceleration * dt * dt;
}
