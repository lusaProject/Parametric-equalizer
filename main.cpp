#include <QApplication>
#include <QAudioDecoder>
#include <QMediaContent>
#include <QAudioOutput>
#include <QUrl>
#include <QBuffer>
#include <QDesktopWidget>

#include "AudioPlayer.h"
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget app;
    QDesktopWidget *desktop = QApplication::desktop();
    app.move((desktop->width() - app.width()) / 2, (desktop->height() - app.height()) / 2);
    app.show();
    return a.exec();
}
