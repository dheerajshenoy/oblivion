#include "oblivion.hpp"
#include "qshortcut.h"

Oblivion::Oblivion(QWidget *parent)
: QMainWindow(parent)
{
    mWidget = new QWidget();
    mLayout = new QVBoxLayout();
    mMenuBar = new QMenuBar();
    mView = new GView();

    mStatusBar = new StatusBar();

    mLayout->addWidget(mView);
    mLayout->addWidget(mStatusBar);

    mWidget->setLayout(mLayout);

    mLayout->setContentsMargins(0, 0, 0, 0);
    this->setCentralWidget(mWidget);

    mMenuBarSetup();
    mShortcutsSetup();

    OpenImage("/home/neo/Downloads/wall.png");
    this->show();
}

void Oblivion::mMenuBarSetup()
{
    this->setMenuBar(mMenuBar);
    
    mFileMenu = new QMenu("File");
    mEditMenu = new QMenu("Edit");
    mImageMenu = new QMenu("Image");
    mImageMenu_FlipMenu = new QMenu("Flip");
    mImageMenu_RotateMenu = new QMenu("Rotate");

    mFileMenu__open = new QAction("Open");
    mFileMenu__open_recent = new QAction("Open Recent");
    mFileMenu__exit = new QAction("Exit");

    connect(mFileMenu__open, &QAction::triggered, this, [=]() {
        Oblivion::OpenImage();
    });

    connect(mFileMenu__exit, &QAction::triggered, this, [=]() {
        Oblivion::Exit();
    });

    mFileMenu->addAction(mFileMenu__open);
    mFileMenu->addAction(mFileMenu__open_recent);
    mFileMenu->addAction(mFileMenu__exit);

    mEditMenu__prefs = new QAction("Preferences");
    mEditMenu->addAction(mEditMenu__prefs);


    mImageMenu__rotate_clock = new QAction("Clockwise");
    mImageMenu__rotate_anticlock = new QAction("Anti-Clockwise");

    connect(mImageMenu__rotate_clock, &QAction::triggered, this, [&]() { Oblivion::RotateImage(90); });
    connect(mImageMenu__rotate_anticlock, &QAction::triggered, this, [&]() { Oblivion::RotateImage(-90); });

    mImageMenu_RotateMenu->addAction(mImageMenu__rotate_clock);
    mImageMenu_RotateMenu->addAction(mImageMenu__rotate_anticlock);

    mImageMenu__flip_vertical = new QAction("Vertical");
    mImageMenu__flip_horizontal = new QAction("Horizontal");

    mImageMenu_FlipMenu->addAction(mImageMenu__flip_vertical);
    mImageMenu_FlipMenu->addAction(mImageMenu__flip_horizontal);

    connect(mImageMenu__flip_vertical, &QAction::triggered, this, [&]() { Oblivion::FlipImageV(); });
    connect(mImageMenu__flip_horizontal, &QAction::triggered, this, [&]() { Oblivion::FlipImageH(); });

    mImageMenu->addMenu(mImageMenu_RotateMenu);
    mImageMenu->addMenu(mImageMenu_FlipMenu);

    mAboutMenu = new QMenu("About");

    mMenuBar->addMenu(mFileMenu);
    mMenuBar->addMenu(mEditMenu);
    mMenuBar->addMenu(mImageMenu);
    mMenuBar->addMenu(mAboutMenu);
}

void Oblivion::mShortcutsSetup()
{
    QShortcut
    *mZoomIn = new QShortcut(QKeySequence("="), this),
    *mZoomOut = new QShortcut(QKeySequence("-"), this),
    *mRotateClock = new QShortcut(QKeySequence("."), this),
    *mRotateAntiClock = new QShortcut(QKeySequence(","), this),
    *mFullScreenImage = new QShortcut(QKeySequence("Shift+F"), this);

    connect(mZoomIn, &QShortcut::activated, this, [&]() { Oblivion::ZoomImage(1.25); });
    connect(mZoomOut, &QShortcut::activated, this, [&]() { Oblivion::ZoomImage(0.8); });
    connect(mRotateClock, &QShortcut::activated, this, [&]() { Oblivion::RotateImage(90); });
    connect(mRotateAntiClock, &QShortcut::activated, this, [&]() { Oblivion::RotateImage(-90); });
    connect(mFullScreenImage, &QShortcut::activated, this, [&]() { Oblivion::FullScreenImage(); });
}

bool Oblivion::OpenImage(QString filepath)
{
    // If file is not passed, show open file dialog
    if (filepath.isEmpty())
    {
        auto files = QFileDialog::getOpenFileNames(this);

        // If no file selected
        if (files.size() == 0)
        {
            QMessageBox::critical(this, "Error", "Please select atleast one image");
            return false;
        } else {
            QFileInfo fileinfo(files[0]);
            QMimeDatabase db;
            QMimeType mimetype = db.mimeTypeForFile(fileinfo.filePath(), QMimeDatabase::MatchContent);
            mStatusBar->SetFileName(fileinfo.fileName());
            mStatusBar->SetFilePath(fileinfo.filePath());
            mStatusBar->SetFileType(mimetype.name());
            mStatusBar->SetFileSize(fileinfo.size());

            mImg = QImage(files[0]);
            mView->addPixmap(QPixmap::fromImage(mImg));

            return true;
        }
    } else {
        QFileInfo fileinfo(filepath);
        if (fileinfo.exists())
        {
            QMimeDatabase db;
            QMimeType mimetype = db.mimeTypeForFile(fileinfo.filePath(), QMimeDatabase::MatchContent);
            mStatusBar->SetFileName(fileinfo.fileName());
            mStatusBar->SetFilePath(fileinfo.filePath());
            mStatusBar->SetFileType(mimetype.name());
            mStatusBar->SetFileSize(fileinfo.size());

            mImg = QImage(filepath);
            mView->addPixmap(QPixmap::fromImage(mImg));

            return true;
        }
        else return false;
    }

    return true;
}

void Oblivion::ZoomImage(float factor)
{
    mGlobalZoom *= factor;
    mView->scale(mGlobalZoom, mGlobalZoom);
}

void Oblivion::RotateImage(float angle)
{
    mGlobalAngle = angle;

    mView->rotate(angle);
}

void Oblivion::FlipImageH()
{
    mView->scale(-1, 1);
}

void Oblivion::FlipImageV()
{
    mView->scale(1, -1);
}

void Oblivion::FullScreenImage()
{

    if (!mFullScreenMode)
    {
        this->showMaximized();
        this->showFullScreen();

        mMenuBar->hide();
        mStatusBar->hide();
    }
    else {
        this->showNormal();
        mMenuBar->show();
        mStatusBar->show();
    }

    mFullScreenMode = !mFullScreenMode;
}

void Oblivion::Exit()
{
    QApplication::exit();
}

Oblivion::~Oblivion() {
}
