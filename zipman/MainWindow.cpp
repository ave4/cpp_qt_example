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
}

void MainWindow::updateTree() {
    // Логика обновления дерева файлов
}
