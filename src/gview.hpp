#include <qt6/QtWidgets/QGraphicsView>
#include <qt6/QtWidgets/QGraphicsItem>
#include <qt6/QtWidgets/QGraphicsScene>
#include <qt6/QtGui/QWheelEvent>

class GView : public QGraphicsView
{

public:
    GView(QWidget *parent = nullptr);
    ~GView();

    QGraphicsScene& Scene() { return mScene; }
    bool addItem(QGraphicsItem *item);
    bool addPixmap(const QPixmap pix);

protected:
    void wheelEvent(QWheelEvent *e) override;

private:
    QGraphicsScene mScene;
};
