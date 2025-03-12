#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include "readEEPROM.h"


QString readEEPROM(const QString &eepromPath) {
    QFile file(eepromPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open EEPROM file!";
        return QString();
    }

    QTextStream in(&file);
    QString data = in.readAll(); //get all information from EEPROM
    file.close();
    return data;
}
