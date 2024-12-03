#define _USE_MATH_DEFINES
#include <cmath>
// glew include
#include <GL/glew.h>

// std includes
#include <string>
#include <iostream>

// glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/TimeManager.h"

// Shader include
#include "Headers/Shader.h"

// Model geometric includes
#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
//#include "Headers/FirstPersonCamera.h"
#include "Headers/ThirdPersonCamera.h"

// GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Headers/Texture.h"

// Include loader Model class
#include "Headers/Model.h"

// Include Terrain
#include "Headers/Terrain.h"

#include "Headers/AnimationUtils.h"

#include "Headers/Colisiones.h"

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a) / sizeof(a[0]))

// Constantes globales
int screenWidth;
int screenHeight;
const int TERRAIN_SIZE = 200;

GLFWwindow *window;

Shader shader;
// Shader con skybox
Shader shaderSkybox;
// Shader con multiples luces
Shader shaderMulLighting;
// Shader para el terreno
Shader shaderTerrain;

Shader shaderCrosshair;

std::shared_ptr<Camera> camera(new ThirdPersonCamera());
float distanceFromTarget = 7.0;

// Objetos
Sphere skyboxSphere(20, 20);
Box boxCollider;
Sphere modelEsfereCollider(10, 10);
Cylinder modeloRayo(20, 20);

// Variables ======================================================
bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;
//float rotDartHead = 0.0, rotDartLeftArm = 0.0, rotDartLeftHand = 0.0, rotDartRightArm = 0.0, rotDartRightHand = 0.0, rotDartLeftLeg = 0.0, rotDartRightLeg = 0.0;
//float rotBuzzHead = 0.0, rotBuzzLeftarm = 0.0, rotBuzzLeftForeArm = 0.0, rotBuzzLeftHand = 0.0;
int modelSelected = 0;
bool enableCountSelected = true;
bool enableActionKeyF = true;

float mouseSensitivity = 0.01f;
float cameraSensitivity = 0.4f;

float joystickSensitivity = 0.5f;  // Sensibilidad del joystick
float joystickDeadzone = 0.2f;     // Zona muerta del joystick
bool isAiming = false;  
// Variables to animations keyframes
//bool saveFrame = false, availableSave = true;
//std::ofstream myfile;
//std::string fileName = "";
//bool record = false;

double deltaTime;
double currTime, lastTime;

// Variables de salto
bool isJump = false;
float GRAVITY = 1.8;
double tmv = 0;
double startTimeJump = 0;

bool isCollidersVisible = false;
bool enableActionKeyC = false;
int estadoTiempo = 0;
bool enableActionKeyT = false;
glm::vec3 colorAmbiente = glm::vec3(1.0);
glm::vec3 colorDifuso = glm::vec3(1.0);
glm::vec3 colorEspecular = glm::vec3(1.0);
glm::vec3 direccionLuz = glm::vec3(1.0);
bool isLampON = false;
bool enableActionKeyL = false;

//camara primera persona
bool isFirstPerson = false;
bool enableActionKeyV = true;

// Definición de los modelos ======================================
// Aquí se definen los modelos, matrices y variables requeridas por
// cada modelo.

// Casa de campaña
Model modelCasaCamp;
glm::mat4 modelMatrixCasaCamp = glm::mat4(1.0); // Matriz de transformación

// Arboles tipo 1
Model modelArbol1;
// Posicionamiento de cada arbol
std::vector<glm::vec3> arbol1Position = {
	glm::vec3(-70, 0, -67), glm::vec3(-21, 0, -85), glm::vec3(1, 0, -73), 
	glm::vec3(-17, 0, -54), glm::vec3(15, 0, -62), glm::vec3(41, 0, -69), 
	glm::vec3(63, 0, -89), glm::vec3(63, 0, -69), glm::vec3(84, 0, -75), 
	glm::vec3(-64, 0, 88), glm::vec3(92, 0, -92), glm::vec3(-29, 0, -37), 
	glm::vec3(-19, 0, 90), glm::vec3(72, 0, 74), glm::vec3(55, 0, -48), 
	glm::vec3(90, 0, -38), glm::vec3(68, 0, -30), glm::vec3(43, 0, -38), 
	glm::vec3(5, 0, -32), glm::vec3(24, 0, 80), glm::vec3(-45, 0, -22), 
	glm::vec3(50, 0, 74), glm::vec3(-94, 0, -28), glm::vec3(-85, 0, -14), 
	glm::vec3(-67, 0, -6), glm::vec3(6, 0, 92), glm::vec3(-10, 0, -17), 
	glm::vec3(24, 0, -19), glm::vec3(62, 0, 55), glm::vec3(84, 0, -18), 
	glm::vec3(69, 0, -9), glm::vec3(38, 0, -2), glm::vec3(89, 0, 4), 
	glm::vec3(-44, 0, 1), glm::vec3(-19, 0, 6), glm::vec3(-85, 0, 8), 
	glm::vec3(55, 0, 5), glm::vec3(-59, 0, 14), glm::vec3(23, 0, 11), 
	glm::vec3(33, 0, -54), glm::vec3(0, 0, 19), glm::vec3(-34, 0, 20), 
	glm::vec3(-77, 0, 26), glm::vec3(-92, 0, 39), glm::vec3(-60, 0, 38), 
	glm::vec3(-57, 0, -96), glm::vec3(15, 0, 32), glm::vec3(39, 0, 20), 
	glm::vec3(64, 0, 30), glm::vec3(87, 0, 25), glm::vec3(79, 0, 42), 
	glm::vec3(43, 0, 43), glm::vec3(-5, 0, 45), glm::vec3(-39, 0, 46), 
	glm::vec3(-74, 0, 49), glm::vec3(-96, 0, 62), glm::vec3(-54, 0, 63), 
	glm::vec3(-19, 0, 58), glm::vec3(21, 0, 54), glm::vec3(12, 0, -4)
};

// Arboles tipo 2
/*Model modelArbol2;
// Posicionamiento de cada arbol
std::vector<glm::vec3> arbol2Position = {
	glm::vec3(-67, 0, -62), glm::vec3(-3, 0, -93), glm::vec3(75, 0, -48), 
	glm::vec3(95, 0, 93), glm::vec3(-81, 0, 70), glm::vec3(-43, 0, 90),
	glm::vec3(37, 0, 86), glm::vec3(73, 0, 14), glm::vec3(-21, 0, 38),
	glm::vec3(-12, 0, -38),
};*/

// Arboles otoño
Model modelArbolOtono;
// Posicionamiento de cada arbol
std::vector<glm::vec3> arbolOtonoPosition = {
	glm::vec3(-60, 0, -63), glm::vec3(91, 0, 58), glm::vec3(-2, 0, 79), 
	glm::vec3(-25, 0, -6), glm::vec3(89, 0, -59), glm::vec3(32, 0, -92),
	glm::vec3(-64, 0, 62), glm::vec3(50, 0, -18), glm::vec3(80, 0, -3),
	glm::vec3(56, 0, 21), glm::vec3(-18, 0, 22), glm::vec3(36, 0, 61),
	glm::vec3(10, 0, -45), glm::vec3(77, 0, -87), glm::vec3(4, 0, 62),
	glm::vec3(-85, 0, 86), glm::vec3(-70, 0, 12), glm::vec3(-16, 0, -73),
	glm::vec3(59, 0, 92), glm::vec3(-34, 0, 76),
};

// Plantas acuaticas
Model modelPlanta;
// Posicionamiento de cada planta
std::vector<glm::vec3> plantaPosition = {
	glm::vec3(-61, 0, -58), glm::vec3(-53, 0, -68), glm::vec3(-73, 0, -64), 
	glm::vec3(-71, 0, -75), glm::vec3(-38, 0, -48), glm::vec3(-36, 0, -93), 
	glm::vec3(-92, 0, -39), glm::vec3(50, 0, -79), glm::vec3(15, 0, -78), 
	glm::vec3(-93, 0, -92)
};

// Yerbas
Model modelYerba;
// Posicionamiento
std::vector<glm::vec3> yerbaPosition = {
	glm::vec3(5, 0, -15), glm::vec3(24, 0, -39), glm::vec3(30, 0, 33), 
	glm::vec3(-57, 0, 78), glm::vec3(-65, 0, -65), glm::vec3(8, 0, -91), 
	glm::vec3(75, 0, -64), glm::vec3(-49, 0, 28), glm::vec3(76, 0, 56), 
	glm::vec3(12, 0, 72)
};

// Troncos
Model modelTronco;
// Posicionamiento
std::vector<glm::vec3> troncoPosition = {
	glm::vec3(48, 0, 58), glm::vec3(-6, 0, 31), glm::vec3(-20, 0, 77), 
	glm::vec3(-4, 0, -56), glm::vec3(50, 0, -63), glm::vec3(94, 0, 39), 
	glm::vec3(-95, 0, -3)
};
// Ángulo de orientación por cada arbol
std::vector<float> troncoOrientation = {
	0, 30, 60, 90, 120, 150, 180
};

// Personaje principal
Model modelCazador;
glm::mat4 modelMatrixCazador = glm::mat4(1.0f);
int animationIndexCazador = 1;

Model modelGun;
glm::mat4 modelMatrixGun = glm::mat4(1.0f);

// Terrain model instance
Terrain terrain(-1, -1, TERRAIN_SIZE, 8, "../Textures/heightmap.png");

GLuint textureLeavesID, textureWallID, textureWindowID, textureHighwayID, textureLandingPadID;
GLuint textureTerrainRID, textureTerrainGID, textureTerrainBID, textureTerrainBlendMapID;
GLuint skyboxTextureID, crosshairTextureID;

GLuint crosshairVAO, crosshairVBO;

GLenum types[6] = {
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z};

// Texturas del skybox
std::string fileNames[6] = {
	"../Textures/Storforsen3/posx.jpg",
	"../Textures/Storforsen3/negx.jpg",
	"../Textures/Storforsen3/posy.jpg",
	"../Textures/Storforsen3/negy.jpg",
	"../Textures/Storforsen3/posz.jpg",
	"../Textures/Storforsen3/negz.jpg",
};

std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4>> collidersSBB;
std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>> collidersOBB;

/*std::vector<glm::vec3> lamp2Position = {
	glm::vec3(-36.52, 0, -23.24),
	glm::vec3(-52.73, 0, -3.90)
};
std::vector<float> lamp2Orientation = {
	21.37 + 90, -65.0 + 90
};*/

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow *window, int key, int scancode, int action,
				 int mode);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod);
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);

void renderCrosshair() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, crosshairTextureID);
    shaderCrosshair.setInt("crosshairTexture", 0);
    
    glBindVertexArray(crosshairVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);
    glDisable(GL_BLEND);
}

// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen)
{

	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
								  glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
								  nullptr);

	if (window == nullptr)
	{
		std::cerr
			<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
			<< std::endl;
		destroy();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Inicialización de los shaders
	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
	shaderSkybox.initialize("../Shaders/skyBox.vs", "../Shaders/skyBox.fs");
	//shaderSkybox.initialize("../Shaders/skyBox.vs", "../Shaders/multipleLights.fs");
	shaderMulLighting.initialize("../Shaders/iluminacion_textura_animation.vs", "../Shaders/multipleLights.fs");
	shaderTerrain.initialize("../Shaders/terrain.vs", "../Shaders/terrain.fs");
	shaderCrosshair.initialize("../Shaders/crosshair.vs", "../Shaders/crosshair.fs");

	float crosshairVertices[] = {
        // Pos      // TexCoords
        -0.05f,  0.05f, 0.0f, 0.0f, 1.0f,
        -0.05f, -0.05f, 0.0f, 0.0f, 0.0f,
         0.05f, -0.05f, 0.0f, 1.0f, 0.0f,

        -0.05f,  0.05f, 0.0f, 0.0f, 1.0f,
         0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
         0.05f,  0.05f, 0.0f, 1.0f, 1.0f
    };

    glGenVertexArrays(1, &crosshairVAO);
    glGenBuffers(1, &crosshairVBO);
    glBindVertexArray(crosshairVAO);
    glBindBuffer(GL_ARRAY_BUFFER, crosshairVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(crosshairVertices), &crosshairVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));


	// Inicializacion de los objetos.
	skyboxSphere.init();
	skyboxSphere.setShader(&shaderSkybox);
	skyboxSphere.setScale(glm::vec3(20.0f, 20.0f, 20.0f));

	boxCollider.init();
	boxCollider.setShader(&shader);
	boxCollider.setColor(glm::vec4(1.0));

	modelEsfereCollider.init();
	modelEsfereCollider.setShader(&shader);
	modelEsfereCollider.setColor(glm::vec4(1.0));

	modeloRayo.init();
	modeloRayo.setShader(&shader);
	modeloRayo.setColor(glm::vec4(1.0, 1.0, 1.0, 0.3));

	// Casa de campaña
	modelCasaCamp.loadModel("../models/casa_camp/casa_camp.obj");
	modelCasaCamp.setShader(&shaderMulLighting);

	// Arboles tipo 1
	modelArbol1.loadModel("../models/arbol1/arbol.obj");
	modelArbol1.setShader(&shaderMulLighting);
	/*modelLamp2.loadModel("../models/Street_Light/Lamp.obj");
	modelLamp2.setShader(&shaderMulLighting);
	modelLampPost2.loadModel("../models/Street_Light/LampPost.obj");
	modelLampPost2.setShader(&shaderMulLighting);*/

	// Arboles tipo 2
	/*modelArbol2.loadModel("../models/arbol2/arbol.obj");
	modelArbol2.setShader(&shaderMulLighting);*/

	// Arboles otoño
	modelArbolOtono.loadModel("../models/arbol_otono/arbol_otono.obj");
	modelArbolOtono.setShader(&shaderMulLighting);

	// Plantas acuaticas
	modelPlanta.loadModel("../models/planta/planta.obj");
	modelPlanta.setShader(&shaderMulLighting);

	// Yerbas
	modelYerba.loadModel("../models/yerba/yerba.obj");
	modelYerba.setShader(&shaderMulLighting);

	// Troncos
	modelTronco.loadModel("../models/troncos/troncoarbol.obj");
	modelTronco.setShader(&shaderMulLighting);

	// Personaje principal
	modelCazador.loadModel("../models/swat/Swat.fbx");
	modelCazador.setShader(&shaderMulLighting);

	modelGun.loadModel("../models/arma/arma.fbx");
	modelGun.setShader(&shaderMulLighting);
	

	// Terreno
	terrain.init();
	terrain.setShader(&shaderTerrain);

	camera->setPosition(glm::vec3(0.0, 3.0, 4.0));
	camera->setDistanceFromTarget(distanceFromTarget);
	camera->setSensitivity(cameraSensitivity);

	// Carga de texturas para el skybox
	Texture skyboxTexture = Texture("");
	glGenTextures(1, &skyboxTextureID);
	// Tipo de textura CUBE MAP
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++)
	{
		skyboxTexture = Texture(fileNames[i]);
		skyboxTexture.loadImage(true);
		if (skyboxTexture.getData())
		{
			glTexImage2D(types[i], 0, skyboxTexture.getChannels() == 3 ? GL_RGB : GL_RGBA, skyboxTexture.getWidth(), skyboxTexture.getHeight(), 0,
						 skyboxTexture.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, skyboxTexture.getData());
		}
		else
			std::cout << "Failed to load texture" << std::endl;
		skyboxTexture.freeImage();
	}

	// Definiendo la textura a utilizar
	Texture textureLeves("../Textures/leaves_forest_ground.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	textureLeves.loadImage();
	// Creando la textura con id 1
	glGenTextures(1, &textureLeavesID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureLeavesID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (textureLeves.getData())
	{
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		std::cout << "Numero de canales :=> " << textureLeves.getChannels() << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, textureLeves.getChannels() == 3 ? GL_RGB : GL_RGBA, textureLeves.getWidth(), textureLeves.getHeight(), 0,
					 textureLeves.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureLeves.getData());
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureLeves.freeImage();

	// Definiendo la textura a utilizar
	Texture textureWall("../Textures/whiteWall.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	textureWall.loadImage();


	// Creando la textura con id 1
	glGenTextures(1, &textureWallID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureWallID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (textureWall.getData())
	{
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, textureWall.getChannels() == 3 ? GL_RGB : GL_RGBA, textureWall.getWidth(), textureWall.getHeight(), 0,
					 textureWall.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureWall.getData());
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureWall.freeImage();

	Texture textureCrosshair("../Textures/objetivo.png");
	textureCrosshair.loadImage(true); // true para incluir canal alpha
	glGenTextures(1, &crosshairTextureID);
	glBindTexture(GL_TEXTURE_2D, crosshairTextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (textureCrosshair.getData()) {
		// Forzar el formato a RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
					textureCrosshair.getWidth(), textureCrosshair.getHeight(), 
					0, GL_RGBA, GL_UNSIGNED_BYTE, textureCrosshair.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	textureCrosshair.freeImage();

	// Definiendo la textura a utilizar
	Texture textureWindow("../Textures/ventana.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	textureWindow.loadImage();
	// Creando la textura con id 1
	glGenTextures(1, &textureWindowID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureWindowID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (textureWindow.getData())
	{
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, textureWindow.getChannels() == 3 ? GL_RGB : GL_RGBA, textureWindow.getWidth(), textureWindow.getHeight(), 0,
					 textureWindow.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureWindow.getData());
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureWindow.freeImage();

	// Definiendo la textura a utilizar
	Texture textureHighway("../Textures/highway.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	textureHighway.loadImage();
	// Creando la textura con id 1
	glGenTextures(1, &textureHighwayID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureHighwayID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (textureHighway.getData())
	{
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, textureHighway.getChannels() == 3 ? GL_RGB : GL_RGBA, textureHighway.getWidth(), textureHighway.getHeight(), 0,
					 textureHighway.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureHighway.getData());
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureHighway.freeImage();

	// Definiendo la textura
	Texture textureLandingPad("../Textures/landingPad.jpg");
	textureLandingPad.loadImage();									  // Cargar la textura
	glGenTextures(1, &textureLandingPadID);							  // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureLandingPadID);				  // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	  // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	  // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if (textureLandingPad.getData())
	{
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureLandingPad.getChannels() == 3 ? GL_RGB : GL_RGBA, textureLandingPad.getWidth(), textureLandingPad.getHeight(), 0,
					 textureLandingPad.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureLandingPad.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Fallo la carga de textura" << std::endl;
	textureLandingPad.freeImage(); // Liberamos memoria

	// Defininiendo texturas del mapa de mezclas
	// Definiendo la textura para rojo
	Texture textureR("../Textures/ganges_river_pebbles.png");
	textureR.loadImage();											  // Cargar la textura
	glGenTextures(1, &textureTerrainRID);							  // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID);				  // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	  // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	  // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if (textureR.getData())
	{
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureR.getChannels() == 3 ? GL_RGB : GL_RGBA, textureR.getWidth(), textureR.getHeight(), 0,
					 textureR.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureR.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Fallo la carga de textura" << std::endl;
	textureR.freeImage(); // Liberamos memoria

	// Definiendo la textura para verde
	Texture textureG("../Textures/grassy.png");
	textureG.loadImage();											  // Cargar la textura
	glGenTextures(1, &textureTerrainGID);							  // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID);				  // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	  // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	  // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if (textureG.getData())
	{
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureG.getChannels() == 3 ? GL_RGB : GL_RGBA, textureG.getWidth(), textureG.getHeight(), 0,
					 textureG.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureG.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Fallo la carga de textura" << std::endl;
	textureG.freeImage(); // Liberamos memoria

	// Definiendo la textura para azul
	Texture textureB("../Textures/water.png");
	textureB.loadImage();											  // Cargar la textura
	glGenTextures(1, &textureTerrainBID);							  // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID);				  // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	  // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	  // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if (textureB.getData())
	{
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureB.getChannels() == 3 ? GL_RGB : GL_RGBA, textureB.getWidth(), textureB.getHeight(), 0,
					 textureB.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureB.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Fallo la carga de textura" << std::endl;
	textureB.freeImage(); // Liberamos memoria

	// Definiendo la textura de mezclas
	Texture textureBlendMap("../Textures/blendMap.png");
	textureBlendMap.loadImage();									  // Cargar la textura
	glGenTextures(1, &textureTerrainBlendMapID);					  // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);			  // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	  // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	  // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if (textureBlendMap.getData())
	{
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureBlendMap.getChannels() == 3 ? GL_RGB : GL_RGBA, textureBlendMap.getWidth(), textureBlendMap.getHeight(), 0,
					 textureBlendMap.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureBlendMap.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Fallo la carga de textura" << std::endl;
	textureBlendMap.freeImage(); // Liberamos memoria
}

void destroy()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	// --------- IMPORTANTE ----------
	// Eliminar los shader y buffers creados.

	// Shaders Delete
	shader.destroy();
	shaderMulLighting.destroy();
	shaderSkybox.destroy();
	shaderTerrain.destroy();

	// Basic objects Delete
	skyboxSphere.destroy();

	// Custom objects Delete
	modelCasaCamp.destroy();
	modelArbol1.destroy();
	//modelArbol2.destroy();
	modelArbolOtono.destroy();
	modelPlanta.destroy();
	modelYerba.destroy();
	modelTronco.destroy();
	modelCazador.destroy();
	modelGun.destroy();

	// Terrains objects Delete
	terrain.destroy();

	// Textures Delete
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureLeavesID);
	glDeleteTextures(1, &textureWallID);
	glDeleteTextures(1, &textureWindowID);
	glDeleteTextures(1, &textureHighwayID);
	glDeleteTextures(1, &textureLandingPadID);
	glDeleteTextures(1, &textureTerrainBID);
	glDeleteTextures(1, &textureTerrainGID);
	glDeleteTextures(1, &textureTerrainRID);
	glDeleteTextures(1, &textureTerrainBlendMapID);

	// Cube Maps Delete
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &skyboxTextureID);
	glDeleteTextures(1, &crosshairTextureID);
}

void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes)
{
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
				 int mode)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos)
{
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	distanceFromTarget -= yoffset;
	camera->setDistanceFromTarget(distanceFromTarget);
}

void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod)
{
	if (state == GLFW_PRESS)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication)
{
	if (exitApp || glfwWindowShouldClose(window) != 0)
	{
		return false;
	}

	if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GL_TRUE) {
		int axesCount, buttonCount;
		const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

		// Movimiento con stick izquierdo
		if (fabs(axes[0]) > joystickDeadzone) {
			modelMatrixCazador = glm::rotate(modelMatrixCazador, 
				glm::radians(-axes[0] * joystickSensitivity), 
				glm::vec3(0, 1, 0));
			animationIndexCazador = 1;
		}
		if (fabs(axes[1]) > joystickDeadzone) {
			modelMatrixCazador = glm::translate(modelMatrixCazador, 
				glm::vec3(0, 0, -axes[1] * 0.1));
			animationIndexCazador = 1;
		}

		// Cámara con stick derecho
		if (fabs(axes[2]) > joystickDeadzone) {
			camera->mouseMoveCamera(-axes[2] * joystickSensitivity, 0.0, deltaTime);
		}
		if (fabs(axes[3]) > joystickDeadzone) {
			camera->mouseMoveCamera(0.0, axes[3] * joystickSensitivity, deltaTime);
		}

		// Apuntado con gatillo derecho (RT)
		if (axes[5] > 0.5f && !isFirstPerson) {
			isFirstPerson = true;
			camera->setDistanceFromTarget(0.0f);
		} else if (axes[5] <= 0.5f && isFirstPerson) {
			isFirstPerson = false;
			camera->setDistanceFromTarget(distanceFromTarget);
		}

		// Salto con botón A (0)
		if (!isJump && buttons[0] == GLFW_PRESS) {
			isJump = true;
			tmv = 0;
			startTimeJump = currTime;
		}

		// Linterna con botón Y (3)
		if (buttons[3] == GLFW_PRESS && enableActionKeyL) {
			enableActionKeyL = false;
			isLampON = !isLampON;
		} else if (buttons[3] == GLFW_RELEASE) {
			enableActionKeyL = true;
		}

		// Disparo con gatillo izquierdo (LT)
		if (axes[4] > 0.5f) {
			animationIndexCazador = 0; // Animación de disparo
		}

		// Cambio de tiempo con D-pad (POV)
		if (buttons[11] == GLFW_PRESS && enableActionKeyT) { // D-pad derecho
			enableActionKeyT = false;
			estadoTiempo++;
			if (estadoTiempo > 5) estadoTiempo = 0;
		} else if (buttons[11] == GLFW_RELEASE) {
			enableActionKeyT = true;
		}
	}

	if (enableActionKeyV && glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
		enableActionKeyV = false;
		isFirstPerson = !isFirstPerson;
		if (isFirstPerson) {
			camera->setDistanceFromTarget(0.0f);
		} else {
			camera->setDistanceFromTarget(distanceFromTarget);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_V) == GLFW_RELEASE) {
		enableActionKeyV = true;
	}


	// Movimientos del personaje principal con control de xbox
	if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GL_TRUE)
	{
		// std::cout << "Joystick presente" << std::endl;
		int axesCount, buttonCount;
		const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		// std::cout << "Número de ejes disponible" << axesCount << std::endl;
		// std::cout << "Stick Izquiedo eje x" << axes[0] << std::endl;
		// std::cout << "Stick Izquiedo eje y" << axes[1] << std::endl;
		// std::cout << "Stick derecho eje x " << axes[2] << std::endl;
		// std::cout << "Stick derecho eje y " << axes[5] << std::endl;
		// std::cout << "Trigger izquierdo " << axes[3] << std::endl;
		// std::cout << "Trigger derecho " << axes[4] << std::endl;
		if (fabs(axes[0]) > 0.2)
		{
			modelMatrixCazador = glm::rotate(modelMatrixCazador, glm::radians(-axes[0] * 0.5f), glm::vec3(0, 1, 0));
			animationIndexCazador = 1;
		}
		if (fabs(axes[1]) > 0.2)
		{
			modelMatrixCazador = glm::translate(modelMatrixCazador, glm::vec3(0, 0, -axes[1] * 0.1));
			animationIndexCazador = 1;
		}
		if (fabs(axes[2]) > 0.2)
		{
			camera->mouseMoveCamera(-axes[2], 0.0, deltaTime);
		}
		if (fabs(axes[5]) > 0.2)
		{
			camera->mouseMoveCamera(0.0, axes[5], deltaTime);
		}
		const unsigned char *buttons =
			glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
		if (buttons[0] == GLFW_PRESS)
			std::cout << "Se presiona boton" << std::endl;
		if (!isJump && buttons[0] == GLFW_PRESS)
		{
			isJump = true;
			tmv = 0;
			startTimeJump = currTime;
		}
	}

	// Control con el ratón
	//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		// Clic izquierdo
		//camera->mouseMoveCamera(offsetX, 0.0, deltaTime);
		
	//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		// Clic derecho
		//camera->mouseMoveCamera(0.0, offsetY, deltaTime);

	// Rotación del personaje prinicipal con el movimiento del mouse
	modelMatrixCazador = glm::rotate(modelMatrixCazador, -offsetX * mouseSensitivity, glm::vec3(0, 1, 0));
	camera->mouseMoveCamera(0.0, offsetY, deltaTime);

	offsetX = 0;
	offsetY = 0;

	// Hacer visibles los colliders
	if (enableActionKeyC && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		enableActionKeyC = false;
		isCollidersVisible = !isCollidersVisible;
	}
	else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
	{
		enableActionKeyC = true;
	}

	// Activar la linterna
	if (enableActionKeyL && glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		enableActionKeyL = false;
		isLampON = !isLampON;
	}
	else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE)
	{
		enableActionKeyL = true;
	}

	// TEMPORAL. Cambiar la iluminación
	if (enableActionKeyT && glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		enableActionKeyT = false;

		switch (estadoTiempo) {
			case 0:
			// Iluminación de madrugada
			colorAmbiente = glm::vec3(0.30, 0.50, 1.00);
			colorDifuso = glm::vec3(0.3,0.3,0);
			colorEspecular = glm::vec3(0.3, 0.3, 0.0);
			direccionLuz = glm::vec3(1,0,0);
			break;
			case 1:
			// Iluminación de mañana
			colorAmbiente = glm::vec3(0.60, 0.7, 1.0);
			colorDifuso = glm::vec3(0.5,0.5,0.5);
			colorEspecular = glm::vec3(0.5, 0.5, 0.5);
			direccionLuz = glm::vec3(1,-1,0);
			break;
			case 2:
			// Iluminación de medio día
			colorAmbiente = glm::vec3(0.8, 0.9, 1.0);
			colorDifuso = glm::vec3(0.8, 0.9, 1.0);
			colorEspecular = glm::vec3(0.8, 0.9, 1.0);
			direccionLuz = glm::vec3(0,-1,0);
			break;
			case 3:
			// Iluminación de tarde
			colorAmbiente = glm::vec3(0.6, 0.6, 0.6);
			colorDifuso = glm::vec3(0.8,0.8,1);
			colorEspecular = glm::vec3(0.8, 0.8, 1);
			direccionLuz = glm::vec3(-1,-1,0);
			break;
			case 4:
			// Iluminación de atardecer
			colorAmbiente = glm::vec3(0.3, 0.5, 1.0);
			colorDifuso = glm::vec3(1, 0.4, 0.0);
			colorEspecular = glm::vec3(1, 0.4, 0);
			direccionLuz = glm::vec3(-1,0,0);
			break;
			case 5:
			// Iluminación de noche
			colorAmbiente = glm::vec3(0.1, 0.2, 0.5);
			colorDifuso = glm::vec3(0.2);
			colorEspecular = glm::vec3(0.2);
			direccionLuz = glm::vec3(0,-1,0);
			break;
			default:
			// Iluminación por defecto
			colorAmbiente = glm::vec3(1);
			colorDifuso = glm::vec3(1);
			colorEspecular = glm::vec3(1);
			direccionLuz = glm::vec3(1);
			estadoTiempo = -1;
			break;
		}
		estadoTiempo++;
	}
	else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE)
	{
		enableActionKeyT = true;
	}
	// Seleccionar modelo
	/*if (enableCountSelected && glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS){
		enableCountSelected = false;
		modelSelected++;
		if(modelSelected > 4)
			modelSelected = 0;
		if(modelSelected == 1)
			fileName = "../animaciones/animation_dart_joints.txt";
		if (modelSelected == 2)
			fileName = "../animaciones/animation_dart.txt";
		if(modelSelected == 3)
			fileName = "../animaciones/animation_buzz_joints.txt";
		if (modelSelected == 4)
			fileName = "../animaciones/animation_buzz.txt";
		std::cout << "modelSelected: " << modelSelected << std::endl;
	}
	else if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
		enableCountSelected = true;*/

	// Guardar key frames
	/*if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
			&& glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
		record = true;
		if(myfile.is_open())
			myfile.close();
		myfile.open(fileName);
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE
			&& glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
		record = false;
		myfile.close();
		if(modelSelected == 1)
			keyFramesDartJoints = getKeyRotFrames(fileName);
		if (modelSelected == 2)
			keyFramesDart = getKeyFrames(fileName);
		if(modelSelected == 3)
			keyFramesBuzzJoints = getKeyRotFrames(fileName);
		if (modelSelected == 4)
			keyFramesBuzz = getKeyFrames(fileName);
	}
	if(availableSave && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
		saveFrame = true;
		availableSave = false;
	}if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE)
		availableSave = true;*/

	// Dart Lego model movements
	/*if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
			glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		rotDartHead += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		rotDartHead -= 0.02;
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
			glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		rotDartLeftArm += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		rotDartLeftArm -= 0.02;
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
			glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		rotDartRightArm += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		rotDartRightArm -= 0.02;
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
			glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		rotDartLeftHand += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		rotDartLeftHand -= 0.02;
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
			glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		rotDartRightHand += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		rotDartRightHand -= 0.02;
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
			glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		rotDartLeftLeg += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		rotDartLeftLeg -= 0.02;
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
			glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		rotDartRightLeg += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		rotDartRightLeg -= 0.02;
	if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		modelMatrixDart = glm::rotate(modelMatrixDart, 0.02f, glm::vec3(0, 1, 0));
	else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		modelMatrixDart = glm::rotate(modelMatrixDart, -0.02f, glm::vec3(0, 1, 0));
	if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		modelMatrixDart = glm::translate(modelMatrixDart, glm::vec3(-0.02, 0.0, 0.0));
	else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		modelMatrixDart = glm::translate(modelMatrixDart, glm::vec3(0.02, 0.0, 0.0));*/

	// Movimientos de buzz
	/*if (modelSelected == 3 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
			glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		rotBuzzHead += 0.02;
	else if (modelSelected == 3 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		rotBuzzHead -= 0.02;
	if (modelSelected == 3 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
			glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		rotBuzzLeftarm += 0.02;
	else if (modelSelected == 3 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		rotBuzzLeftarm -= 0.02;
	if (modelSelected == 3 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
			glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		rotBuzzLeftForeArm += 0.02;
	else if (modelSelected == 3 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		rotBuzzLeftForeArm -= 0.02;
	if (modelSelected == 3 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
			glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		rotBuzzLeftHand += 0.02;
	else if (modelSelected == 3 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		rotBuzzLeftHand -= 0.02;
	if (modelSelected == 4 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		modelMatrixBuzz = glm::rotate(modelMatrixBuzz, 0.02f, glm::vec3(0, 1, 0));
	else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		modelMatrixBuzz = glm::rotate(modelMatrixBuzz, -0.02f, glm::vec3(0, 1, 0));
	if (modelSelected == 4 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		modelMatrixBuzz = glm::translate(modelMatrixBuzz, glm::vec3(0.0, 0.0, 0.02));
	else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		modelMatrixBuzz = glm::translate(modelMatrixBuzz, glm::vec3(0.0, 0.0, -0.02));*/

	// Controles del personaje principal
	if (modelSelected == 0 && (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS))
	{
		modelMatrixCazador = glm::translate(modelMatrixCazador, glm::vec3(0.1, 0.0, 0.0));
		animationIndexCazador = 2;
	}
	else if (modelSelected == 0 && (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS))
	{
		modelMatrixCazador = glm::translate(modelMatrixCazador, glm::vec3(-0.1, 0.0, 0.0));
		animationIndexCazador = 2;
	}
	if (modelSelected == 0 && (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
	{
		modelMatrixCazador = glm::translate(modelMatrixCazador, glm::vec3(0.0, 0.0, 0.2));
		animationIndexCazador = 2;
	}
	else if (modelSelected == 0 && (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS))
	{
		modelMatrixCazador = glm::translate(modelMatrixCazador, glm::vec3(0.0, 0.0, -0.2));
		animationIndexCazador = 2;
	}
	
	if (enableActionKeyF && glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		animationIndexCazador = 0;
	}
	bool keySpaceStatus = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
	if (!isJump && keySpaceStatus)
	{
		isJump = true;
		startTimeJump = currTime;
		tmv = 0;
	}

	glfwPollEvents();
	return continueApplication;
}

void applicationLoop()
{
	bool psi = true;

	glm::vec3 axis;
	glm::vec3 target;
	float angleTarget;

	/*modelMatrixEclipse = glm::translate(modelMatrixEclipse, glm::vec3(27.5, 0, 30.0));
	modelMatrixEclipse = glm::rotate(modelMatrixEclipse, glm::radians(180.0f), glm::vec3(0, 1, 0));
	int state = 0;
	float advanceCount = 0.0;
	float rotCount = 0.0;
	float rotWheelsX = 0.0;
	float rotWheelsY = 0.0;
	int numberAdvance = 0;
	int maxAdvance = 0.0;*/

	// Posicionamiento de la casa de campaña
	modelMatrixCasaCamp = glm::translate(modelMatrixCasaCamp, glm::vec3(-3.0, 0.0, 2.0));

	// Posicionamiento del personaje principal
	modelMatrixCazador = glm::translate(modelMatrixCazador, glm::vec3(0.0f, 0.5f, 0.0f));

	// modelMatrixHeli = glm::translate(modelMatrixHeli, glm::vec3(5.0, 10.0, -5.0));

	// modelMatrixAircraft = glm::translate(modelMatrixAircraft, glm::vec3(10.0, 2.0, -17.5));

	// modelMatrixLambo = glm::translate(modelMatrixLambo, glm::vec3(23.0, 0.0, 0.0));

	// modelMatrixDart = glm::translate(modelMatrixDart, glm::vec3(3.0, 0.0, 20.0));

	// modelMatrixBuzz = glm::translate(modelMatrixBuzz, glm::vec3(15.0, 0.0, -10.0));

	// modelMatrixCowboy = glm::translate(modelMatrixCowboy, glm::vec3(13.0, 0.05, 0.0));

	// modelMatrixGuardian = glm::translate(modelMatrixGuardian, glm::vec3(15, 0.05, 0.0));
	// modelMatrixGuardian = glm::rotate(modelMatrixGuardian, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));

	// modelMatrixCyborg = glm::translate(modelMatrixCyborg, glm::vec3(5.0f, 0.05, 0.0f));

	// Variables to interpolation key frames
	/*fileName = "../animaciones/animation_dart_joints.txt";
	keyFramesDartJoints = getKeyRotFrames(fileName);
	keyFramesDart = getKeyFrames("../animaciones/animation_dart.txt");
	keyFramesBuzzJoints = getKeyRotFrames("../animaciones/animation_buzz_joints.txt");
	keyFramesBuzz = getKeyFrames("../animaciones/animation_buzz.txt");*/

	lastTime = TimeManager::Instance().GetTime();

	while (psi)
	{
		currTime = TimeManager::Instance().GetTime();
		if (currTime - lastTime < 0.016666667)
		{
			glfwPollEvents();
			continue;
		}
		lastTime = currTime;
		TimeManager::Instance().CalculateFrameRate(true);
		deltaTime = TimeManager::Instance().DeltaTime;
		psi = processInput(true);
		std::map<std::string, bool> collisionDetection;

		// Variables donde se guardan las matrices de cada articulacion por 1 frame
		std::vector<float> matrixDartJoints;
		std::vector<glm::mat4> matrixDart;
		std::vector<float> matrixBuzzJoints;
		std::vector<glm::mat4> matrixBuzz;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
												(float)screenWidth / (float)screenHeight, 0.01f, 100.0f);

		/*if(modelSelected == 1){
			axis = glm::axis(glm::quat_cast(modelMatrixDart));
			angleTarget = glm::angle(glm::quat_cast(modelMatrixDart));
			target = modelMatrixDart[3];
		}
		else{
			axis = glm::axis(glm::quat_cast(modelMatrixMayow));
			angleTarget = glm::angle(glm::quat_cast(modelMatrixMayow));
			target = modelMatrixMayow[3];
		}*/

		// seguimiento de la camara en tercera persona al personaje principal
		if (isFirstPerson) {
			renderCrosshair();
			// Obtener la posición base del cazador
			glm::vec3 position = glm::vec3(modelMatrixCazador[3]);
			position.y += 2.0f; // Altura de los ojos
			
			// Ajustar el vector de dirección
			glm::vec3 forward = glm::normalize(glm::vec3(modelMatrixCazador[2])); // Agregamos el negativo de nuevo
			glm::vec3 target = position + (forward * 0.40f) ; // El target debe estar adelante de la posición
			
			// Configurar la cámara en primera persona
			camera->setPosition(position);
			camera->setCameraTarget(target); // Miramos hacia el punto adelante
			camera->setDistanceFromTarget(0.1f);
			
			// Ajustar el ángulo para que coincida con la dirección de vista
			glm::vec3 axis = glm::axis(glm::quat_cast(modelMatrixCazador));
			float angleTarget = glm::angle(glm::quat_cast(modelMatrixCazador));
			if (std::isnan(angleTarget))
				angleTarget = 0.0;
			if (axis.y < 0)
				angleTarget = -angleTarget;
			//angleTarget += glm::radians(180.0f); // Agregar rotación de 180 grados
			float upwardRotation = 0.0f; // Ajusta este valor según necesites
    		angleTarget += glm::radians(upwardRotation);
			camera->setAngleTarget(angleTarget);
		} else {
			// Código original para la cámara en tercera persona
			axis = glm::axis(glm::quat_cast(modelMatrixCazador));
			angleTarget = glm::angle(glm::quat_cast(modelMatrixCazador));
			target = modelMatrixCazador[3];

			if (std::isnan(angleTarget))
				angleTarget = 0.0;
			if (axis.y < 0)
				angleTarget = -angleTarget;
			if (modelSelected == 1)
				angleTarget -= glm::radians(90.0f);
			camera->setCameraTarget(target);
			camera->setAngleTarget(angleTarget);
		}

		camera->updateCamera();
		glm::mat4 view = camera->getViewMatrix();

		// Settea la matriz de vista y projection al shader con solo color
		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con skybox
		shaderSkybox.setMatrix4("projection", 1, false,
								glm::value_ptr(projection));
		shaderSkybox.setMatrix4("view", 1, false,
								glm::value_ptr(glm::mat4(glm::mat3(view))));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderMulLighting.setMatrix4("projection", 1, false,
									 glm::value_ptr(projection));
		shaderMulLighting.setMatrix4("view", 1, false,
									 glm::value_ptr(view));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderTerrain.setMatrix4("projection", 1, false,
								 glm::value_ptr(projection));
		shaderTerrain.setMatrix4("view", 1, false,
								 glm::value_ptr(view));

		/*******************************************
		 * Propiedades Luz direccional
		 *******************************************/
		shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(colorAmbiente));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(colorDifuso));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(colorEspecular));
		shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(direccionLuz));

		shaderTerrain.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderTerrain.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(colorAmbiente));
		shaderTerrain.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(colorDifuso));
		shaderTerrain.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(colorEspecular));
		shaderTerrain.setVectorFloat3("directionalLight.direction", glm::value_ptr(direccionLuz));

		shaderSkybox.setVectorFloat3("light.ambient", glm::value_ptr(colorAmbiente));

		/*******************************************
		 * Propiedades SpotLights
		 *******************************************/
	
		// Linterna del personaje principal
		if (isLampON) {
			shaderMulLighting.setInt("spotLightCount", 1);
			shaderTerrain.setInt("spotLightCount", 1);

			glm::vec3 spotPosition = glm::vec3(modelMatrixCazador * glm::vec4(0, 0.5, 1, 1.0));
			shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
			shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.8)));
			shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.8)));
			shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(spotPosition));
			shaderMulLighting.setVectorFloat3("spotLights[0].direction", value_ptr(modelMatrixCazador[2]));
			shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
			shaderMulLighting.setFloat("spotLights[0].linear", 0.07);
			shaderMulLighting.setFloat("spotLights[0].quadratic", 0.03);
			shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(14.0f)));
			shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0f)));

			shaderTerrain.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
			shaderTerrain.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.8)));
			shaderTerrain.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.8)));
			shaderTerrain.setVectorFloat3("spotLights[0].position", glm::value_ptr(spotPosition));
			shaderTerrain.setVectorFloat3("spotLights[0].direction", glm::value_ptr(modelMatrixCazador[2]));
			shaderTerrain.setFloat("spotLights[0].constant", 1.0);
			shaderTerrain.setFloat("spotLights[0].linear", 0.07);
			shaderTerrain.setFloat("spotLights[0].quadratic", 0.03);
			shaderTerrain.setFloat("spotLights[0].cutOff", cos(glm::radians(14.0f)));
			shaderTerrain.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0f)));
		} else {
			shaderMulLighting.setInt("spotLightCount", 0);
			shaderTerrain.setInt("spotLightCount", 0);
		}

		/*******************************************
		 * Propiedades PointLights
		 *******************************************/
		/*shaderMulLighting.setInt("pointLightCount", lamp1Position.size() + lamp2Position.size());
		shaderTerrain.setInt("pointLightCount", lamp1Position.size() + lamp2Position.size());
		for(int i = 0; i < lamp1Position.size(); i++){
			glm::mat4 matrixAdjustLamp = glm::mat4(1.0);
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp1Position[i]);
			matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp1Orientation[i]), glm::vec3(0, 1, 0));
			matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(0.5));
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0.0, 10.35, 0));
			glm::vec3 lampPosition = glm::vec3(matrixAdjustLamp[3]);
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.02);
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.02);
		}
		for(int i = 0; i < lamp2Position.size(); i++){
			glm::mat4 matrixAdjustLamp = glm::mat4(1.0);
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp2Position[i]);
			matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp2Orientation[i]), glm::vec3(0, 1, 0));
			matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(1.0));
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0.75, 5.0, 0));
			glm::vec3 lampPosition = glm::vec3(matrixAdjustLamp[3]);
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].position", glm::value_ptr(lampPosition));
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].constant", 1.0);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].linear", 0.09);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].quadratic", 0.02);
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].position", glm::value_ptr(lampPosition));
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].constant", 1.0);
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].linear", 0.09);
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].quadratic", 0.02);
		}*/

		/*******************************************
		 * Terrain
		 *******************************************/
		// Se activa la textura de hojas
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureLeavesID);
		shaderTerrain.setInt("backgroundTexture", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
		shaderTerrain.setInt("rTexture", 1);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
		shaderTerrain.setInt("gTexture", 2);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, textureTerrainBID);
		shaderTerrain.setInt("bTexture", 3);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);
		shaderTerrain.setInt("blendMapTexture", 4);
		shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(80, 80)));
		// Posicionamiento del terreno
		terrain.setPosition(glm::vec3(TERRAIN_SIZE / 2, 0, TERRAIN_SIZE / 2));
		terrain.render();
		shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(0, 0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		/*******************************************
		 * Custom objects obj
		 *******************************************/
		// Renderizado de la casa de campaña
		modelMatrixCasaCamp[3][1] = terrain.getHeightTerrain(modelMatrixCasaCamp[3][0], modelMatrixCasaCamp[3][2]);
		modelCasaCamp.render(modelMatrixCasaCamp);
		// Forze to enable the unit texture to 0 always ----------------- IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		// Renderizado de arboles tipo 1
		for (int i = 0; i < arbol1Position.size(); i++)
		{
			arbol1Position[i].y = terrain.getHeightTerrain(arbol1Position[i].x, arbol1Position[i].z);
			modelArbol1.setPosition(arbol1Position[i]);
			// modelArbol1.setOrientation(glm::vec3(0, 0, 0));
			modelArbol1.render();
		}

		// Renderizado de arboles tipo 2
		/*for (int i = 0; i < arbol2Position.size(); i++)
		{
			arbol2Position[i].y = terrain.getHeightTerrain(arbol2Position[i].x, arbol2Position[i].z);
			modelArbol2.setPosition(arbol2Position[i]);
			modelArbol2.render();
		}*/

		// Renderizado de arboles otoño
		for (int i = 0; i < arbolOtonoPosition.size(); i++){
			arbolOtonoPosition[i].y = terrain.getHeightTerrain(arbolOtonoPosition[i].x, arbolOtonoPosition[i].z);
			modelArbolOtono.setPosition(arbolOtonoPosition[i]);
			modelArbolOtono.render();
		}

		// Renderizado de plantas acuaticas
		for (int i = 0; i < plantaPosition.size(); i++){
			plantaPosition[i].y = terrain.getHeightTerrain(plantaPosition[i].x, plantaPosition[i].z);
			modelPlanta.setPosition(plantaPosition[i]);
			modelPlanta.render();
		}

		// Renderizado de yerbas
		for (int i = 0; i < yerbaPosition.size(); i++){
			yerbaPosition[i].y = terrain.getHeightTerrain(yerbaPosition[i].x, yerbaPosition[i].z);
			modelYerba.setPosition(yerbaPosition[i]);
			modelYerba.render();
		}

		// Renderizado de troncos
		for (int i = 0; i < troncoPosition.size(); i++){
			troncoPosition[i].y = terrain.getHeightTerrain(troncoPosition[i].x, troncoPosition[i].z);
			modelTronco.setPosition(troncoPosition[i]);
			modelTronco.setOrientation(glm::vec3(0, troncoOrientation[i], 0));
			modelTronco.render();
		}

		/*****************************************
		 * Objetos animados por huesos
		 * **************************************/
		// Personaje principal
		/*glm::vec3 ejey = glm::normalize(terrain.getNormalTerrain(modelMatrixCazador[3][0], modelMatrixCazador[3][2]));
		glm::vec3 ejex = glm::vec3(modelMatrixCazador[0]);
		glm::vec3 ejez = glm::normalize(glm::cross(ejex, ejey));
		ejex = glm::normalize(glm::cross(ejey, ejez));
		modelMatrixCazador[0] = glm::vec4(ejex, 0.0);
		modelMatrixCazador[1] = glm::vec4(ejey, 0.0);
		modelMatrixCazador[2] = glm::vec4(ejez, 0.0);*/
		modelMatrixCazador[3][1] = -GRAVITY * tmv * tmv + 3.0 * tmv +
								 terrain.getHeightTerrain(modelMatrixCazador[3][0], modelMatrixCazador[3][2]);
		tmv = currTime - startTimeJump; // Incrementa el tmv desde que inicio.
		if (modelMatrixCazador[3][1] < terrain.getHeightTerrain(modelMatrixCazador[3][0], modelMatrixCazador[3][2]))
		{
			isJump = false;
			modelMatrixCazador[3][1] = terrain.getHeightTerrain(
				modelMatrixCazador[3][0], modelMatrixCazador[3][2]);
		}
		modelMatrixCazador[3][1] = terrain.getHeightTerrain(modelMatrixCazador[3][0], modelMatrixCazador[3][2]);
		glm::mat4 modelMatrixCazadorBody = glm::mat4(modelMatrixCazador);
		modelMatrixCazadorBody = glm::scale(modelMatrixCazadorBody, glm::vec3(0.1f));
		modelCazador.setAnimationIndex(animationIndexCazador);
		modelCazador.render(modelMatrixCazadorBody);
		animationIndexCazador = 1;

		float gunOffsetX = 0.12f;    // Ajuste lateral
		float gunOffsetY = 1.5f;     // Ajuste de altura
		float gunOffsetZ = 0.2f;     // Ajuste frontal
		float gunRotateY = 90.0f;    // Rotación horizontal
		float gunRotateX = -15.0f;   // Inclinación
		float gunScale = 0.02f;      // Escala
		/*
		glm::mat4 modelMatrixGun = glm::mat4(modelMatrixCazador);
		modelMatrixGun = glm::translate(modelMatrixGun, glm::vec3(gunOffsetX, gunOffsetY, gunOffsetZ));
		modelMatrixGun = glm::rotate(modelMatrixGun, glm::radians(gunRotateY), glm::vec3(0, 1, 0));
		modelMatrixGun = glm::rotate(modelMatrixGun, glm::radians(gunRotateX), glm::vec3(1, 0, 0));
		modelMatrixGun = glm::scale(modelMatrixGun, glm::vec3(gunScale));

		//modelGun.render(modelMatrixGun);
		/*modelMatrixCowboy[3][1] = terrain.getHeightTerrain(modelMatrixCowboy[3][0], modelMatrixCowboy[3][2]);
		glm::mat4 modelMatrixCowboyBody = glm::mat4(modelMatrixCowboy);
		modelMatrixCowboyBody = glm::scale(modelMatrixCowboyBody, glm::vec3(0.0021f));
		cowboyModelAnimate.render(modelMatrixCowboyBody);*/

		/*modelMatrixGuardian[3][1] = terrain.getHeightTerrain(modelMatrixGuardian[3][0], modelMatrixGuardian[3][2]);
		glm::mat4 modelMatrixGuardianBody = glm::mat4(modelMatrixGuardian);
		modelMatrixGuardianBody = glm::scale(modelMatrixGuardianBody, glm::vec3(0.04f));
		guardianModelAnimate.render(modelMatrixGuardianBody);*/

		/*modelMatrixCyborg[3][1] = terrain.getHeightTerrain(modelMatrixCyborg[3][0], modelMatrixCyborg[3][2]);
		glm::mat4 modelMatrixCyborgBody = glm::mat4(modelMatrixCyborg);
		modelMatrixCyborgBody = glm::scale(modelMatrixCyborgBody, glm::vec3(0.009f));
		cyborgModelAnimate.setAnimationIndex(1);
		cyborgModelAnimate.render(modelMatrixCyborgBody);*/

		/*******************************************
		 * Skybox
		 *******************************************/
		GLint oldCullFaceMode;
		GLint oldDepthFuncMode;
		// deshabilita el modo del recorte de caras ocultas para ver las esfera desde adentro
		glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
		glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
		shaderSkybox.setFloat("skybox", 0);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);
		glActiveTexture(GL_TEXTURE0);
		skyboxSphere.render();
		glCullFace(oldCullFaceMode);
		glDepthFunc(oldDepthFuncMode);

		// Creación de los colliders ========================================

		// Colliders de la casa de campaña
		glm::mat4 colliderMatrixCasaCamp = glm::mat4(modelMatrixCasaCamp);
		colliderMatrixCasaCamp = glm::scale(colliderMatrixCasaCamp, glm::vec3(0.5));
		colliderMatrixCasaCamp = glm::translate(colliderMatrixCasaCamp, modelCasaCamp.getSbb().c);
		AbstractModel::SBB casaCampCollider;
		casaCampCollider.c = colliderMatrixCasaCamp[3];
		casaCampCollider.ratio = modelCasaCamp.getSbb().ratio * 0.8;
		addOrUpdateColliders(collidersSBB, "casa_camp", casaCampCollider, modelMatrixCasaCamp);

		// Collider del personaje principal
		glm::mat4 colliderMatrixCazador = glm::mat4(modelMatrixCazador);
		AbstractModel::OBB cazadorCollider;
		colliderMatrixCazador = glm::scale(colliderMatrixCazador, glm::vec3(0, 0.1, 0));
		colliderMatrixCazador = glm::translate(colliderMatrixCazador, modelCazador.getObb().c);
		cazadorCollider.u = glm::quat_cast(modelMatrixCazador);
		cazadorCollider.c = colliderMatrixCazador[3];
		cazadorCollider.e = modelCazador.getObb().e * glm::vec3(0.015,0.02,0.01);
		addOrUpdateColliders(collidersOBB, "cazador", cazadorCollider, modelMatrixCazador);

		/*glm::mat4 colliderMatrixAircraft = glm::mat4(modelMatrixAircraft);
		AbstractModel::OBB colliderAircraft;
		// Primero la inicialización de u antes de todo
		colliderAircraft.u = glm::quat_cast(colliderMatrixAircraft);
		colliderMatrixAircraft = glm::scale(colliderMatrixAircraft,
			glm::vec3(1.0));
		colliderMatrixAircraft = glm::translate(colliderMatrixAircraft,
			modelAircraft.getObb().c);
		colliderAircraft.c = colliderMatrixAircraft[3];
		colliderAircraft.e = modelAircraft.getObb().e * 1.0f;
		addOrUpdateColliders(collidersOBB, "aircraft", colliderAircraft,
			modelMatrixAircraft);*/

		// Colliders de arboles tipo 1
		for (int i = 0; i < arbol1Position.size(); i++)
		{
			AbstractModel::OBB arbol1Collider;
			glm::mat4 ColliderMatrixArbol1 = glm::mat4(1.0f);
			ColliderMatrixArbol1 = glm::translate(ColliderMatrixArbol1, arbol1Position[i]);
			arbol1Collider.u = glm::quat_cast(ColliderMatrixArbol1);
			ColliderMatrixArbol1 = glm::scale(ColliderMatrixArbol1, glm::vec3(1.0));
			ColliderMatrixArbol1 = glm::translate(ColliderMatrixArbol1, modelArbol1.getObb().c);
			arbol1Collider.c = ColliderMatrixArbol1[3];
			arbol1Collider.e = modelArbol1.getObb().e * glm::vec3(0.1, 1.0, 0.1);
			std::get<0>(collidersOBB.find("arbol_1-" + std::to_string(i))->second) = arbol1Collider;

			addOrUpdateColliders(collidersOBB, "arbol_1-" + std::to_string(i), arbol1Collider,
								 ColliderMatrixArbol1);
		}

		// Colliders de arboles tipo 2
		/*for (int i = 0; i < arbol2Position.size(); i++)
		{
			AbstractModel::OBB arbol2Collider;
			glm::mat4 ColliderMatrixArbol2 = glm::mat4(1.0f);
			ColliderMatrixArbol2 = glm::translate(ColliderMatrixArbol2, arbol2Position[i]);
			// modelColliderMatrix= glm::rotate(modelColliderMatrix, glm::radians(arbol1Orientation[i]), glm::vec3(0, 1, 0));
			
			arbol2Collider.u = glm::quat_cast(ColliderMatrixArbol2);
			ColliderMatrixArbol2 = glm::scale(ColliderMatrixArbol2, glm::vec3(1.0));
			ColliderMatrixArbol2 = glm::translate(ColliderMatrixArbol2, modelArbol2.getObb().c);
			arbol2Collider.c = ColliderMatrixArbol2[3];
			arbol2Collider.e = modelArbol2.getObb().e * glm::vec3(0.1, 1.0, 0.1);
			std::get<0>(collidersOBB.find("arbol_2-" + std::to_string(i))->second) = arbol2Collider;

			addOrUpdateColliders(collidersOBB, "arbol_2-" + std::to_string(i), arbol2Collider,
								 ColliderMatrixArbol2);
		}*/

		// Colliders de arboles otoño
		for (int i = 0; i < arbolOtonoPosition.size(); i++)
		{
			AbstractModel::OBB arbolOtonoCollider;
			glm::mat4 colliderMatrixArbolOt = glm::mat4(1.0f);
			colliderMatrixArbolOt = glm::translate(colliderMatrixArbolOt, arbolOtonoPosition[i]);
			
			arbolOtonoCollider.u = glm::quat_cast(colliderMatrixArbolOt);
			colliderMatrixArbolOt = glm::scale(colliderMatrixArbolOt, glm::vec3(1.0));
			colliderMatrixArbolOt = glm::translate(colliderMatrixArbolOt, modelArbolOtono.getObb().c);
			arbolOtonoCollider.c = colliderMatrixArbolOt[3];
			arbolOtonoCollider.e = modelArbolOtono.getObb().e * glm::vec3(0.1, 1.0, 0.1);
			std::get<0>(collidersOBB.find("arbol_otono-" + std::to_string(i))->second) = arbolOtonoCollider;

			addOrUpdateColliders(collidersOBB, "arbol_otono-" + std::to_string(i), arbolOtonoCollider,
								 colliderMatrixArbolOt);
		}

		// Colliders de troncos
		for (int i = 0; i < troncoPosition.size(); i++)
		{
			AbstractModel::OBB troncoCollider;
			glm::mat4 colliderMatrixTronco = glm::mat4(1.0f);
			colliderMatrixTronco = glm::translate(colliderMatrixTronco, troncoPosition[i]);
			colliderMatrixTronco = glm::rotate(colliderMatrixTronco, glm::radians(troncoOrientation[i]), glm::vec3(0, 1, 0));

			troncoCollider.u = glm::quat_cast(colliderMatrixTronco);
			colliderMatrixTronco = glm::scale(colliderMatrixTronco, glm::vec3(1.0));
			colliderMatrixTronco = glm::translate(colliderMatrixTronco, modelTronco.getObb().c);
			troncoCollider.c = colliderMatrixTronco[3];
			troncoCollider.e = modelTronco.getObb().e * glm::vec3(1.0);
			std::get<0>(collidersOBB.find("tronco-" + std::to_string(i))->second) = troncoCollider;

			addOrUpdateColliders(collidersOBB, "tronco-" + std::to_string(i), troncoCollider,
								 colliderMatrixTronco);
		}

		// Pruebas de colisión
		auto itOBBC = collidersOBB.begin();
		for (; itOBBC != collidersOBB.end(); itOBBC++)
		{
			bool isColision = false;
			auto jtOBBC = collidersOBB.begin();
			for (; jtOBBC != collidersOBB.end(); jtOBBC++)
			{
				if (itOBBC != jtOBBC &&
					testOBBOBB(std::get<0>(itOBBC->second), std::get<0>(jtOBBC->second)))
				{
					std::cout << "Hay colisión entre " << itOBBC->first << " y " << jtOBBC->first << std::endl;
					isColision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, itOBBC->first, isColision);
		}
		// OBBS VS SBB
		itOBBC = collidersOBB.begin();
		for (; itOBBC != collidersOBB.end(); itOBBC++)
		{
			auto itSBBC = collidersSBB.begin();
			bool isCollision = false;
			for (; itSBBC != collidersSBB.end(); itSBBC++)
			{
				if (testSphereOBox(std::get<0>(itSBBC->second), std::get<0>(itOBBC->second)))
				{
					std::cout << "Estan colisionando " << itSBBC->first << " y " << itOBBC->first << std::endl;
					isCollision = true;
					addOrUpdateCollisionDetection(collisionDetection, itSBBC->first, true);
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, itOBBC->first, isCollision);
		}
		// SBB vs SBB
		auto itSBBC = collidersSBB.begin();
		for (; itSBBC != collidersSBB.end(); itSBBC++)
		{
			auto jtSBBC = collidersSBB.end();
			bool isColision = false;
			for (; jtSBBC != collidersSBB.end(); jtSBBC++)
			{
				if (itSBBC != jtSBBC && testSphereSphereIntersection(
											std::get<0>(itSBBC->second), std::get<0>(jtSBBC->second)))
				{
					std::cout << "Colisonan de " << itSBBC->first << " y " << jtSBBC->first << std::endl;
					isColision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, itSBBC->first, isColision);
		}
		auto itCollision = collisionDetection.begin();
		for (; itCollision != collisionDetection.end(); itCollision++)
		{
			auto sbbBuscado = collidersSBB.find(itCollision->first);
			auto obbBuscado = collidersOBB.find(itCollision->first);
			if (sbbBuscado != collidersSBB.end())
			{ // Encontrado
				if (!itCollision->second)
					addOrUpdateColliders(collidersSBB, itCollision->first);
			}
			if (obbBuscado != collidersOBB.end())
			{ // Encontrado en las OBBS
				if (!itCollision->second)
					addOrUpdateColliders(collidersOBB, itCollision->first);
				else
				{
					if (itCollision->first.compare("cazador") == 0)
					{
						modelMatrixCazador = std::get<1>(obbBuscado->second);
					}
				}
			}
		}
		// Colision entre rayos
		glm::mat4 modelMatrixRay = glm::mat4(modelMatrixCazador);
		modelMatrixRay = glm::translate(modelMatrixRay, glm::vec3(0, 1.2, 0));
		float maxDistance = 10.0f;
		glm::vec3 rayDirection = modelMatrixRay[2];
		glm::vec3 origen = modelMatrixRay[3];
		glm::vec3 rmd = origen + rayDirection * maxDistance / 2.0f; // Un cilindro
		glm::vec3 target = origen + rayDirection * maxDistance;
		modelMatrixRay[3] = glm::vec4(rmd, 1.0);
		modelMatrixRay = glm::rotate(modelMatrixRay, glm::radians(90.0f), glm::vec3(1, 0, 0));
		modelMatrixRay = glm::scale(modelMatrixRay, glm::vec3(0.03, maxDistance, 0.03));
		if (isCollidersVisible) {
			modeloRayo.render(modelMatrixRay);
		}

		itSBBC = collidersSBB.begin();
		for (; itSBBC != collidersSBB.end(); itSBBC++)
		{
			float t;
			if (raySphereIntersect(origen, target,
								   rayDirection, std::get<0>(itSBBC->second), t))
			{
				std::cout << "Colision rato y el modelo " << itSBBC->first << std::endl;
			}
		}

		itOBBC = collidersOBB.begin();
		for (; itOBBC != collidersOBB.end(); itOBBC++)
		{
			if (testRayOBB(origen, target, std::get<0>(itOBBC->second)))
				std::cout << "Hay collision entre el rayo y el modelo " << itOBBC->first << std::endl;
		}

		// Picking para seleccionar objeto
		glm::vec3 o = glm::unProject(
			glm::vec3(lastMousePosX, screenHeight - lastMousePosY, 0.0f),
			view, projection, glm::vec4(0.0, 0.0, screenWidth, screenHeight));
		glm::vec3 t = glm::unProject(
			glm::vec3(lastMousePosX, screenHeight - lastMousePosY, 1.0f),
			view, projection, glm::vec4(0.0, 0.0, screenWidth, screenHeight));
		glm::vec3 d = glm::normalize(t - o);
		itSBBC = collidersSBB.begin();
		for (; itSBBC != collidersSBB.end(); itSBBC++)
		{
			float tInt;
			if (raySphereIntersect(o, t,
								   d, std::get<0>(itSBBC->second), tInt))
			{
				std::cout << "Selecciono el modelo " << itSBBC->first << std::endl;
			}
		}
		itOBBC = collidersOBB.begin();
		for (; itOBBC != collidersOBB.end(); itOBBC++)
		{
			if (testRayOBB(o, t, std::get<0>(itOBBC->second)))
				std::cout << "Seleccionado el modelo " << itOBBC->first << std::endl;
		}

		// Para visualizar los colliders.
		auto it = collidersSBB.begin();
		for (; it != collidersSBB.end(); it++)
		{
			glm::mat4 matrixCollider = glm::mat4(1.0);
			AbstractModel::SBB collider = std::get<0>(it->second);
			matrixCollider = glm::translate(matrixCollider,
											collider.c);
			matrixCollider = glm::scale(matrixCollider, glm::vec3(collider.ratio * 2.0f));
			if (isCollidersVisible){
				modelEsfereCollider.enableWireMode();
				modelEsfereCollider.render(matrixCollider);
			}
		}
		auto itObb = collidersOBB.begin();
		for (; itObb != collidersOBB.end(); itObb++)
		{
			AbstractModel::OBB collider = std::get<0>(itObb->second);
			glm::mat4 matrixCollider = glm::translate(glm::mat4(1.0), collider.c);
			matrixCollider = matrixCollider * glm::mat4(collider.u);
			matrixCollider = glm::scale(matrixCollider, collider.e * 2.0f);
			if (isCollidersVisible)
			{
				boxCollider.enableWireMode();
				boxCollider.render(matrixCollider);
			}
		}

		// Animaciones por keyframes dart Vader
		// Para salvar los keyframes
		/*if(record && modelSelected == 1){
			matrixDartJoints.push_back(rotDartHead);
			matrixDartJoints.push_back(rotDartLeftArm);
			matrixDartJoints.push_back(rotDartLeftHand);
			matrixDartJoints.push_back(rotDartRightArm);
			matrixDartJoints.push_back(rotDartRightHand);
			matrixDartJoints.push_back(rotDartLeftLeg);
			matrixDartJoints.push_back(rotDartRightLeg);
			if(saveFrame){
				saveFrame = false;
				appendFrame(myfile, matrixDartJoints);
			}
		}
		else if(keyFramesDartJoints.size() > 0){
			// Para reproducir el frame
			interpolationDartJoints = numPasosDartJoints / (float) maxNumPasosDartJoints;
			numPasosDartJoints++;
			if(interpolationDartJoints > 1.0){
				interpolationDartJoints = 0;
				numPasosDartJoints = 0;
				indexFrameDartJoints = indexFrameDartJointsNext;
				indexFrameDartJointsNext++;
			}
			if(indexFrameDartJointsNext > keyFramesDartJoints.size() -1)
				indexFrameDartJointsNext = 0;
			rotDartHead = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 0, interpolationDartJoints);
			rotDartLeftArm = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 1, interpolationDartJoints);
			rotDartLeftHand = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 2, interpolationDartJoints);
			rotDartRightArm = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 3, interpolationDartJoints);
			rotDartRightHand = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 4, interpolationDartJoints);
			rotDartLeftLeg = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 5, interpolationDartJoints);
			rotDartRightLeg = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 6, interpolationDartJoints);
		}
		if(record && modelSelected == 2){
			matrixDart.push_back(modelMatrixDart);
			if(saveFrame){
				saveFrame = false;
				appendFrame(myfile, matrixDart);
			}
		}
		else if(keyFramesDart.size() > 0){
			interpolationDart = numPasosDart / (float) maxNumPasosDart;
			numPasosDart++;
			if(interpolationDart > 1.0){
				numPasosDart = 0;
				interpolationDart = 0;
				indexFrameDart = indexFrameDartNext;
				indexFrameDartNext++;
			}
			if(indexFrameDartNext > keyFramesDart.size() - 1)
				indexFrameDartNext = 0;
			modelMatrixDart = interpolate(keyFramesDart, indexFrameDart, indexFrameDartNext, 0, interpolationDart);
		}*/
		// Animaciones por keyframes buzz
		// Para salvar los keyframes
		/*if(record && modelSelected == 3){
			matrixBuzzJoints.push_back(rotBuzzHead);
			matrixBuzzJoints.push_back(rotBuzzLeftarm);
			matrixBuzzJoints.push_back(rotBuzzLeftForeArm);
			matrixBuzzJoints.push_back(rotBuzzLeftHand);
			if(saveFrame){
				saveFrame = false;
				appendFrame(myfile, matrixBuzzJoints);
			}
		}
		else if(keyFramesBuzzJoints.size() > 0){
			// Para reproducir el frame
			interpolationBuzzJoints = numPasosBuzzJoints / (float) maxNumPasosBuzzJoints;
			numPasosBuzzJoints++;
			if(interpolationBuzzJoints > 1.0){
				interpolationBuzzJoints = 0;
				numPasosBuzzJoints = 0;
				indexFrameBuzzJoints = indexFrameBuzzJointsNext;
				indexFrameBuzzJointsNext++;
			}
			if(indexFrameBuzzJointsNext > keyFramesBuzzJoints.size() -1)
				indexFrameBuzzJointsNext = 0;
			rotBuzzHead = interpolate(keyFramesBuzzJoints, indexFrameBuzzJoints, indexFrameBuzzJointsNext, 0, interpolationBuzzJoints);
			rotBuzzLeftarm = interpolate(keyFramesBuzzJoints, indexFrameBuzzJoints, indexFrameBuzzJointsNext, 1, interpolationBuzzJoints);
			rotBuzzLeftForeArm = interpolate(keyFramesBuzzJoints, indexFrameBuzzJoints, indexFrameBuzzJointsNext, 2, interpolationBuzzJoints);
			rotBuzzLeftHand = interpolate(keyFramesBuzzJoints, indexFrameBuzzJoints, indexFrameBuzzJointsNext, 3, interpolationBuzzJoints);
		}
		if(record && modelSelected == 4){
			matrixBuzz.push_back(modelMatrixBuzz);
			if(saveFrame){
				saveFrame = false;
				appendFrame(myfile, matrixBuzz);
			}
		}
		else if(keyFramesBuzz.size() > 0){
			interpolationBuzz = numPasosBuzz / (float) maxNumPasosBuzz;
			numPasosBuzz++;
			if(interpolationBuzz > 1.0){
				numPasosBuzz = 0;
				interpolationBuzz = 0;
				indexFrameBuzz = indexFrameBuzzNext;
				indexFrameBuzzNext++;
			}
			if(indexFrameBuzzNext > keyFramesBuzz.size() - 1)
				indexFrameBuzzNext = 0;
			modelMatrixBuzz = interpolate(keyFramesBuzz, indexFrameBuzz, indexFrameBuzzNext, 0, interpolationBuzz);
		}*/

		/**********Maquinas de estado*************/
		// Maquina de estados para el carro eclipse
		/*switch (state){
		case 0:
			if(numberAdvance == 0)
				maxAdvance = 65.0;
			else if(numberAdvance == 1)
				maxAdvance = 49.0;
			else if(numberAdvance == 2)
				maxAdvance = 44.5;
			else if(numberAdvance == 3)
				maxAdvance = 49.0;
			else if(numberAdvance == 4)
				maxAdvance = 44.5;
			state = 1;
			break;
		case 1:
			modelMatrixEclipse = glm::translate(modelMatrixEclipse, glm::vec3(0.0f, 0.0f, avance));
			advanceCount += avance;
			rotWheelsX += 0.05;
			rotWheelsY -= 0.02;
			if(rotWheelsY < 0)
				rotWheelsY = 0;
			if(advanceCount > maxAdvance){
				advanceCount = 0;
				numberAdvance++;
				state = 2;
			}
			break;
		case 2:
			modelMatrixEclipse = glm::translate(modelMatrixEclipse, glm::vec3(0.0, 0.0, 0.025f));
			modelMatrixEclipse = glm::rotate(modelMatrixEclipse, glm::radians(giroEclipse), glm::vec3(0, 1, 0));
			rotCount += giroEclipse;
			rotWheelsX += 0.05;
			rotWheelsY += 0.02;
			if(rotWheelsY > 0.25)
				rotWheelsY = 0.25;
			if(rotCount >= 90.0f){
				rotCount = 0;
				state = 0;
				if(numberAdvance > 4)
					numberAdvance = 1;
			}
			break;

		default:
			break;
		}

		// Maquina de estado de lambo
		switch (stateDoor)
		{
		case 0:
			dorRotCount += 0.5;
			if(dorRotCount > 75)
				stateDoor = 1;
			break;
		case 1:
			dorRotCount -= 0.5;
			if(dorRotCount < 0){
				dorRotCount = 0.0;
				stateDoor = 0;
			}

		default:
			break;
		}*/

		// Constantes de animaciones
		// rotHelHelY += 0.5;
		// rotHelHelBack += 0.5;

		if (isFirstPerson) {
			renderCrosshair();
		}

		glfwSwapBuffers(window);
	}
}

int main(int argc, char **argv)
{
	init(1000, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}