#pragma once

#include <QOpenGLWidget>
#include "Camera.h"
#include <chrono>
#include <QMatrix4x4>
#include <QOpenGLShader>
#include <qopenglshaderprogram.h>
#include <qopenglvertexarrayobject.h>
#include "Renderable.h"
#include "ui_QtGLWidget.h"
#include "qopengldebug.h"
#include <QtOpenGLExtensions\qopenglextensions.h>

enum mode { PAN, ZOOM, ROTATE };

class QtGLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	QtGLWidget(QWidget *parent = Q_NULLPTR);
	~QtGLWidget();

	bool collisionsDetected(Renderable& obj);
	void createVAO(GeoModel3D model);
	QVector<Renderable> getObjects();
	void initShaders();
	bool isMouseDragging(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent * event);
	QPoint normalizedDeviceCoordinatesToViewport(QVector3D ndc, int screen_width, int screen_height);
	void renderBoundingBox(Renderable& object);
	void renderModel(GeoModel3D model);
	QVector<Renderable> selectedObjects();
	void setObjects(QVector<Renderable> objs);
	void showContextMenu(const QPoint &pos);
	QVector3D viewportToNormalizedDeviceCoordinates(int xPos, int yPos, int screen_width, int screen_height);
	void wheelEvent(QWheelEvent *event);

	public slots:
	void onRotateModeSelected();
	void onPanModeSelected();
	void onZoomModeSelected();
	void reset();
	void updateFrame();

private:
	QPoint dragStartPosition;
	Camera glCamera;
	QPoint lastDragOffset;
	std::chrono::steady_clock::time_point last_time_step;
	QOpenGLDebugLogger * logger;
	QMatrix4x4 m_projection;
	QOpenGLShaderProgram m_shaderProgram;
	std::map<GLuint, QOpenGLVertexArrayObject*> object_vao_map;
	QVector<Renderable> objects;
	Ui::QtGLWidget ui;
	mode viewMode;

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
};
