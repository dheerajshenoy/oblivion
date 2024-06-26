#include <qt6/QtWidgets/QScrollArea>
#include <qt6/QtWidgets/QScrollBar>
#include <qt6/QtGui/QMouseEvent>
#include <qt6/QtGui/QPainter>

class ScrollArea : public QScrollArea
{

public:
    ScrollArea(QWidget *parent = nullptr);
    ~ScrollArea();

    void setPixmap(const QPixmap &pix) {
        m_pixmap = pix;
        m_rect = m_pixmap.rect();
        m_rect.translate(-m_rect.center());
        update();
    }

    void scale(qreal s) {
        m_scale *= s;
        update();
    }

    void FitToWindow();

protected:

    
private:

    QPixmap m_pixmap;
    QRectF m_rect;
    QPointF m_reference;
    QPointF m_delta;
    qreal m_scale = 1.0;

};
