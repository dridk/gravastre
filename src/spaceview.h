#ifndef SPACEVIEW_H
#define SPACEVIEW_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include "view.h"

class SpaceView: public QGraphicsView
{
public:
    SpaceView(QWidget * parent=0);
    ~SpaceView();
    void setUniverseWidget(view::UniverseWidget * widget);

protected:
    virtual void wheelEvent(QWheelEvent*);

private:
    QGraphicsScene * mScene;
    view::UniverseWidget * mUniverseWidget;
};

#endif // SPACEVIEW_H
