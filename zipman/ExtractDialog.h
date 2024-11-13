#ifndef ExtractDialog_H
#define ExtractDialog_H

#include <QDialog>
#include <QLineEdit>

class ExtractDialog : public QDialog {
    Q_OBJECT

public:
    ExtractDialog(const QString& archivePath, QWidget* parent = nullptr);

private slots:
    void fileDia();
    void extractZip();

private:
    QString archivePath;
    QLineEdit* pathExt;
};

#endif // ExtractDialog_H
