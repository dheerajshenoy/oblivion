#include "gview.hpp"
#include "qwidget.h"

GView::GView(QWidget *parent)
    : QGraphicsView(parent)
{

    mScene = new QGraphicsScene();
    /*setTransformationAnchor(QGraphicsView::AnchorViewCenter);*/
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setScene(mScene);
    this->show();
}

bool GView::addItem(QGraphicsItem *item)
{
    mScene->addItem(item);
    return true;
}

bool GView::setPixmap(const QPixmap& pix)
{
    if (!mPixItem)
    {
        qDebug() << "DD";
        mPixItem = mScene->addPixmap(pix);
    }
    else {
        mPixItem->setPixmap(pix);
        mPixItem->setPos(0, 0);
        mScene->setSceneRect(QRectF(0, 0, pix.width(), pix.height()));
    }

    scale(1, 1);
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
