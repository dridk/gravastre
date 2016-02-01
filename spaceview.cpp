#include "spaceview.h"

SpaceView::SpaceView(QWidget * parent = 0):
    QGraphicsView(parent)
{
    mScene = new QGraphicsScene;
    setScene(mScene);


}

SpaceView::~SpaceView()
{

}


