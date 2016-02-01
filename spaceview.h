#ifndef SPACEVIEW_H
#define SPACEVIEW_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include "src/view.h"
class SpaceView : public QGraphicsView
{
public:
    SpaceView(QWidget * parent = 0);
    ~SpaceView();

    void setSpaceWidget()


private:
    QGraphicsScene * mScene;
};

#endif // SPACEVIEW_H
