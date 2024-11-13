#ifndef NoFile_H
#define NoFile_H

#include <QErrorMessage>

class NoFile : public QErrorMessage {
public:
    NoFile() {
        showMessage("ZIP-файл не открыт!");
    }
};
#endif // NoFile_H
