#include "gview.hpp"
#include "qwidget.h"

GView::GView(QWidget *parent)
    : QGraphicsView(parent)
{

    mScene = new QGraphicsScene();
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

void GView::rotateImage(float angle)
{
    mPixItem->setPixmap(rotatePixmap(mPixItem->pixmap(), angle));
}

QPixmap GView::rotatePixmap(const QPixmap pixmap, qreal rotationAngle)
{
    if (pixmap.isNull()) {
        return QPixmap();
    }

    QTransform transform;
    transform.rotate(rotationAngle);

    QPixmap rotatedPixmap(pixmap.size());
    rotatedPixmap.fill(Qt::transparent); // Ensure the background is transparent

    QPainter painter(&rotatedPixmap);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setTransform(transform);
    painter.drawPixmap(0, 0, pixmap);
    painter.end();

    return rotatedPixmap;
}

bool GView::SavePixmap(QString filename)
{
    if (mPixItem) {

        QRectF bounds = mPixItem->boundingRect();
        QImage img(bounds.size().toSize(), QImage::Format_ARGB32);
        img.fill(Qt::transparent);

        QPainter painter(&img);
        mScene->render(&painter, QRectF(), bounds);
        painter.end();

        img.save(filename);
    }

    return false;
}

QGraphicsPixmapItem* GView::pixitem()
{
    return mPixItem;
}

GView::~GView()
{}
