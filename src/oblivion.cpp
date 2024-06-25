#include "oblivion.hpp"

Oblivion::Oblivion(QWidget *parent)
: QMainWindow(parent)
{
    mWidget->setLayout(mLayout);
    this->setCentralWidget(mWidget);
    this->show();

    mMenuBarSetup();
}

void Oblivion::mMenuBarSetup()
{
    this->setMenuBar(mMenuBar);
    
    mFileMenu = new QMenu("File");

    mFileMenu__open = new QAction("Open");
    mFileMenu__open_recent = new QAction("Open Recent");
    mFileMenu__exit = new QAction("Exit");

    mFileMenu->addAction(mFileMenu__open);
    mFileMenu->addAction(mFileMenu__open_recent);
    mFileMenu->addAction(mFileMenu__exit);

    mMenuBar->addMenu(mFileMenu);

    mAboutMenu = new QMenu("About");

    mMenuBar->addMenu(mAboutMenu);
}

bool Oblivion::OpenImage(QString filepath)
{
    // If file is not passed, show open file dialog
    if (filepath.isEmpty())
    {
        QStringList files = QFileDialog::getOpenFileNames(this);

        if (files.size() == 0)
        {

        } else {

        }
    } else {
        QFile file(filepath);
    }

    return true;
}


Oblivion::~Oblivion() {
}
