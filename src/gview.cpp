#include "gview.hpp"

GView::GView(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setScene(&mScene);
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

GView::~GView()
{}
