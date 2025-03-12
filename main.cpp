#include "widget.h"
#include <QApplication>
#include <QObject>
#include <QFontDatabase>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*set the font defined by ourselevs*/
    int fontId = QFontDatabase::addApplicationFont("/root/fonts/Ubuntu-R.ttf");
    if (fontId == -1) {
        qWarning("Failed to load font!");
    }
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if (!fontFamilies.isEmpty())
    {
            QString fontFamily = fontFamilies.at(0);
            QFont font(fontFamily);
            a.setFont(font);
    } 

    Widget w; //widget
    w.show();
    return a.exec();
}
