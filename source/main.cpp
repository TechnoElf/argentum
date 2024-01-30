/*
 * Created by janis on 2024-01-25
 */

#include <QApplication>
#include <QSettings>

#include "ui/window.h"

int main(int argc, char* argv[]) {
    std::srand(std::time(nullptr));

    QApplication app(argc, argv);
    QApplication::setApplicationName("argentum");
    QApplication::setApplicationDisplayName("Argentum");
    QApplication::setOrganizationName("fsei");
    QApplication::setOrganizationDomain("fs.ei.tum.de");

    QSettings settings(QApplication::organizationName(), QApplication::applicationName());
    settings.sync();

    ag::Window window(settings);
    window.setWindowTitle("Argentum Trade Guild");
    window.show();

    return QApplication::exec();
}