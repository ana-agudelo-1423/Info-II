#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include "pacman.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

    inline void setMoveSpeed(qint8 ms) {moveSpeed = ms;}
protected:
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void hmov();
    void bgmov();
private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    Pacman  *pacman;
    QTimer *timer, *bgTimer;
    QGraphicsPixmapItem *bgImage1, *bgImage2;
    qint8 moveSpeed = 1;
    QPixmap fondo;
};
#endif // WIDGET_H
