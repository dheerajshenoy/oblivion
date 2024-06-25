#include "gview.hpp"
#include "qwidget.h"

GView::GView(QWidget *parent)
    : QGraphicsView(parent)
{

    /*setTransformationAnchor(QGraphicsView::AnchorViewCenter);*/
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    setDragMode(QGraphicsView::ScrollHandDrag);
    setScene(&mScene);
    this->show();
}

bool GView::addItem(QGraphicsItem *item)
{
    mScene.addItem(item);
    return true;
}

bool GView::addPixmap(const QPixmap pix)
{
    mScene.addPixmap(pix);

    return true;
}

void GView::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier)
    {
        if (e->angleDelta().y() > 0)
            scale(1.25, 1.25);
        else
            scale(0.8, 0.8);

        return;
    }

    QGraphicsView::wheelEvent(e);
}

GView::~GView()
{}
