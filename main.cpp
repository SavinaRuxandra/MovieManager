#include "Tiffgui.h"
#include <QApplication>
#include <iostream>

#include <QJsonArray>
#include <QJsonObject>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MovieRepository* repository= new MovieRepository();
    Validator valid;
    Service* service = new Service(repository, valid);

    TiffGUI gui(service);
    gui.show();

    return app.exec();
}
