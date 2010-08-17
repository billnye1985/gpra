#include "MainWidget.h"
#include "MainWidgetSettingsSaver.h"
#include <QtCore/QEvent>
#include <QtCore/QSettings>
#include <QtGui/QLineEdit>

// ----------------------------------------------------------------------
// -public

MainWidgetSettingsSaver::MainWidgetSettingsSaver(MainWidget *mainWidgetArg)
	: QObject(mainWidgetArg)
	, m_mainWidget(mainWidgetArg)
{
	setup();
}

bool
MainWidgetSettingsSaver::eventFilter(QObject *recipient, QEvent *e)
{
	if (e->type() == QEvent::Close) {
		saveSettings();
	}
	return QObject::eventFilter(recipient, e);
}

// ----------------------------------------------------------------------
// -private

void
MainWidgetSettingsSaver::setup()
{
	mainWidget()->installEventFilter(this);
	loadSettings();
}

void
MainWidgetSettingsSaver::loadSettings()
{
	QSettings settings;

	mainWidget()->restoreGeometry(settings.value("mainWidget.geometry").toByteArray());
	mainWidget()->knownSaltLineEdit()->setText(settings.value("mainWidget.knownSaltLineEdit.text").toString());
	mainWidget()->knownHashLineEdit()->setText(settings.value("mainWidget.knownHashLineEdit.text").toString());
	mainWidget()->passwordLineEdit()->setText(settings.value("mainWidget.passwordLineEdit.text").toString());

	mainWidget()->passwordLineEdit()->selectAll();
	mainWidget()->passwordLineEdit()->setFocus();
}

void
MainWidgetSettingsSaver::saveSettings()
{
	QSettings settings;

	settings.setValue("mainWidget.geometry", mainWidget()->saveGeometry());
	settings.setValue("mainWidget.knownSaltLineEdit.text", mainWidget()->knownSaltLineEdit()->text());
	settings.setValue("mainWidget.knownHashLineEdit.text", mainWidget()->knownHashLineEdit()->text());
	settings.setValue("mainWidget.passwordLineEdit.text", mainWidget()->passwordLineEdit()->text());
}
