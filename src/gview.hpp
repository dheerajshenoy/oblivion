#include <qt6/QtWidgets/QGraphicsView>
#include <qt6/QtWidgets/QGraphicsItem>
#include <qt6/QtWidgets/QGraphicsScene>
#include <qt6/QtWidgets/QGraphicsPixmapItem>
#include <qt6/QtGui/QWheelEvent>

class GView : public QGraphicsView
{

public:
    GView(QWidget *parent = nullptr);
    ~GView();

    bool addItem(QGraphicsItem *item);
    bool setPixmap(const QPixmap& pix);

protected:
    void wheelEvent(QWheelEvent *e) override;

private:
    QGraphicsScene* mScene;
    QGraphicsPixmapItem *mPixItem;
};
