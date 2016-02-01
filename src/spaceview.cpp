#include "spaceview.h"

SpaceView::SpaceView(QWidget * parent):
    QGraphicsView(parent)
{
    mScene = new QGraphicsScene;
    setScene(mScene);


    setInteractive(true);

}

SpaceView::~SpaceView()
{

}

void SpaceView::setUniverseWidget(view::UniverseWidget *widget)
{
    mUniverseWidget = widget;
    mScene->addWidget(widget);
}

void SpaceView::wheelEvent(QWheelEvent * event)
{

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor = 1.15;
    if (event->delta()>0)
    {
        scale(scaleFactor,scaleFactor);
    }

    else {
        scale (1. / scaleFactor, 1. / scaleFactor);
    }


}



