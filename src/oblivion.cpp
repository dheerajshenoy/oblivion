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

    mFileMenu__open = new QAction("Open");
    mFileMenu__open_recent = new QAction("Open Recent");
    mFileMenu__exit = new QAction("Exit");

    connect(mFileMenu__open, &QAction::triggered, this, [=]() {
        Oblivion::OpenImage();
    });

    mFileMenu->addAction(mFileMenu__open);
    mFileMenu->addAction(mFileMenu__open_recent);
    mFileMenu->addAction(mFileMenu__exit);

    mMenuBar->addMenu(mFileMenu);

    mAboutMenu = new QMenu("About");

    mMenuBar->addMenu(mAboutMenu);
}

void Oblivion::mShortcutsSetup()
{
    QShortcut
    *mZoomIn = new QShortcut(QKeySequence("="), this),
    *mZoomOut = new QShortcut(QKeySequence("-"), this);

    connect(mZoomIn, &QShortcut::activated, this, [&]() { Oblivion::ZoomImage(1.25); });
    connect(mZoomOut, &QShortcut::activated, this, [&]() { Oblivion::ZoomImage(0.8); });
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
    mGlobalFactor *= factor;

    mView->scale(mGlobalFactor, mGlobalFactor);
}

Oblivion::~Oblivion() {
}
