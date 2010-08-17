#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui/QWidget>

class QLineEdit;

// ----------------------------------------------------------------------
// -MainWidget

class MainWidget : public QWidget {
	Q_OBJECT
public:
	MainWidget(QWidget *parent = 0);

	QLineEdit * knownSaltLineEdit() const { Q_ASSERT(m_knownSaltLineEdit); return m_knownSaltLineEdit; }
	QLineEdit * knownHashLineEdit() const { Q_ASSERT(m_knownHashLineEdit); return m_knownHashLineEdit; }
	QLineEdit * passwordLineEdit() const { Q_ASSERT(m_passwordLineEdit); return m_passwordLineEdit; }
	QLineEdit * hashLineEdit() const { Q_ASSERT(m_hashLineEdit); return m_hashLineEdit; }

private slots:
	void syncHashLineEdit();

private:
	void setup();
	void setupWidgets();

	QLineEdit *m_knownSaltLineEdit;
	QLineEdit *m_knownHashLineEdit;
	QLineEdit *m_passwordLineEdit;
	QLineEdit *m_hashLineEdit;
};

#endif // #ifndef MAINWIDGET_H
