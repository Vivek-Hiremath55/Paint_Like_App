#include <QOpenGLBuffer>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include<vector>
#include "DataBase.h"
#include "Intersection.h"


class OpenGLWindow :public QOpenGLWidget, private QOpenGLFunctions
{
	Q_OBJECT

public:
	static bool drawLineMode;
	static bool drawCircleMode;
	static bool drawRectangleMode;
	static bool highlightMode;
	static bool drawPolylineMode;
	static bool drawPolylineMode2;

	void mousePressEvent(QMouseEvent* event) override;

	void drawLine();
	void drawCircle();
	void drawRectangle();
	void renderIntersection();
	void reset();
	void highlight();
	void drawPolyline();
	void drawPolyline2();


	OpenGLWindow(QWidget* parent = nullptr);

	QOpenGLShaderProgram* shaderProgram;
	QOpenGLBuffer vbo;

	DataBase db;
	Intersection it;

	std::vector<DataBase::Item>itemList;
	std::vector<DataBase::Item>highlightItemList;

	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec2 position;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = vec4(position, 0.0, 1.0);\n"
		"}\n";

	const char* fragmentShaderSource =
		"#version 330 core\n"
		"uniform vec4 color;\n"
		"out vec4 fragColor;\n"
		"void main()\n"
		"{\n"
		"    fragColor = color;\n"
		"}\n";
private:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;



};

