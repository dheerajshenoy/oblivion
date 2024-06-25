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
#include <qt6/QtWidgets/QMessageBox>
#include <qt6/QtCore/QMimeDatabase>
#include <qt6/QtCore/QMimeType>

#include <qt6/QtGui/QImage>
#include <qt6/QtGui/QAction>


#include <qt6/QtCore/QFile>
#include <qt6/QtCore/QFileInfo>

#include "gview.hpp"
#include "statusbar.hpp"

class Oblivion : public QMainWindow
{
public:
    Oblivion(QWidget *parent = nullptr);
    ~Oblivion();

    bool OpenImage(QString filepath = "");

private:
    QWidget *mWidget;
    QVBoxLayout *mLayout;
    QMenuBar *mMenuBar;
    StatusBar *mStatusBar;

    QMenu *mFileMenu,
          *mAboutMenu;

    QAction *mFileMenu__open,
            *mFileMenu__open_recent,
            *mFileMenu__exit;


    void mMenuBarSetup();

    QImage mImg;

    GView *mView;
};

