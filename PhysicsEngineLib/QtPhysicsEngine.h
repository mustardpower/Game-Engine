#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtPhysicsEngine.h"

class QtPhysicsEngine : public QMainWindow
{
	Q_OBJECT

public:
	static QString getApplicationDirectory();
	static QString getModelDirectory();
	static QString getTexturesDirectory();

	QVector<Renderable> getObjects();
	int loadFromFile(QString fileName);
	int saveToFile(QString file_name);

    QtPhysicsEngine(QWidget *parent = Q_NULLPTR);

	public slots:
	void loadXML();
	void saveXML();

private:
	static QString applicationDirectory;
	static QString modelDirectory;
	static QString texturesDirectory;

    Ui::QtPhysicsEngineClass ui;
};
