#include "statusbar.hpp"

StatusBar::StatusBar(QWidget *parent)
    : QWidget(parent)
{

    mMsgLabel = new QLabel();
    mFileNameLabel = new QLabel("NAME");
    mFilePathLabel = new QLabel("PATH");
    mFileSizeLabel = new QLabel("SIZE");
    mFileTypeLabel = new QLabel("FT");

    mLayout = new QHBoxLayout();

    this->setMaximumHeight(30);
    this->setFixedHeight(30);
    this->setFixedHeight(30);

    mLayout->addWidget(mMsgLabel);
    mLayout->addWidget(mFileNameLabel, 1);
    mLayout->addWidget(mFileSizeLabel);
    mLayout->addWidget(mFileTypeLabel);
    mLayout->addWidget(mFilePathLabel);

    this->setLayout(mLayout);

    Message("HELLO WORLD", 2);
}

void StatusBar::Message(QString text, int s)
{
    mMsgLabel->show();
    mMsgLabel->setText(text);
    QTimer::singleShot(s * 1000, [&]() { mMsgLabel->hide(); });
}

void StatusBar::SetFileName(QString text)
{
    mFileNameLabel->setText(text);
}

void StatusBar::SetFilePath(QString text)
{
    mFilePathLabel->setText(text);
}

void StatusBar::SetFileType(QString text)
{
    mFileTypeLabel->setText(text);
}

void StatusBar::SetFileSize(qint64 size)
{
    QLocale locale = this->locale();
    mFileSizeLabel->setText(locale.formattedDataSize(size));
}

StatusBar::~StatusBar()
{

}


