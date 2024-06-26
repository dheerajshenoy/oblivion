#include "scrollarea.hpp"

ScrollArea::ScrollArea(QWidget *parent)
    : QScrollArea(parent)
{
    this->setBackgroundRole(QPalette::Dark);
    this->setAlignment(Qt::AlignCenter);

}

void ScrollArea::FitToWindow()
{
    this->setWidgetResizable(true);
}



ScrollArea::~ScrollArea()
{}
