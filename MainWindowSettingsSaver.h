#ifndef MAINWINDOWSETTINGSSAVER_H
#define MAINWINDOWSETTINGSSAVER_H

#include <QtCore/QObject>

class MainWindow;

// ----------------------------------------------------------------------
// -MainWindowSettingsSaver

class MainWindowSettingsSaver : public QObject {
	Q_OBJECT
public:
	MainWindowSettingsSaver(MainWindow *mainWindow);

	/* virtual */ bool eventFilter(QObject *recipient, QEvent *e);

private:
	void setup();

	void saveSettings();
	void loadSettings();

	MainWindow *m_mainWindow;
	MainWindow * mainWindow() const { Q_ASSERT(m_mainWindow); return m_mainWindow; }
};

#endif // #ifndef MAINWINDOWSETTINGSSAVER_H
