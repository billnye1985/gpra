#include "MainWindow.h"
#include "MainWindowSettingsSaver.h"
#include <QtGui/QApplication>

int
main(int argc, char **argv)
{
	QApplication app(argc, argv);
#include "go_settings.inc"

	MainWindow mainWindow;
	MainWindowSettingsSaver mainWindowSettingsSaver(&mainWindow);
	mainWindow.show();

	return app.exec();
}
