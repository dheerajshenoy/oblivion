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
#include <qt6/QtGui/QShortcut>
#include <qt6/QtGui/QKeySequence>
#include <qt6/QtGui/QAction>


#include <qt6/QtCore/QFile>
#include <qt6/QtCore/QFileInfo>

#include "gview.hpp"
#include "statusbar.hpp"

class Oblivion : public QMainWindow
{
public:
    Oblivion(int argc, char ** argv, QWidget *parent = nullptr);
    ~Oblivion();

    bool OpenImage(QString filepath = "");
    void ZoomImage(float factor);
    void RotateImage(float angle);
    void FlipImageV();
    void FlipImageH();
    void FullScreenImage();
    void SlideShow(QStringList imagepaths, bool loop = false);
    void Exit();


private:
    QWidget *mWidget;
    QVBoxLayout *mLayout;
    QMenuBar *mMenuBar;
    StatusBar *mStatusBar;
    QSplitter *mSplitter;

    QMenu   *mFileMenu,
            *mEditMenu,
            *mImageMenu,
            *mSlideShowMenu,
            *mImageMenu_FlipMenu,
            *mImageMenu_RotateMenu,
            *mAboutMenu;


    QAction *mFileMenu__open,
            *mFileMenu__open_recent,
            *mFileMenu__exit,
            *mEditMenu__prefs,
            *mImageMenu__rotate_clock,
            *mImageMenu__rotate_anticlock,
            *mImageMenu__flip_horizontal,
            *mImageMenu__flip_vertical,
            *mSlideShowMenu__toggle_slideshow;


    void mMenuBarSetup();
    void mShortcutsSetup();
    bool mNextImage();
    void mToggleSlideShow();
    void mSetSlideShowState(bool);

    QStringList convertCharArrayToQStringList(char **charArray, int count);

    QImage mImg;

    float   mGlobalZoom = 1.0f,
            mGlobalAngle = 0.0f;

    GView *mView;

    const float VERSION = 0.1;

    bool mFullScreenMode = false;

    // In seconds
    const float SLIDE_SHOW_INTERVAL = 5; 

    QStringList mSlideShowList;
    bool mSlideShowLoop, mSlideShowState = false;
    QTimer *mSlideShowTimer;

    int mSlideShowIndex = 1;
};


