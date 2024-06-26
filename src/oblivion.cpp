#include "oblivion.hpp"

Oblivion::Oblivion(int argc, char ** argv, QWidget *parent)
: QMainWindow(parent)
{
    mSplitter = new QSplitter(Qt::Orientation::Horizontal);
    mWidget = new QWidget();
    mLayout = new QVBoxLayout();
    mMenuBar = new QMenuBar();
    /*mView = new GView();*/

    mImgLabel = new QLabel();
    mImgLabel->setBackgroundRole(QPalette::Base);
    mImgLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    mImgLabel->setScaledContents(true);

    mScrollArea = new ScrollArea();

    mScrollArea->setWidget(mImgLabel);
    mStatusBar = new StatusBar();

    /*mLayout->addWidget(mView);*/
    mLayout->addWidget(mScrollArea);
    mLayout->addWidget(mStatusBar);

    mWidget->setLayout(mLayout);

    mLayout->setContentsMargins(0, 0, 0, 0);
    this->setCentralWidget(mWidget);

    mMenuBarSetup();
    mShortcutsSetup();

    auto images = Oblivion::convertCharArrayToQStringList(argv, argc);

    images.removeAt(0);

    if (images.size() == 1)
    {
        OpenImage(images[0]);
    }

    this->show();
}

bool Oblivion::mNextImage()
{
    if (mSlideShowIndex < mSlideShowList.size())
    {
        OpenImage(mSlideShowList.at(mSlideShowIndex));
        mSlideShowIndex++;
        return true;
    }
    else if (mSlideShowLoop)
    {
        mSlideShowIndex = 0;
        OpenImage(mSlideShowList.at(mSlideShowIndex));
        return true;
    }
    return false;
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
    mFileMenu__save = new QAction("Save");
    mFileMenu__exit = new QAction("Exit");

    connect(mFileMenu__open, &QAction::triggered, this, [=]() {
        Oblivion::OpenImage();
    });

    connect(mFileMenu__save, &QAction::triggered, this, [=]() {
        Oblivion::SaveImage();
    });

    connect(mFileMenu__exit, &QAction::triggered, this, [=]() {
        Oblivion::Exit();
    });

    mFileMenu->addAction(mFileMenu__open);
    mFileMenu->addAction(mFileMenu__open_recent);
    mFileMenu->addAction(mFileMenu__save);
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
    mSlideShowMenu = new QMenu("Slideshow");

    mSlideShowMenu__toggle_slideshow = new QAction("Start");

    mSlideShowMenu->addAction(mSlideShowMenu__toggle_slideshow);

    connect(mSlideShowMenu__toggle_slideshow, &QAction::triggered, this, [&]() {
        Oblivion::mToggleSlideShow();
    });

    mMenuBar->addMenu(mFileMenu);
    mMenuBar->addMenu(mEditMenu);
    mMenuBar->addMenu(mImageMenu);
    mMenuBar->addMenu(mSlideShowMenu);
    mMenuBar->addMenu(mAboutMenu);
}

void Oblivion::mShortcutsSetup()
{
    QShortcut
    *mZoomIn = new QShortcut(QKeySequence("="), this),
    *mZoomOut = new QShortcut(QKeySequence("-"), this),
    *mRotateClock = new QShortcut(QKeySequence("."), this),
    *mRotateAntiClock = new QShortcut(QKeySequence(","), this),
    *mFullScreenImage = new QShortcut(QKeySequence("Shift+F"), this),
    *mSlideShowToggle = new QShortcut(QKeySequence("Space"), this);

    connect(mZoomIn, &QShortcut::activated, this, [&]() { Oblivion::ZoomImage(1.25); });
    connect(mZoomOut, &QShortcut::activated, this, [&]() { Oblivion::ZoomImage(0.8); });
    connect(mRotateClock, &QShortcut::activated, this, [&]() { Oblivion::RotateImage(90); });
    connect(mRotateAntiClock, &QShortcut::activated, this, [&]() { Oblivion::RotateImage(-90); });
    connect(mFullScreenImage, &QShortcut::activated, this, [&]() { Oblivion::FullScreenImage(); });
    connect(mSlideShowToggle, &QShortcut::activated, this, [&]() { Oblivion::mToggleSlideShow(); });
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


            QImageReader reader(files[0]);
            reader.setAutoTransform(true);
            mImg = reader.read();
            mImgLabel->setPixmap(QPixmap::fromImage(mImg));
            mImgLabel->resize(mImgLabel->pixmap().size());
            ZoomImage(1);

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

            QImageReader reader(filepath);
            reader.setAutoTransform(true);
            mImg = reader.read();

            return true;
        } else {

            QMessageBox::critical(this, "Error", QString("Unable to open the image" + fileinfo.filePath()));
            return false;
        }
    }

    return true;
}

void Oblivion::ZoomImage(float factor)
{
    mGlobalZoom *= factor;

    mImgLabel->resize(mGlobalZoom * mImgLabel->pixmap(Qt::ReturnByValue).size());

    adjustScrollBar(mScrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(mScrollArea->verticalScrollBar(), factor);

}

void Oblivion::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void Oblivion::RotateImage(float angle)
{
    mGlobalAngle = angle;

    /*mView->rotateImage(angle);*/
}

void Oblivion::FlipImageH()
{
    /*mView->scale(-1, 1);*/
}

void Oblivion::FlipImageV()
{
    /*mView->scale(1, -1);*/
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

void Oblivion::mToggleSlideShow()
{

    if (mSlideShowList.size() == 0)
    {
        QMessageBox::information(this, "Slideshow Error", "No slideshow images selected");
        return;
    }

    if (mSlideShowState)
    {
        mSlideShowTimer->stop();
        mStatusBar->Message("Slideshow paused", 2);
        mSlideShowMenu__toggle_slideshow->setText("Resume");
    }
    else {
        mSlideShowTimer->start();
        mStatusBar->Message("Slideshow resumed", 2);
        mSlideShowMenu__toggle_slideshow->setText("Pause");
    }

    mSlideShowState = !mSlideShowState;
}

// FIX : handle start and stop of the timer here
void Oblivion::mSetSlideShowState(bool state)
{

    if (state)
    {
        /*mSlideShowTimer->stop();*/
        mStatusBar->Message("Slideshow paused", 2);
        mSlideShowMenu__toggle_slideshow->setText("Resume");
    }
    else {
        /*mSlideShowTimer->start();*/
        mStatusBar->Message("Slideshow resumed", 2);
        mSlideShowMenu__toggle_slideshow->setText("Pause");
    }

    mSlideShowState = state;
}

void Oblivion::SlideShow(QStringList imagepaths, bool loop)
{

    mSetSlideShowState(true);

    if (!mSlideShowTimer)
        mSlideShowTimer = new QTimer();

    OpenImage(imagepaths[0]);
    mSlideShowList = imagepaths;
    mSlideShowTimer = new QTimer();
    
    mSlideShowTimer->setInterval(SLIDE_SHOW_INTERVAL * 1000);

    if (!loop)
    {
        connect(mSlideShowTimer, &QTimer::timeout, this, [&]() {
            if(!mNextImage())
            {
                mSlideShowTimer->stop();
            }
        });
    } else {
        connect(mSlideShowTimer, &QTimer::timeout, this, [&]() {
            mNextImage();
        });
    }

    mSlideShowTimer->start();
}

QStringList Oblivion::convertCharArrayToQStringList(char **charArray, int count)
{
    QStringList stringList;

    for (int i = 0; i < count; ++i) {
        stringList.append(QString(charArray[i]));
    }

    return stringList;
}

void Oblivion::Exit()
{
    QApplication::exit();
}

bool Oblivion::SaveImage(QString filename)
{
    if (!filename.isEmpty())
    {
        /*mView->SavePixmap(filename);*/
    }
    else {
        QString filename = QFileDialog::getSaveFileName(this, "Save file");

        if (!filename.isEmpty())

            try {
                /*mView->grab().save(filename);*/
                /*mView->SavePixmap(filename);*/
            } catch (std::exception &e) {
                QMessageBox::critical(this, "Error Saving File", "Could not save the file due to " + QString(e.what()));
            }
        else
            QMessageBox::critical(this, "Error Saving File", "Could not save the file under the given filename");
    }
    
    return true;
}

Oblivion::~Oblivion() {
}
