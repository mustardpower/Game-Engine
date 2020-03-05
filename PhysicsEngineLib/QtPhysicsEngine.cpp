#include "QtPhysicsEngine.h"
#include <QDir>
#include <QFileDialog>
#include <QOpenGLContext>
#include <QMessageBox>
#include "tinyxml2\tinyxml2.h"

#include <filesystem>

QString QtPhysicsEngine::applicationDirectory = QtPhysicsEngine::getApplicationDirectory();

QtPhysicsEngine::QtPhysicsEngine(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.actionNew, SIGNAL(triggered()), ui.openGLWidget, SLOT(reset()));
	QObject::connect(ui.actionLoadXML, SIGNAL(triggered()), this, SLOT(loadXML()));
	QObject::connect(ui.actionSaveXML, SIGNAL(triggered()), this, SLOT(saveXML()));
	QObject::connect(ui.actionLoad_Obj, SIGNAL(triggered()), this, SLOT(loadObj()));
	QObject::connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

QString QtPhysicsEngine::getApplicationDirectory()
{
	return QDir::currentPath();
}

QVector<Renderable> QtPhysicsEngine::getObjects()
{
	return ui.openGLWidget->getObjects();
}

int QtPhysicsEngine::loadFromObj(QString fileName)
{
	Renderable scene_object;
	std::string file = fileName.toUtf8().constData();
	QVector<Renderable> objects;

	int error = 0;
	Renderable anObject;
	GeoModel3D model;

	if (!std::filesystem::exists(file))
	{
		return -1;
	}

	model.loadFromFile(fileName);
	anObject.setModel(model);
	objects.push_back(anObject);

	if (!error)
	{
		ui.openGLWidget->setObjects(objects);
	}

	return error;
}

int QtPhysicsEngine::loadFromXML(QString fileName)
{
	Renderable scene_object;
	tinyxml2::XMLDocument aDoc;
	std::string file = fileName.toUtf8().constData();
	tinyxml2::XMLError error = aDoc.LoadFile(file.c_str());
	tinyxml2::XMLNode * pRoot = aDoc.FirstChild();
	QVector<Renderable> objects;

	if (pRoot != nullptr)
	{
		tinyxml2::XMLNode * pRenderable = pRoot->NextSibling()->FirstChild();
		while (pRenderable != nullptr)
		{
			error = Renderable::deserialize(pRenderable, scene_object);
			if (error == tinyxml2::XML_SUCCESS)
			{
				objects.push_back(scene_object);
			}
			else
			{
				qDebug() << "Could not deserialize Renderable object - error code: " << error << "\n";
			}
			pRenderable = pRenderable->NextSibling();
		}
	}

	if (!error)
	{
		ui.openGLWidget->setObjects(objects);
	}

	return error;
}

void QtPhysicsEngine::loadObj()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		"Open File",
		"C://",
		"Obj Files (*.obj);;All Files (*.*)");

	if (!fileName.isEmpty())
	{
		if (loadFromObj(fileName))
		{
			QMessageBox::critical(this, "Could not load file", "Loading file failed");
		}
	}
}

void QtPhysicsEngine::loadXML()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		"Open File",
		"C://",
		"XML Files (*.xml);;Text Files(*.txt);;All Files (*.*)");

	if (!fileName.isEmpty())
	{
		if (loadFromXML(fileName))
		{
			QMessageBox::critical(this, "Could not load file", "Loading file failed");
		}
	}
}

int QtPhysicsEngine::saveToXML(QString fileName)
{
	std::string file_name = fileName.toUtf8().constData();

	tinyxml2::XMLDocument aDoc;
	tinyxml2::XMLDeclaration* decl = aDoc.NewDeclaration();
	aDoc.LinkEndChild(decl);

	tinyxml2::XMLNode* root = aDoc.NewElement("root");
	aDoc.LinkEndChild(root);

	QVector<Renderable> objects = ui.openGLWidget->getObjects();

	// this may need modifying to deal with nested elements
	for (QVector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
	{
		object->serialize(aDoc, root);
	}

	tinyxml2::XMLError error = aDoc.SaveFile(file_name.c_str());
	return error;
}

void QtPhysicsEngine::saveXML()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save File", "C:\\", "XML Files (*.xml);;Text Files(*.txt)");
	if (!fileName.isEmpty())
	{
		int error = saveToXML(fileName);
		if (error)
		{
			QMessageBox::critical(this, "Could not save as XML", "Error saving XML");
		}
	}
}
