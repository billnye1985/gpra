#include "MainWindow.h"
#include "MainWindowSettingsSaver.h"
#include <QtCore/QEvent>
#include <QtCore/QSettings>
#include <QtGui/QLineEdit>

// ----------------------------------------------------------------------
// -public

MainWindowSettingsSaver::MainWindowSettingsSaver(MainWindow *mainWindowArg)
	: QObject(mainWindowArg)
	, m_mainWindow(mainWindowArg)
{
	setup();
}

bool
MainWindowSettingsSaver::eventFilter(QObject *recipient, QEvent *e)
{
	if (e->type() == QEvent::Close) {
		saveSettings();
	}
	return QObject::eventFilter(recipient, e);
}

// ----------------------------------------------------------------------
// -private

void
MainWindowSettingsSaver::setup()
{
	mainWindow()->installEventFilter(this);
	loadSettings();
}

void
MainWindowSettingsSaver::loadSettings()
{
	QSettings settings;

	mainWindow()->restoreGeometry(settings.value("mainWindow.geometry").toByteArray());
	mainWindow()->knownSaltLineEdit()->setText(settings.value("mainWindow.knownSaltLineEdit.text").toString());
	mainWindow()->knownHashLineEdit()->setText(settings.value("mainWindow.knownHashLineEdit.text").toString());
	mainWindow()->passwordLineEdit()->setText(settings.value("mainWindow.passwordLineEdit.text").toString());

	mainWindow()->passwordLineEdit()->selectAll();
	mainWindow()->passwordLineEdit()->setFocus();
}

void
MainWindowSettingsSaver::saveSettings()
{
	QSettings settings;

	settings.setValue("mainWindow.geometry", mainWindow()->saveGeometry());
	settings.setValue("mainWindow.knownSaltLineEdit.text", mainWindow()->knownSaltLineEdit()->text());
	settings.setValue("mainWindow.knownHashLineEdit.text", mainWindow()->knownHashLineEdit()->text());
	settings.setValue("mainWindow.passwordLineEdit.text", mainWindow()->passwordLineEdit()->text());
}
