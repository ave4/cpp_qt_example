#include "ExtractDialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QDir>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

ExtractDialog::ExtractDialog(const QString& archivePath, QWidget* parent)
    : QDialog(parent), archivePath(archivePath) {
    setAutoFillBackground(true);
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(new QLabel("Путь распаковки"), 0, 0);
    pathExt = new QLineEdit(QDir::currentPath());
    layout->addWidget(pathExt, 1, 0);
    QPushButton* dirButton = new QPushButton("Диалог");
    layout->addWidget(dirButton, 1, 1);
    connect(dirButton, &QPushButton::clicked, this, &ExtractDialog::fileDia);
    QPushButton* extButton = new QPushButton("Извлечь файлы");
    layout->addWidget(extButton, 2, 0);
    connect(extButton, &QPushButton::clicked, this, &ExtractDialog::extractZip);
}

void ExtractDialog::fileDia() {
    QString dirPath = QFileDialog::getExistingDirectory(this, "Путь распаковки архива", QDir::currentPath(), QFileDialog::ShowDirsOnly);
    pathExt->setText(dirPath);
}

void ExtractDialog::extractZip() {
    if (!archivePath.isEmpty() && !pathExt->text().isEmpty()) {
        // Логика распаковки архива

        QMessageBox::information(this, "Успех", "Файлы успешно извлечены!");
    }
}
