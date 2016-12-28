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

bool QtGLWidget::collisionsDetected(const Renderable &obj)
{
	// TO DO: COLLISION DETECTION!
	return false;
}

void QtGLWidget::createVAO(GeoModel3D model)
{
	QOpenGLVertexArrayObject* m_vao;
	QVector<GLModel3DData> modelData = model.retrieveMeshes();
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

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

		QRect viewport(0.0f, 0.0f, width(), height());

		// calculate point on near and far plane
		QVector3D worldPosNear = glCamera.pointOnNearPlane(event->pos().x(), height() - event->pos().y(), viewport);
		QVector3D worldPosFar = glCamera.pointOnFarPlane(event->pos().x(), height() - event->pos().y(), viewport);

		QVector3D ray_direction = (worldPosFar - worldPosNear).normalized();
		for (QVector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
		{
			bool intersects = object->intersects(worldPosNear, ray_direction);
			object->setSelection(intersects);
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

void QtGLWidget::resizeGL(int w, int h)
{
	// Update projection matrix and other size related settings:
	glCamera.resizeViewport(w, h);
}

void QtGLWidget::paintGL()
{
	// Draw the scene:

	QMatrix4x4 object_model_matrix;
	QMatrix4x4 mvp_matrix;
	QMatrix4x4 camera_mvp_matrix = glCamera.getMVPMatrix();
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shaderProgram.bind();
	for (QVector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
	{
		object_model_matrix = object->getModelMatrix();
		mvp_matrix = camera_mvp_matrix * object_model_matrix;
		m_shaderProgram.setUniformValue("mvp_matrix", mvp_matrix);

		renderModel(object->getModel());
		if (object->isSelected())
		{
			renderBoundingBox(object->getBoundingBox());
		}
	}
}

void QtGLWidget::renderBoundingBox(AABB boundingBox)
{
	QOpenGLVertexArrayObject m_vao;
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	QVector3D min = boundingBox.getVecMin();
	QVector3D max = boundingBox.getVecMax();
	const int NUM_OF_VERTICES = 8;

	m_vao.create(); // Create our Vertex Array Object
	m_vao.bind(); // Bind our Vertex Array Object so we can use it

	std::vector<float> vertices = {
		max.x(),  max.y(),  max.z(), // Vertex 0 (X, Y, Z)
		max.x(),  max.y(),  min.z(), // Vertex 1 (X, Y, Z)
		max.x(),	min.y(),  min.z(), // Vertex 2 (X, Y, Z)
		max.x(),	min.y(),  max.z(), // Vertex 3 (X, Y, Z)
		min.x(),  max.y(), max.z(), // Vertex 4 (X, Y, Z)
		min.x(),  max.y(), min.z(), // Vertex 5 (X, Y, Z)
		min.x(),	min.y(), min.z(), // Vertex 6 (X, Y, Z)
		min.x(),	min.y(), max.z()  // Vertex 7 (X, Y, Z)
	};

	std::vector<unsigned int> indices = {
		0,1,  1,5,  5,4,  4,0,    // edges of the top face
		7,3,  3,2,  2,6,  6,7,    // edges of the bottom face
		1,2,  0,3,  4,7,  5,6	 // edges connecting top face to bottom face
	};

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

	f->glDrawElements(GL_LINES, NUM_OF_VERTICES * 3, GL_UNSIGNED_INT, 0);
}

void QtGLWidget::renderModel(GeoModel3D model)
{
	QOpenGLVertexArrayObject* vaoID;
	GLuint sampler_loc = 4;
	QVector<GLModel3DData> modelData = model.retrieveMeshes();
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

	for (QVector<GLModel3DData>::iterator m = modelData.begin(); m != modelData.end(); m++)
	{
		if (object_vao_map.find(m->getMeshID()) == object_vao_map.end())
		{
			createVAO(model); // if errors here ensure to create VAOs
		}

		vaoID = object_vao_map.at(m->getMeshID());
		vaoID->bind();

		//QOpenGLTexture texture(QImage(m->texture).mirrored());
		QOpenGLTexture texture(QImage(m->texture));
		texture.bind();

		tinyobj::mesh_t mesh = m->getMeshData();
		f->glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
	}
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

	// calculate point on near and far plane
	QVector3D worldPosNear = glCamera.pointOnNearPlane(width() / 2.0, height() / 2.0, viewport);
	QVector3D worldPosFar = glCamera.pointOnFarPlane(width() / 2.0, height() / 2.0, viewport);
	QVector3D ray_direction = (worldPosFar - worldPosNear).normalized();

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

	for (QVector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
	{
		object->storeFrame();				// store the position, velocity, inertia etc
		object->updateFrame(dt);			// update the position based on the velocity etc
		if (collisionsDetected(*object))
		{
			object->previousFrame();		// if the new position is in collision with another object
											// revert to previous position and use more accurate handling
		}
	}

	last_time_step = current_time_step;

	update();
}
