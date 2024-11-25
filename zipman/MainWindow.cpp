#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDir>
#include <QFile>
#include <QDirIterator>
#include <QInputDialog>
#include <QErrorMessage>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QGridLayout>
#include <QIcon>
#include <QDebug>
#include <QStandardItem>
#include <QCoreApplication>

#include "MainWindow.h"
#include "NoFile.h"
#include "ExtractDialog.h"
#include <zip.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("ZIP Manager");
    setGeometry(100, 100, 600, 400);

    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);

    QToolBar* toolbar = addToolBar("MainToolBar");
    toolbar->setMovable(false);

    QAction* openAction = new QAction(QIcon("icons/document-open.png"), "Open Archive", this);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    toolbar->addAction(openAction);

    QAction* extractAction = new QAction(QIcon("icons/insert-object.png"), "Extract Archive", this);
    connect(extractAction, &QAction::triggered, this, &MainWindow::extractZip);
    toolbar->addAction(extractAction);

    QAction* addAction = new QAction(QIcon("icons/list-add.png"), "Add to Archive", this);
    connect(addAction, &QAction::triggered, this, &MainWindow::addToArchive);
    toolbar->addAction(addAction);

    QAction* newAction = new QAction(QIcon("icons/document-new.png"), "New Archive", this);
    connect(newAction, &QAction::triggered, this, &MainWindow::createNewArchive);
    toolbar->addAction(newAction);

    QAction* exitAction = new QAction(QIcon("icons/window-close.png"), "Exit", this);
    connect(exitAction, &QAction::triggered, this, &QCoreApplication::quit);
    toolbar->addAction(exitAction);

    QVBoxLayout* layout = new QVBoxLayout(widget);
    tree = new QTreeView(this);
    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList() << "Files");
    tree->setModel(model);
    layout->addWidget(tree);
}

void MainWindow::openFile() {
    currentArchivePath = QFileDialog::getOpenFileName(this, "Выбрать zip-файл", "", "ZIP Archive (*.zip *.jar);;Все файлы (*)");
    if (!currentArchivePath.isEmpty()) {
            updateTree();
    }
}

void MainWindow::extractZip() {
    if (!currentArchivePath.isEmpty()) {
        ExtractDialog* dialog = new ExtractDialog(currentArchivePath, this);
        dialog->exec();
    } else {
        NoFile* error = new NoFile();
        error->exec();
    }
}

void MainWindow::addToArchive() {
    // Логика добавления в архив
}

void MainWindow::createNewArchive() {
    // Логика создания нового архива
    new_archive_path = QFileDialog::getSaveFileName(this, "Создать новый zip-файл", "", "ZIP Archive (*.zip)");
    if (new_archive_path.isEmpty()) {
            return;
        }
}

void MainWindow::updateTree() {
    if (currentArchivePath.isEmpty()) {
            return;
        }

    model->clear();
    model->setHorizontalHeaderLabels(QStringList() << "Files");
    // Логика обновления дерева файлов
    int err = 0;
    zip* zf = zip_open(currentArchivePath.toStdString().c_str(), 0, &err);
    if (zf == nullptr) {
        qDebug() << "Failed to open ZIP archive:" << currentArchivePath;
        return;
    }

    zip_int64_t numEntries = zip_get_num_entries(zf, 0);
    for (zip_int64_t i = 0; i < numEntries; ++i) {
        const char* fileName = zip_get_name(zf, i, 0);
        if (fileName) {
            QStringList items = QString(fileName).split('/');
            QStandardItem* parent = model->invisibleRootItem();

            for (const QString& item : items) {
                if (item.isEmpty()) {
                    continue;
                }

                QList<QStandardItem*> foundItems;
                for (int j = 0; j < parent->rowCount(); ++j) {
                    QStandardItem* child = parent->child(j);
                    if (child->text() == item) {
                        foundItems.append(child);
                    }
                }

                if (!foundItems.isEmpty()) {
                    parent = foundItems.first();
                } else {
                    QStandardItem* newItem = new QStandardItem(item);
                    parent->appendRow(newItem);
                    parent = newItem;
                }
            }
        }
    }

    zip_close(zf);

}
