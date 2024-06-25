#include <qt6/QtWidgets/QWidget>
#include <qt6/QtWidgets/QHBoxLayout>
#include <qt6/QtWidgets/QLabel>

#include <qt6/QtCore/QTimer>
#include <qt6/QtCore/QLocale>

class StatusBar : public QWidget
{

public:
    StatusBar(QWidget *parent = nullptr);
    ~StatusBar();

    void Message(QString text, int s = 5);
    void SetFileName(QString text);
    void SetFilePath(QString text);
    void SetFileType(QString text);
    void SetFileSize(qint64 size);

private:
    QLabel  *mMsgLabel,
            *mFileNameLabel,
            *mFileSizeLabel,
            *mFileTypeLabel,
            *mFilePathLabel;

    QHBoxLayout *mLayout;
};
