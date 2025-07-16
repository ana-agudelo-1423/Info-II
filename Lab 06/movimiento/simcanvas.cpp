#include "simcanvas.h"

#include <QPainter>

SimCanvas::SimCanvas(QWidget *parent) : QWidget(parent) {}

void SimCanvas::setPositions(const QVector<QVector<QVector2D>>& newPositions) {
    positions = newPositions;
    update(); // esto fuerza a que paintEvent se llame
}

void SimCanvas::paintEvent(QPaintEvent *) {
    if (positions.isEmpty()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);

    int w = width();
    int h = height();

    // 1. Centrar en el cuerpo más masivo
    QVector2D centerWorld;
    if (!positions[0].isEmpty()) {
        centerWorld = positions[0][0]; // asume que el cuerpo 0 es el más masivo
    }

    // 2. Calcular límites relativos al centro
    float maxRadius = 1.0f;
    for (const QVector<QVector2D>& step : positions) {
        for (const QVector2D& pos : step) {
            float dist = (pos - centerWorld).length();
            if (dist > maxRadius)
                maxRadius = dist;
        }
    }

    float scale = qMin(w, h) / (2.2f * maxRadius);  // 10% margen

    QPointF canvasCenter(w / 2.0, h / 2.0);

    // 3. Dibujar trayectorias
    for (int i = 0; i < positions[0].size(); ++i) {
        QColor color = QColor::fromHsv((i * 80) % 360, 255, 200);
        painter.setPen(QPen(color, 1.5));

        for (const QVector<QVector2D>& step : positions) {
            QVector2D p = step[i] - centerWorld;
            float x = p.x() * scale + canvasCenter.x();
            float y = -p.y() * scale + canvasCenter.y();
            painter.drawPoint(QPointF(x, y));
        }
    }
}


