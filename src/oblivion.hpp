#include <qt6/QtWidgets/QApplication>
#include <qt6/QtWidgets/QWidget>
#include <qt6/QtWidgets/QLabel>
#include <qt6/QtWidgets/QPushButton>
#include <qt6/QtWidgets/QToolBar>
#include <qt6/QtWidgets/QVBoxLayout>
#include <qt6/QtWidgets/QHBoxLayout>
#include <qt6/QtWidgets/QSplitter>
#include <qt6/QtWidgets/QMainWindow>
#include <qt6/QtWidgets/QMenuBar>
#include <qt6/QtWidgets/QMenu>
#include <qt6/QtWidgets/QFileDialog>

#include <qt6/QtCore/QFile>
#include <qt6/QtCore/QFileInfo>

class Oblivion : public QMainWindow
{
public:
    Oblivion(QWidget *parent = nullptr);
    ~Oblivion();

    bool OpenImage(QString filepath);

private:
    QWidget *mWidget = new QWidget();
    QVBoxLayout *mLayout = new QVBoxLayout();
    QMenuBar *mMenuBar = new QMenuBar();

    QMenu *mFileMenu,
          *mAboutMenu;

    QAction *mFileMenu__open,
            *mFileMenu__open_recent,
            *mFileMenu__exit;

    void mMenuBarSetup();
};
