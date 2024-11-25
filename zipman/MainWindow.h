#ifndef ZIPMAN_H
#define ZIPMAN_H

#include <QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openFile();
    void extractZip();
    void addToArchive();
    void createNewArchive();
    void updateTree();

private:
    QString currentArchivePath;
    QString new_archive_path;
    QTreeView* tree;
    QStandardItemModel* model;
};

#endif // ZIPMAN_H
