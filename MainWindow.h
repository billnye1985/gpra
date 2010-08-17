#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class QLineEdit;

// ----------------------------------------------------------------------
// -MainWindow

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);

	QLineEdit * knownSaltLineEdit() const { Q_ASSERT(m_knownSaltLineEdit); return m_knownSaltLineEdit; }
	QLineEdit * knownHashLineEdit() const { Q_ASSERT(m_knownHashLineEdit); return m_knownHashLineEdit; }
	QLineEdit * passwordLineEdit() const { Q_ASSERT(m_passwordLineEdit); return m_passwordLineEdit; }
	QLineEdit * hashLineEdit() const { Q_ASSERT(m_hashLineEdit); return m_hashLineEdit; }

	QString dbFileName() const;
	void setDbFileName(const QString &val) { m_dbFileName = val; }

private slots:
	void syncHashLineEdit();
	void readKnowns();
	void about();

private:
	void setup();
	void setupActions();
	void setupMenus();
	void setupWidgets();
	void setupCentralWidget();

	QLineEdit *m_knownSaltLineEdit;
	QLineEdit *m_knownHashLineEdit;
	QLineEdit *m_passwordLineEdit;
	QLineEdit *m_hashLineEdit;

	QString m_dbFileName;

#define A(NAME) \
	QAction *m_##NAME##Action; \
	QAction * NAME##Action() const { Q_ASSERT(m_##NAME##Action); return m_##NAME##Action; }

	A(readKnowns)
	A(quit)
	A(aboutQt)
	A(about)
#undef A
};

#endif // #ifndef MAINWINDOW_H
