///////////////////////////////////////////////////////////////////////
//
// Assignment 2 consists in the following:
//
// - Rewrite the program using C++ classes for:
//   - Matrix manipulation;
//   - Shader manipulation;
//   - Managing drawable entities.
//
// - Provide an UML diagram of your solution.
//
// - Add the following functionality:
//   - Read shader code from external files;
//   - Check shader compilation and linkage for error messages.
// 
// - Draw the following scene, minimizing the number of vertices on the GPU:
//   - A set of 7 TANs (i.e. TANGRAM shapes) of different colors;
//   - A flat surface on which the TANs will be placed (with an appropriate contrasting color).
//
// - Alternate between the following dispositions when the user presses the 't' key;
//   - The 7 TANs in their original square configuration;
//   - The 7 TANs put together to form a shape of your choice (6500 to choose from!);
//   - The silhouette of the shape of your choice on the flat surface.
//
// Further suggestions to verify your understanding of the concepts explored:
//
// - Use linear interpolation to create a transition between the two TAN configurations.
// - Parse geometrical information from external XML files.
//
// (c) 2013 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <string>

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "Shader.h"
#include "ShaderProgram.h"
#include "Polygon.h"
#include "Matrix.h"
#include "scenenode/PolygonNode.h"
#include "scenenode/GroupNode.h"
#include "scenenode/SingleNode.h"
#include "scenenode/MatrixNode.h"
#include "scenenode/ColorNode.h"
#include "SceneManager.h"

#define CAPTION "Hello New World"

int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;

#define VERTICES 0
#define COLORS 1

GLuint VaoId, *VboId;
GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UniformId;
SceneManager manager;

/////////////////////////////////////////////////////////////////////// ERRORS

bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

void checkOpenGLError(std::string error)
{
	if(isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

/////////////////////////////////////////////////////////////////////// SHADERs

Shader *VertexShader   = NULL;
Shader *FragmentShader = NULL;
ShaderProgram *TriShaderProgram = NULL;

void createShaderProgram()
{
	VertexShader = new Shader(
		glCreateShader(GL_VERTEX_SHADER),
		"shaders/VertexShader.glsl"
	);
	VertexShader->compile();

	FragmentShader = new Shader(
		glCreateShader(GL_FRAGMENT_SHADER),
		"shaders/FragmentShader.glsl"
	);
	FragmentShader->compile();
	
	TriShaderProgram = new ShaderProgram(VertexShader, FragmentShader);

	ProgramId = TriShaderProgram->getId();
	TriShaderProgram->linkProgram();

	TriShaderProgram->setPositionAttribName("in_Position");
	TriShaderProgram->linkProgram();
	manager.setShaderProgram(TriShaderProgram);
    manager.getShaderProgram()->getUniformLocation("Color");
	checkOpenGLError("ERROR: Could not create shaders.");
}

void destroyShaderProgram()
{
	delete TriShaderProgram;

	checkOpenGLError("ERROR: Could not destroy shaders.");
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

#define L 1.0f // length of a side of the tangram square

const Vertex GrateTriagleVerices[] = 
{
	{{  0.0f,   0.0f,   0.0f, 1.0f }},
	{{  L/2.0f, L/2.0f, 0.0f, 1.0f }},
	{{ -L/2.0f, L/2.0f, 0.0f, 1.0f }}
};

GLfloat GrateTriagleColor1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat GrateTriagleColor2[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

const Vertex MiddleTriangleVertices[] =
{
	{{  0.0f,   0.0f,   0.0f, 1.0f }},
	{{  0.0f,   L/2.0f, 0.0f, 1.0f }},
	{{ -L/2.0f, 0.0f,   0.0f, 1.0f }}
};

GLfloat MiddleTriagleColor[4] = { 0.0f, 1.0f, 1.0f, 1.0f };

const GLubyte TriangleIndices[] =
{
	0,1,2
};


void createScene()
{
	// greate triangle
	Polygon *grateTriangle;
	grateTriangle = new Polygon(&manager);
	grateTriangle->setVertices(GrateTriagleVerices, sizeof(GrateTriagleVerices));
	grateTriangle->setIndices(TriangleIndices, sizeof(TriangleIndices), 3);
	grateTriangle->createBuffers();

	PolygonNode *grateTriangleNode  = new PolygonNode(grateTriangle);

	// grate triangle 1
	ColorNode *coloredGrateTriangle = new ColorNode(GrateTriagleColor1, &manager);
	coloredGrateTriangle->setNext(grateTriangleNode);
	MatrixNode *grateTrianglePosition = new MatrixNode( &manager, &Matrix::createIdentity() );
	grateTrianglePosition->setNext(coloredGrateTriangle);

	// grate triangle 2
	ColorNode *coloredGrateTriangle = new ColorNode(GrateTriagleColor2, &manager);
	coloredGrateTriangle->setNext(grateTriangleNode);
	MatrixNode *grateTrianglePosition = new MatrixNode( &manager, &Matrix::createRotationZ(PI/2) );
	grateTrianglePosition->setNext(coloredGrateTriangle);

	// middle triangle
	Polygon *middleTriangle;
	middleTriangle = new Polygon(&manager);
	middleTriangle->setVertices(MiddleTriangleVertices, sizeof(MiddleTriangleVertices));
	middleTriangle->setIndices(TriangleIndices, sizeof(TriangleIndices), 3);
	middleTriangle->createBuffers();

	PolygonNode *middleTriangleNode = new PolygonNode(middleTriangle);

	ColorNode *coloredMiddleTriangle = new ColorNode(MiddleTriagleColor, &manager);
	coloredMiddleTriangle->setNext(middleTriangleNode);

	MatrixNode *middleTrianglePosition = new MatrixNode( &manager, &Matrix::createTranslation(L/2.0f, -L/2.0f, 0) );
	middleTrianglePosition->setNext(coloredMiddleTriangle);

	
	GroupNode *sceneRoot = manager.getSceneRoot();
	sceneRoot->add( grateTrianglePosition );
	sceneRoot->add( middleTrianglePosition );
	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void destroyBufferObjects()
{
	// Donne whene the sceneRoot is destroyed.
	/*
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(2, VboId);
	glDeleteVertexArrays(1, &VaoId);
	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
	*/
}

/////////////////////////////////////////////////////////////////////// SCENE

GLfloat Iv[16] = {
	1.0f,  0.0f,  0.0f,  0.0f,
	0.0f,  1.0f,  0.0f,  0.0f,
	0.0f,  0.0f,  1.0f,  0.0f,
	0.0f,  0.0f,  0.0f,  1.0f
}; // Row Major (GLSL is Column Major)

GLfloat Mv[16] = {
	1.0f,  0.0f,  0.0f, -1.0f,
	0.0f,  1.0f,  0.0f, -1.0f,
	0.0f,  0.0f,  1.0f,  0.0f,
	0.0f,  0.0f,  0.0f,  1.0f
}; // Row Major (GLSL is Column Major)


Matrix I(Iv);
Matrix T = Matrix::createTranslation(-1,-1,0);
Matrix R = Matrix::createRotationZ(PI/2);
Matrix FinalMatrix = Matrix::createTranslation(1,0,0) * R;

void drawScene()
{
	manager.renderScene();

	checkOpenGLError("ERROR: Could not draw scene.");
}

/////////////////////////////////////////////////////////////////////// CALLBACKS

void cleanup()
{
	destroyShaderProgram();
	destroyBufferObjects();
}

void display()
{
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawScene();
	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	WinX = w;
	WinY = h;
	glViewport(0, 0, WinX, WinY);
}

void timer(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
    FrameCount = 0;
    glutTimerFunc(1000, timer, 0);
}

/////////////////////////////////////////////////////////////////////// SETUP

void setupCallbacks() 
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
}

void setupOpenGL() {
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void setupGLEW() {
	glewExperimental = GL_TRUE;
	GLenum result = glewInit() ; 
	if (result != GLEW_OK) { 
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	} 
	GLenum err_code = glGetError();
}

void setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);
	
	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	
	glutInitWindowSize(WinX, WinY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	WindowHandle = glutCreateWindow(CAPTION);
	if(WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	createShaderProgram();
	createScene();
	setupCallbacks();
}

int main(int argc, char* argv[])
{
	init(argc, argv);
	glutMainLoop();	
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////
