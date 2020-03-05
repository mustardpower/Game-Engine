#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtPhysicsEngine.h"

class QtPhysicsEngine : public QMainWindow
{
	Q_OBJECT

public:
	static QString getApplicationDirectory();

	QVector<Renderable> getObjects();

	int loadFromXML(QString fileName);
	int saveToXML(QString file_name);

	int loadFromObj(QString fileName);

    QtPhysicsEngine(QWidget *parent = Q_NULLPTR);

	public slots:
	void loadXML();
	void saveXML();
	void loadObj();

private:
	static QString applicationDirectory;

    Ui::QtPhysicsEngineClass ui;
};
