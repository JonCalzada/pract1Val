/*---------------------------------------------------------*/
/* ----------------   Práctica 2 --------------------------*/
/*-----------------    2023-2   ---------------------------*/
/*------------- (Nombre del alumno: DEL VALLE ARAGON ALEXIS RAFAEL ) ---------------*/
#include <glew.h>
#include <glfw3.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow* window);

// settings
// Window size
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

GLFWmonitor* monitors;
GLuint VBO[2], VAO[2], EBO[2];
GLuint shaderProgramYellow, shaderProgramColor;

// Layoyt - Locacion 0 en tres vectores con nombre aPos
// Layout para color de vertices
//out vec3 ourColor -Salida para sacar el color
//ourColor=aColor -La salida sera igual a los colores de entrada
static const char* myVertexShader = "										\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
layout (location = 1) in vec3 aColor;										\n\
out vec3 ourColor;															\n\
																			\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);						\n\
	ourColor= aColor;		\n\
}";

static const char* myVertexShaderColor = "									\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
layout (location = 1) in vec3 aColor;										\n\
out vec3 ourColor;															\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos, 1.0);											\n\
	ourColor = aColor;														\n\
}";

// Fragment Shader Color de la figura RGB escala 0-1 "finalColor=vec3(Rf,Gf,Bf)
static const char* myFragmentShaderYellow = "									\n\
#version 330																\n\
in vec3 ourColor;															\n\
out vec3 finalColor;														\n\
																			\n\
void main()																	\n\
{																			\n\
    finalColor = vec3(ourColor.x, ourColor.y, ourColor.z);									\n\
}";

static const char* myFragmentShaderColor = "								\n\
#version 330 core															\n\
out vec4 FragColor;															\n\
in vec3 ourColor;															\n\
																			\n\
void main()																	\n\
{																			\n\
	FragColor = vec4(ourColor, 1.0f);										\n\
}";

void myData(void);
void setupShaders(void);
void display(void);
void getResolution(void);


void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{
	float vertices[] =
	{
		// Posicion de vertices		//  Color
		//1
		0.48f,  0.66f, 0.0f,	0.47f, 0.69f, 0.26f,	//0	
		0.43f,  0.5f, 0.0f,		0.98f, 0.44f, 0.35f,	//1	
		0.13f,  0.33f, 0.0f,	0.22f, 0.69f, 0.88f,	//2
		0.26f,  0.33f, 0.0f,	0.11f, 0.5333f, 0.72f,	//3	

		//2
		0.48f,  0.66f, 0.0f,	0.789f, 0.653f, 0.48f,	//4
		0.43f,  0.5f, 0.0f,		0.05f, 0.105f, 0.369f,	//5
		0.5f,  0.275f, 0.0f,	0.035f, 0.330f, 0.450f,	//6
		0.45f,  0.285f, 0.0f,	0.57f, 0.33f, 0.72f,	//7	

		//3
		0.45f,  0.285f, 0.0f,	0.56f, 0.78f, 0.99f,	//8
		0.5f,  0.275f, 0.0f,	0.0f, 0.98f, 1.0f,		//9
		0.45f,  0.175f, 0.0f,	0.57f, 0.569f, 0.998,	//10	
		0.52f,  0.03f, 0.0f,	0.546f, 1.0f, 1.0f,		//11

		//4
		0.0f,  0.33f, 0.0f,		0.63f, 0.789f, 1.0f,	//12
		0.26f,  0.33f, 0.0f,	1.0f, 0.456f, 0.887f,	//13
		0.45f,  0.175f, 0.0f,	0.369f, 0.12f, 0.77f,	//14

		//5
		0.0f,  0.33f, 0.0f,		0.478f, 0.99f, 0.63f,	//15
		0.0f,  0.115f, 0.0f,	0.26f, 0.78f, 0.478f,	//16
		0.45f,  0.175f, 0.0f,	0.36f, 0.78f, 0.96f,	//17
		0.2f,  0.03f, 0.0f,		0.987f, 0.789f, 0.52f,	//18

		//6
		0.45f,  0.175f, 0.0f,	0.63f, 0.159f, 0.951f,	//19
		0.52f,  0.03f, 0.0f,	0.78f, 0.45f, 0.78f,	//20
		0.2f,  0.03f, 0.0f,		0.74f, 0.896f, 0.123f,	//21
		0.28f,  -0.1f, 0.0f,	0.54f, 0.741f, 0.658f,	//22	
		0.15f,  -0.13f, 0.0f,	0.698f, 0.4f, 1.0f,		//23	

		//7
		0.52f,  0.03f, 0.0f,	0.120f, 0.630f, 0.780f,	//24
		0.28f,  -0.1f, 0.0f,	0.54f, 0.741f, 0.658f,	//25
		0.53f,  -0.27f, 0.0f,	0.49f, 0.43f, 0.82f,	//26

		//8
		0.28f,  -0.1f, 0.0f,	0.74f, 0.258f, 0.963f,	//27
		0.53f,  -0.27f, 0.0f,	0.111f, 0.222f, 0.556f,	//28
		0.225f,  -0.19f, 0.0f,	0.555f, 0.666f, 0.999f,	//29	
		0.4f,  -0.42f, 0.0f,	0.74f, 0.56f, 0.777f,	//30

		//9
		0.225f,  -0.19f, 0.0f,	0.69f, 0.74f, 1.0f,		//31
		0.13f,  -0.22f, 0.0f,	569.54f, 1.0f, 1.0f,	//32
		0.4f,  -0.42f, 0.0f,	1.0f, 1.0f, 1.0f,		//33
		0.23f,  -0.55f, 0.0f,	0.47f, 0.56f, 0.569f,	//34

		//10
		0.0f,  0.115f, 0.0f,	1.0f, 1.0f, 0.458f,		//35
		0.2f,  0.03f, 0.0f,		1.0f, 0.88f, 0.66f,		//36
		0.0f,  0.0f, 0.0f,		1.0f, 1.0f, 1.0f,		//37
		0.13f,  -0.22f, 0.0f,	0.266f, 0.478f, 0.697f,		//38
		0.0f,  -0.53f, 0.0f,	0.35f, 0.78f, 0.569f,	//39
		0.08f,  -0.53f, 0.0f,	0.245f, 0.58f, 0.314f,	//40

		0.13f,  -0.22f, 0.0f,	0.756f, 0.359f, 1.0f,	//41
		0.08f,  -0.53f, 0.0f,	0.369f, 1.0f, 1.0f,		//42
		0.23f,  -0.55f, 0.0f,	0.24f, 0.78f, 0.356f,	//43
		0.1f,  -0.6f, 0.0f,		0.856f, 0.0f, 0.656f,	//44
		0.18f,  -0.68f, 0.0f,	1.0f, 1.0f, 0.0f,		//45
		0.0f,  -0.65f, 0.0f,	1.0f, 1.0f, 0.0f,		//46

		//11
		0.18f,  -0.68f, 0.0f,	0.0f, 1.0f, 0.0f,		//47	
		0.0f,  -0.64f, 0.0f,	0.78f, 0.366f, 0.0f,	//48
		0.0f,  -0.73f, 0.0f,	0.78f, 0.366f, 0.0f,	//49
		-0.18f,  -0.68f, 0.0f,	0.0f, 1.0f, 0.0f,		//50

		//12
		-0.0f,  0.115f, 0.0f,	1.0f, 1.0f, 0.458f,		//51
		-0.2f,  0.03f, 0.0f,	1.0f, 0.88f, 0.66f,		//52
		-0.0f,  0.0f, 0.0f,		1.0f, 1.0f, 1.0f,		//53
		-0.13f,  -0.22f, 0.0f,	0.266f, 0.478f, 0.697f,		//54
		-0.0f,  -0.53f, 0.0f,	0.35f, 0.78f, 0.569f,	//55
		-0.08f,  -0.53f, 0.0f,	0.245f, 0.58f, 0.314f,	//56

		-0.13f,  -0.22f, 0.0f,	0.756f, 0.359f, 1.0f,	//57
		-0.08f,  -0.53f, 0.0f,	0.369f, 1.0f, 1.0f,		//58
		-0.23f,  -0.55f, 0.0f,	0.24f, 0.78f, 0.356f,	//59
		-0.1f,  -0.6f, 0.0f,	0.856f, 0.0f, 0.656f,	//60
		-0.18f,  -0.68f, 0.0f,	1.0f, 1.0f, 0.0f,		//61
		-0.0f,  -0.65f, 0.0f,	1.0f, 1.0f, 0.0f,		//62

		//13
		-0.225f,  -0.19f, 0.0f,	0.69f, 0.74f, 1.0f,		//63
		-0.13f,  -0.22f, 0.0f,	569.54f, 1.0f, 1.0f,	//64
		-0.4f,  -0.42f, 0.0f,	1.0f, 1.0f, 1.0f,		//65
		-0.23f,  -0.55f, 0.0f,	0.47f, 0.56f, 0.569f,	//66

		//14
		-0.28f,  -0.1f, 0.0f,	0.54f, 0.741f, 0.658f,	//67
		-0.53f,  -0.27f, 0.0f,	0.111f, 0.222f, 0.556f,	//68
		-0.225f,  -0.19f, 0.0f,	0.555f, 0.666f, 0.999f,	//69	
		-0.4f,  -0.42f, 0.0f,	0.74f, 0.56f, 0.777f,	//70

		//15
		-0.52f, 0.03f, 0.0f,	 0.120f, 0.630f, 0.780f,	//71
		-0.28f, -0.1f, 0.0f,	 0.190f, 0.17f, 0.15f,		//72
		-0.53f, -0.27f, 0.0f,	0.49f, 0.43f, 0.82f,		//73

		//16
		-0.45f, 0.175f, 0.0f,	 0.63f, 0.159f, 0.951f,		//74
		-0.52f, 0.03f, 0.0f,	 0.78f, 0.45f, 0.78f,		//75
		-0.2f, 0.03f, 0.0f,		0.74f, 0.896f, 0.123f,		//76
		-0.28f, -0.1f, 0.0f,	 0.54f, 0.741f, 0.658f,		//77	
		-0.15f, -0.13f, 0.0f,	 0.698f, 0.4f, 1.0f,		//78		

		//17
		-0.0f, 0.33f, 0.0f,		0.478f, 0.99f, 0.63f,		//79
		-0.0f, 0.115f, 0.0f,	0.26f, 0.78f, 0.478f,		//80
		-0.45f, 0.175f, 0.0f,	 0.36f, 0.78f, 0.96f,		//81
		-0.2f, 0.03f, 0.0f,		0.987f, 0.789f, 0.52f,		//82

		//18
		-0.0f, 0.33f, 0.0f,		 0.63f, 0.789f, 1.0f,		//83
		-0.26f, 0.33f, 0.0f,	1.0f, 0.456f, 0.887f,		//84
		-0.45f, 0.175f, 0.0f,	0.369f, 0.12f, 0.77f,		//85

		//19
		-0.45f, 0.285f, 0.0f,	 0.56f, 0.78f, 0.99f,		//86
		-0.5f, 0.275f, 0.0f,	0.0f, 0.98f, 1.0f,			//87
		-0.45f, 0.175f, 0.0f,	0.57f, 0.569f, 0.998,		//88	
		-0.52f, 0.03f, 0.0f,	0.546f, 1.0f, 1.0f,			//89

		//20
		-0.48f, 0.66f, 0.0f,	0.789f, 0.653f, 0.48f,		//90
		-0.43f, 0.5f, 0.0f,		0.05f, 0.105f, 0.369f,		//91
		-0.5f, 0.275f, 0.0f,	 0.035f, 0.330f, 0.450f,	//92
		-0.45f, 0.285f, 0.0f,	0.57f, 0.33f, 0.72f,		//93

		//21
		-0.48f, 0.66f, 0.0f,	0.47f, 0.69f, 0.26f,		//94
		-0.43f, 0.5f, 0.0f,		0.98f, 0.44f, 0.35f,		//95
		-0.13f, 0.33f, 0.0f,	0.22f, 0.69f, 0.88f,		//96
		-0.26f, 0.33f, 0.0f,	0.11f, 0.5333f, 0.72f,		//97	
			////////////////////////////////////////////////////

		//Ojos
		0.28f, -0.1f, 0.0f,			0.54f, 0.0f, 0.0f,				//98 22	Ojo derecho
		0.15f, -0.13f, 0.0f,		 0.54f, 0.0f, 0.0f,				//99 23	Ojo derecho
		0.225f, -0.19f, 0.0f,		0.54f, 0.0f, 0.0f,				//100 29 Ojo derecho
		0.13f, -0.22f, 0.0f,		0.54f, 0.0f, 0.0f,				//101 32 Ojo derecho

		-0.13f, -0.22f, 0.0f,		0.54f, 0.0f, 0.0f,				//102 64 Ojo izquierdo
		-0.225f, -0.19f, 0.0f,		0.54f, 0.0f, 0.0f,				//103 69 Ojo izquierdo
		-0.28f, -0.1f, 0.0f,		0.54f, 0.0f, 0.0f,				//104 77 Ojo izquierdo
		-0.15f, -0.13f, 0.0f,		 0.54f, 0.0f, 0.0f,				//105 78 Ojo izquierdo

		//Oreja
		0.43f, 0.5f, 0.0f,		0.4157f, 0.5333f, 0.7294f,			//106 1	Oreja Derecha
		0.26f, 0.33f, 0.0f,		 0.4157f, 0.5333f, 0.7294f,			//107 3	Oreja Derecha
		0.45f, 0.285f, 0.0f,		0.4157f, 0.5333f, 0.7294f,		//108 7	Oreja Derecha
		0.45f, 0.175f, 0.0f,		0.4157f, 0.5333f, 0.7294f,		//109 10 Oreja Derecha

		-0.45f, 0.175f, 0.0f,		0.4157f, 0.5333f, 0.7294f,		//110 88 Oreja Izquierda
		-0.45f, 0.285f, 0.0f,		0.4157f, 0.5333f, 0.7294f,		//111 93 Oreja Izquierda
		-0.43f, 0.5f, 0.0f,			0.4157f, 0.5333f, 0.7294f,		//112 95 Oreja Izquierda
		-0.26f, 0.33f, 0.0f,		0.4157f, 0.5333f, 0.7294f,		//113 97 Oreja Izquierda

		//Nariz
		0.0f, -0.53f, 0.0f,		0.0f, 0.0f, 0.0f,		//114 39
		0.08f, -0.53f, 0.0f,	0.0f, 0.0f, 0.0f,		//115 40
		0.1f, -0.6f, 0.0f,		0.0f, 0.0f, 0.0f,		//116 44
		0.0f, -0.65f, 0.0f,		0.0f, 0.0f, 0.0f,		//117 46
		-0.08f, -0.53f, 0.0f,	0.0f, 0.0f, 0.0f,		//118 40
		-0.1f, -0.6f, 0.0f,		0.0f, 0.0f, 0.0f,		//119 44

	};

	//Arreglo de indices 
	unsigned int indices[] =
	{
		//Ojos
		98,99,100,101,	
		102,103,105,104,

		//Orejas
		106,107,108,109,
		110,111,113,112,
		
		//Nariz
		114,115,116,117,
		114,118,119,117,

		//Cara
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		13,12,16,18,14,
		19,20,21,22,23,
		34,32,31,25,24,26,
		35,36,37,38,39,40,
		41,42,43,44,45,46,
		47,48,49,50,
		51,52,53,54,55,56,
		57,58,59,60,61,62,
		66,64,69,67,71,73,
		74,75,76,77,78,
		84,79,80,82,85,
		86,87,88,89,
		90,91,92,93,
		94,95,96,97
	
	};

	//Datos en la memoria principal
	glGenVertexArrays(2, VAO);	//Crear contenedores de información reservando dentro de la memoria de video (2 contenedores, de nombre VAO)
	glGenBuffers(2, VBO);	//Creamos espacio para operaciones  (2 espacios, de nombre VBO)
	glGenBuffers(2, EBO);



	glBindVertexArray(VAO[0]); //Se manda a llamar el contenedor VAO que necesitamos(VAO 0)
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); //Activamos el buffer 0
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//Vaciado de informacion de (buffer, cantidad de vertices(sizeof-todo),vertices,...)
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	//Decimos a shader (entrada 0, tomas #datos, de tipo flotante, separación, posicion donde comienza a leer los datos )
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void setupShaders()
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &myVertexShader, NULL);
	glCompileShader(vertexShader);

	unsigned int vertexShaderColor = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderColor, 1, &myVertexShaderColor, NULL);
	glCompileShader(vertexShaderColor);

	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &myFragmentShaderYellow, NULL);
	glCompileShader(fragmentShaderYellow);

	unsigned int fragmentShaderColor = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderColor, 1, &myFragmentShaderColor, NULL);
	glCompileShader(fragmentShaderColor);


	//Crear el Programa que combina Geometr�a con Color
	shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	shaderProgramColor = glCreateProgram();
	glAttachShader(shaderProgramColor, vertexShaderColor);
	glAttachShader(shaderProgramColor, fragmentShaderColor);
	glLinkProgram(shaderProgramColor);
	//Check for errors 

	//ya con el Programa, el Shader no es necesario
	glDeleteShader(vertexShader);
	glDeleteShader(vertexShaderColor);
	glDeleteShader(fragmentShaderYellow);
	glDeleteShader(fragmentShaderColor);

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();  //Pregunta por el monitor principal
	getResolution();
	//						Crea una app	Ancho y altura de monitor				Monitor principal
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 1 Alex", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);	//Indica la posici�n de la ventana inicial "0" horizontal y desciende 30 pixeles 
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//My Functions
	//Setup Data to use
	myData();	//Mis datos 
	//To Setup Shaders
	setupShaders();

	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		my_input(window);

		// render
		// Background color
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);	//Color de fondo al lienzo de fondo RGB-A (alpha)
		glClear(GL_COLOR_BUFFER_BIT);

		//Display Section
		glUseProgram(shaderProgramYellow);

		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);

		glPointSize(10.0);	//Tama�o del punto multiplicado por 10
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0); //Para indices (tIPO DE FIGURA,CUANTOS VERTICES SE USARAN, ENTEROS SIN SIGNO, PRIMER VERTICE)
		glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_INT, (void*)(16*sizeof(float)));
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)(4 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)(8 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)(12 * sizeof(float)));

		glDrawElements(GL_TRIANGLE_STRIP, 12, GL_UNSIGNED_INT, (void*)(24 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(36 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(41 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(46 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (void*)(52 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (void*)(58 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)(64 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (void*)(68 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (void*)(74 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(80 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(86 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(91 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_STRIP, 12, GL_UNSIGNED_INT, (void*)(96 * sizeof(float)));




		

		/*glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 12, 3);
		glDrawArrays(GL_TRIANGLE_STRIP, 15, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 19, 5);
		glDrawArrays(GL_TRIANGLE_STRIP, 24, 3);
		glDrawArrays(GL_TRIANGLE_STRIP, 27, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 31, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 35, 6);
		glDrawArrays(GL_TRIANGLE_STRIP, 41, 6);
		glDrawArrays(GL_TRIANGLE_STRIP, 47, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 51, 6);
		glDrawArrays(GL_TRIANGLE_STRIP, 57, 6);
		glDrawArrays(GL_TRIANGLE_STRIP, 63, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 67, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 71, 3);
		glDrawArrays(GL_TRIANGLE_STRIP, 74, 5);
		glDrawArrays(GL_TRIANGLE_STRIP, 79, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 83, 3);
		glDrawArrays(GL_TRIANGLE_STRIP, 86, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 90, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 94, 4);*/

		glBindVertexArray(0);
		glUseProgram(0);

		//End of Display Section

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}