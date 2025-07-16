#ifndef SIMCANVAS_H
#define SIMCANVAS_H
#include <QWidget>
#include <QVector>
#include <QVector2D>

class SimCanvas : public QWidget {
    Q_OBJECT

public:
    explicit SimCanvas(QWidget *parent = nullptr);
    void setPositions(const QVector<QVector<QVector2D>>& newPositions);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QVector<QVector2D>> positions; // posiciones[step][cuerpo]
};

#endif // SIMCANVAS_H
