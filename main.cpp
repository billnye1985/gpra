#include "MainWidget.h"
#include "MainWidgetSettingsSaver.h"
#include <QtGui/QApplication>

int
main(int argc, char **argv)
{
	QApplication app(argc, argv);
#include "go_settings.inc"

	MainWidget mainWidget;
	MainWidgetSettingsSaver mainWidgetSettingsSaver(&mainWidget);
	mainWidget.show();

	return app.exec();
}
