#ifndef MAINWIDGETSETTINGSSAVER_H
#define MAINWIDGETSETTINGSSAVER_H

#include <QtCore/QObject>

class MainWidget;

// ----------------------------------------------------------------------
// -MainWidgetSettingsSaver

class MainWidgetSettingsSaver : public QObject {
	Q_OBJECT
public:
	MainWidgetSettingsSaver(MainWidget *mainWidget);

	/* virtual */ bool eventFilter(QObject *recipient, QEvent *e);

private:
	void setup();

	void saveSettings();
	void loadSettings();

	MainWidget *m_mainWidget;
	MainWidget * mainWidget() const { Q_ASSERT(m_mainWidget); return m_mainWidget; }
};

#endif // #ifndef MAINWIDGETSETTINGSSAVER_H
