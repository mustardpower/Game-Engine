#include "QtGLWidget.h"
#include "QDrag"
#include "QMenu"
#include "QMessagebox"
#include "QMimeData"
#include "QMouseEvent"
#include <qopenglfunctions.h>
#include <QOpenGLTexture>
#include <QTimer>
#include "qopenglvertexarrayobject.h"
#include "qopenglbuffer.h"

#include <iostream>

QtGLWidget::QtGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	ui.setupUi(this);
	viewMode = ROTATE;

	QTimer *timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
	timer->start(10);
}

QtGLWidget::~QtGLWidget()
{
}

void QtGLWidget::initializeGL()
{
	QOpenGLContext *context = QOpenGLContext::currentContext();
	context->create();
	makeCurrent();

	// Set up the rendering context, load shaders and other resources, etc.:
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	f->initializeOpenGLFunctions();
	f->glClearColor(0, 0.5, 0.5, 1);

	initShaders();

	// Enable depth buffer
	f->glEnable(GL_DEPTH_TEST);

	// Enable back face culling
	f->glEnable(GL_CULL_FACE);
}

bool QtGLWidget::collisionsDetected(Renderable &obj)
{
	// TO DO: COLLISION DETECTION!
	for (QVector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
	{
		if (*object != obj)
		{
			if (object->intersects(obj))
			{
				return true;
			}
		}
	}

	return false;
}

void QtGLWidget::createVAO(GeoModel3D model)
{
	QVector<GLModel3DData> modelData = model.retrieveMeshes();

	for (QVector<GLModel3DData>::iterator mesh = modelData.begin(); mesh != modelData.end(); mesh++)
	{
		QOpenGLVertexArrayObject* m_vao = new QOpenGLVertexArrayObject(this);
		m_vao->create(); // Create our Vertex Array Object
		m_vao->bind(); // Bind our Vertex Array Object so we can use it

		GLuint mesh_id = mesh->getMeshID();
		tinyobj::mesh_t mesh_data = mesh->getMeshData();
		std::pair<GLuint, QOpenGLVertexArrayObject*> mapping(mesh_id, m_vao);
		object_vao_map.insert(mapping);

		QOpenGLBuffer m_positionBuffer;
		m_positionBuffer.create();
		m_positionBuffer.bind();
		m_positionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
		m_positionBuffer.allocate(&mesh_data.positions[0],
			mesh_data.positions.size() * sizeof(float));
		m_shaderProgram.enableAttributeArray("position");
		m_shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3);

		QOpenGLBuffer m_texCoordBuffer;
		m_texCoordBuffer.create();
		m_texCoordBuffer.bind();
		m_texCoordBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
		m_texCoordBuffer.allocate(&mesh_data.texcoords[0],
			mesh_data.texcoords.size() * sizeof(float));
		m_shaderProgram.enableAttributeArray("TexCoord");
		m_shaderProgram.setAttributeBuffer("TexCoord", GL_FLOAT, 0, 2);

		QOpenGLBuffer m_IndexBuffer(QOpenGLBuffer::IndexBuffer);
		m_IndexBuffer.create();
		m_IndexBuffer.bind();
		m_IndexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
		m_IndexBuffer.allocate(&mesh_data.indices[0],
			mesh_data.indices.size() * sizeof(GLuint));

		m_vao->release();
	}
}

Renderable* QtGLWidget::getCollidingObject(Renderable &object)
{
	for (QVector<Renderable>::iterator obj = objects.begin(); obj != objects.end(); obj++)
	{
		if (object != *obj)
		{
			if (object.intersects(*obj))
			{
				return obj;
			}
		}
	}

	return NULL;
}

QVector3D QtGLWidget::getCollisionNormal(Renderable objectA, Renderable objectB)
{
	AABB boxA = objectA.getBoundingBox();
	AABB boxB = objectB.getBoundingBox();
	
	QVector3D overlap = boxA.overlap(boxB);
	float ax = fabs(overlap.x());
	float ay = fabs(overlap.y());
	float az = fabs(overlap.z());

	float sx = boxA.getCenter().x() < boxB.getCenter().x() ? -1.0f : 1.0f;
	float sy = boxA.getCenter().y() < boxB.getCenter().y() ? -1.0f : 1.0f;
	float sz = boxA.getCenter().z() < boxB.getCenter().z() ? -1.0f : 1.0f;

	if (ax <= ay && ax <= az)
		return QVector3D(sx, 0.0f, 0.0f);
	else if (ay <= az)
		return QVector3D(0.0f, sy, 0.0f);
	else
		return QVector3D(0.0f, 0.0f, sz);
}

QVector<Renderable> QtGLWidget::getObjects()
{
	return objects;
}

void QtGLWidget::initShaders()
{
	// Compile vertex shader
	if (!m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "vert_shader.vs"))
		close();

	// Compile fragment shader
	if (!m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "frag_shader.fs"))
		close();

	// Link shader pipeline
	if (!m_shaderProgram.link())
		close();

	// Bind shader pipeline for use
	if (!m_shaderProgram.bind())
		close();
}

bool QtGLWidget::isMouseDragging(QMouseEvent *event)
{
	return ((event->pos() - dragStartPosition).manhattanLength()
		> QApplication::startDragDistance());
}

void QtGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (!(event->buttons() &  (Qt::LeftButton | Qt::MiddleButton)))
		return;
	if (!isMouseDragging(event))
		return;

	float deltaX = ((float)event->pos().x() - (float)lastDragOffset.x()) / (float) width();
	float deltaY = ((float)event->pos().y() - (float)lastDragOffset.y()) / (float) height();
	QVector<Renderable> selected = selectedObjects();

	if (event->buttons() & Qt::MiddleButton)
	{
		glCamera.onPan(deltaX, deltaY);
	}
	else if (event->buttons() & Qt::LeftButton)
	{
		if (selected.isEmpty())
		{
			switch (viewMode)
			{
			case ROTATE:
			{
				glCamera.onRotate(deltaX, deltaY);
			}
			break;
			case PAN:
			{
				glCamera.onPan(deltaX, deltaY);
			}
			break;
			case ZOOM:
			{
				glCamera.onZoom(deltaX, deltaY);
			}
			break;
			}
		}
	}

	lastDragOffset = event->pos();
}


void QtGLWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragStartPosition = event->pos();
		lastDragOffset = event->pos();
	}

	if (event->button() == Qt::MiddleButton)
	{
		dragStartPosition = event->pos();
		lastDragOffset = event->pos();
	}

	if (event->button() == Qt::RightButton)
		showContextMenu(event->pos());
}

//Click event = MousePress->MouseRelease	
void QtGLWidget::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (isMouseDragging(event))
			return;

		for (QVector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
		{
			object->getBoundingBox();
			int x = event->pos().x();
			int y = event->pos().y();
			object->setSelectionIfRayIntersects(pointOnNearPlane(x, y), rayDirectionBetweenNearAndFarPlane(x, y));
		}
	}
};

QPoint QtGLWidget::normalizedDeviceCoordinatesToViewport(QVector3D ndc, int screen_width, int screen_height)
{
	float x = ((ndc.x() + 1) * screen_width) / 2;
	float y = ((1.0f - ndc.y()) * screen_height) / 2;
	return QPoint(x, y);
}

void QtGLWidget::onRotateModeSelected()
{
	viewMode = ROTATE;
}

void QtGLWidget::onPanModeSelected()
{
	viewMode = PAN;
}

void QtGLWidget::onZoomModeSelected()
{
	viewMode = ZOOM;
}

void QtGLWidget::paintGL()
{
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shaderProgram.bind();
	for (QVector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
	{
		m_shaderProgram.setUniformValue("mvp_matrix", glCamera.getMVPMatrix() * object->getModelMatrix());
		renderModel(object->getModel());
		if(object->isSelected())
		{
			renderBoundingBox(*object);
		}
	}
}

QVector3D QtGLWidget::pointOnNearPlane(const int x, const int y)
{
	QRect viewport(0.0f, 0.0f, width(), height());
	return glCamera.pointOnNearPlane(x, height() - y, viewport);
}

QVector3D QtGLWidget::pointOnFarPlane(const int x, const int y)
{
	QRect viewport(0.0f, 0.0f, width(), height());
	return glCamera.pointOnFarPlane(x, height() - y, viewport);
}

QVector3D QtGLWidget::rayDirectionBetweenNearAndFarPlane(const int x, const int y)
{
	return (pointOnFarPlane(x,y) - pointOnNearPlane(x,y)).normalized();
}

void QtGLWidget::resizeGL(int w, int h)
{
	// Update projection matrix and other size related settings:
	glCamera.resizeViewport(w, h);
}

void QtGLWidget::renderBoundingBox(Renderable& object)
{
	QOpenGLVertexArrayObject m_vao;

	m_shaderProgram.setUniformValue("mvp_matrix", glCamera.getMVPMatrix()); // bounding box stored in global coordinates so no need for object transform
	m_vao.create(); 
	m_vao.bind(); 

	std::vector<float> vertices = object.getBoundingBox().getVertices();
	std::vector<unsigned int> indices = object.getBoundingBox().getEdgeIndices();

	QOpenGLBuffer m_positionBuffer;
	m_positionBuffer.create();
	m_positionBuffer.bind();
	m_positionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_positionBuffer.allocate(&vertices[0],
		vertices.size() * sizeof(float));
	m_shaderProgram.enableAttributeArray("position");
	m_shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3);

	QOpenGLBuffer m_IndexBuffer(QOpenGLBuffer::IndexBuffer);
	m_IndexBuffer.create();
	m_IndexBuffer.bind();
	m_IndexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_IndexBuffer.allocate(&indices[0],
		indices.size() * sizeof(GLuint));

	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	f->glDrawElements(GL_LINES, vertices.size() * 3, GL_UNSIGNED_INT, 0);
}

void QtGLWidget::renderModel(GeoModel3D model)
{
	QOpenGLVertexArrayObject* vaoID;
	QVector<GLModel3DData> modelData = model.retrieveMeshes();
	QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();

	for (QVector<GLModel3DData>::iterator m = modelData.begin(); m != modelData.end(); m++)
	{
		if (object_vao_map.find(m->getMeshID()) == object_vao_map.end())
		{
			createVAO(model); // if errors here ensure to create VAOs
		}

		vaoID = object_vao_map.at(m->getMeshID());
		vaoID->bind();

		//QOpenGLTexture texture(QImage(m->texture).mirrored());
		QString texture_str = m->getTexture();

		if (texture_str.isNull() || texture_str.isEmpty())
		{
			std::cout << "Texture could not bind" << std::endl;
		}
		else
		{
			QImage texture_image(texture_str);
			if (texture_image.isNull())
			{
				std::cout << "Image is not loaded" << std::endl;
			}
			else
			{
				QOpenGLTexture texture(texture_image);
				texture.bind();

				tinyobj::mesh_t mesh = m->getMeshData();
				f->glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);

				if (texture.isBound())
				{
					texture.release();
				}
			}
		}
	}
}

void QtGLWidget::resolveCollision(Renderable &object, Renderable & collidingObj)
{
	// calculate contact point on colliding bodies
	// calculate offset between contact points and centre of mass
	// calculate the contact normal (assumed to point away from body 1 and towards body 2)
	// calculate vr (the pre-collision relative velocity)
	PhysicsHandler ph;
	QVector3D v1 = object.getVelocity();
	QVector3D v2 = collidingObj.getVelocity();
	QVector3D w1 = object.getAngularVelocity();
	QVector3D w2 = collidingObj.getAngularVelocity();
	QVector3D r1(-1, 0, 0);
	QVector3D r2(1, 0, 0);
	float m1 = object.getMass();
	float m2 = collidingObj.getMass();
	float e = 1.0;
	QVector3D n = getCollisionNormal(object, collidingObj); 
	QMatrix4x4 i1 = object.getInertia();
	QMatrix4x4 i2 = collidingObj.getInertia();
	QVector3D vr = ph.calculateRelativeVelocity(v1, v2, w1, w2, r1, r2);
	float impulseMagnitude = ph.calculateReactionForce(r1, r2, i1, i2, m1, m2, e, n, vr);
	QVector3D newVelocity1 = ph.calculateLinearVelocity(v1, -impulseMagnitude, m1, n);
	QVector3D newVelocity2 = ph.calculateLinearVelocity(v2, impulseMagnitude, m2, n);
	object.setVelocity(newVelocity1);
	collidingObj.setVelocity(newVelocity2);
}

QVector<Renderable> QtGLWidget::selectedObjects()
{
	QVector<Renderable> selectedObjects;
	for (QVector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
	{
		if (object->isSelected())
		{
			selectedObjects.push_back(*object);
		}
	}
	return selectedObjects;
}

void QtGLWidget::reset()
{
	objects.clear();
}

void QtGLWidget::setObjects(QVector<Renderable> objs)
{
	objects = objs;
}

void QtGLWidget::showContextMenu(const QPoint &pos)
{
	QMenu contextMenu("Context menu", this);

	QMenu subMenu("View mode", this);
	QAction rotateAction("Rotate", this);
	QAction zoomAction("Zoom", this);
	QAction panAction("Pan", this);

	connect(&rotateAction, SIGNAL(triggered()), this, SLOT(onRotateModeSelected()));
	connect(&zoomAction, SIGNAL(triggered()), this, SLOT(onZoomModeSelected()));
	connect(&panAction, SIGNAL(triggered()), this, SLOT(onPanModeSelected()));

	subMenu.addAction(&rotateAction);
	subMenu.addAction(&zoomAction);
	subMenu.addAction(&panAction);

	contextMenu.addMenu(&subMenu);
	contextMenu.exec(mapToGlobal(pos));
}

QVector3D QtGLWidget::viewportToNormalizedDeviceCoordinates(int xPos, int yPos, int screen_width, int screen_height)
{
	float x = (2.0f * xPos) / screen_width - 1.0f;
	float y = 1.0f - (2.0f * yPos) / screen_height;
	float z = 1.0f;
	return QVector3D(x, y, z);
}

void QtGLWidget::wheelEvent(QWheelEvent *event)
{
	QRect viewport(0.0f, 0.0f, width(), height());
	QVector3D ray_direction = rayDirectionBetweenNearAndFarPlane(event->x(), event->y());

	if (event->delta() > 0)
	{
		glCamera.translate(ray_direction);
	}
	if (event->delta() < 0)
	{
		glCamera.translate(-ray_direction);
	}
}

void QtGLWidget::updateFrame()
{
	auto current_time_step = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> time_step(current_time_step - last_time_step);
	float dt = time_step.count();
	Renderable* collidingObj;
	for (QVector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
	{
		object->storeFrame();				// store the position, velocity, inertia etc
		object->updateFrame(dt);			// update the position based on the velocity etc
		if (collisionsDetected(*object))
		{
			collidingObj = getCollidingObject(*object);
			object->previousFrame();		// if the new position is in collision with another object
											// revert to previous position and use more accurate handling
			if (collidingObj)
			{
				resolveCollision(*object, *collidingObj);
			}
		}
	}

	last_time_step = current_time_step;

	update();
}
