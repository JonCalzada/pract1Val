/*---------------------------------------------------------*/
/* ----------------   Práctica 1 - Ejercicio 2: Lobo --------------------------*/
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

static const char* myVertexShader = "										\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
																			\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);							\n\
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

// Fragment Shader Color de la figura
static const char* myFragmentShaderYellow = "									\n\
#version 330																\n\
																			\n\
out vec3 finalColor;														\n\
																			\n\
void main()																	\n\
{																			\n\
    finalColor = vec3(0.7176f, 0.1098f, 0.1098f);									\n\
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
		// Lista posiciones del dibujo			//  Arreglo de vertices en 3 dimensiones xyz
		//1
		0.48f,  0.66f, 0.0f,	//0	Ubicacion 0 en el origen 
		0.43f,  0.5f, 0.0f,		//1
		0.13f,  0.33f, 0.0f,	//2
		0.26f,  0.33f, 0.0f,	//3

		//2
		0.48f,  0.66f, 0.0f,	//4
		0.43f,  0.5f, 0.0f,		//5
		0.5f,  0.275f, 0.0f,	//6
		0.45f,  0.285f, 0.0f,	//7

		//3
		0.45f,  0.285f, 0.0f,	//8
		0.5f,  0.275f, 0.0f,	//9
		0.45f,  0.175f, 0.0f,	//10
		0.52f,  0.03f, 0.0f,	//11

		//4
		0.0f,  0.33f, 0.0f,		//12
		0.26f,  0.33f, 0.0f,	//13
		0.45f,  0.175f, 0.0f,	//14

		//5
		0.0f,  0.33f, 0.0f,		//15
		0.0f,  0.115f, 0.0f,	//16
		0.45f,  0.175f, 0.0f,	//17
		0.2f,  0.03f, 0.0f,		//18

		//6
		0.45f,  0.175f, 0.0f,	//19
		0.52f,  0.03f, 0.0f,	//20
		0.2f,  0.03f, 0.0f,		//21
		0.28f,  -0.1f, 0.0f,	//22
		0.15f,  -0.13f, 0.0f,	//23

		//7
		0.52f,  0.03f, 0.0f,	//24
		0.28f,  -0.1f, 0.0f,	//25
		0.53f,  -0.27f, 0.0f,	//26

		//8
		0.28f,  -0.1f, 0.0f,	//27
		0.53f,  -0.27f, 0.0f,	//28
		0.225f,  -0.19f, 0.0f,	//29
		0.4f,  -0.42f, 0.0f,	//30

		//9
		0.225f,  -0.19f, 0.0f,	//31
		0.13f,  -0.22f, 0.0f,	//32
		0.4f,  -0.42f, 0.0f,	//33
		0.23f,  -0.55f, 0.0f,	//34

		//10
		0.0f,  0.115f, 0.0f,	//35
		0.2f,  0.03f, 0.0f,		//36
		0.0f,  0.0f, 0.0f,		//37
		0.13f,  -0.22f, 0.0f,	//38
		0.0f,  -0.53f, 0.0f,	//39
		0.08f,  -0.53f, 0.0f,	//40

		0.13f,  -0.22f, 0.0f,	//41
		0.08f,  -0.53f, 0.0f,	//42
		0.23f,  -0.55f, 0.0f,	//43
		0.1f,  -0.6f, 0.0f,		//44
		0.18f,  -0.68f, 0.0f,	//45
		0.0f,  -0.65f, 0.0f,	//46

		//11
		0.18f,  -0.68f, 0.0f,	//47	
		0.0f,  -0.64f, 0.0f,	//48
		0.0f,  -0.73f, 0.0f,	//49
		-0.18f,  -0.68f, 0.0f,	//50

		//12
		-0.0f,  0.115f, 0.0f,	//51
		-0.2f,  0.03f, 0.0f,	//52
		-0.0f,  0.0f, 0.0f,		//53
		-0.13f,  -0.22f, 0.0f,	//54
		-0.0f,  -0.53f, 0.0f,	//55
		-0.08f,  -0.53f, 0.0f,	//56

		-0.13f,  -0.22f, 0.0f,	//57
		-0.08f,  -0.53f, 0.0f,	//58
		-0.23f,  -0.55f, 0.0f,	//59
		-0.1f,  -0.6f, 0.0f,	//60
		-0.18f,  -0.68f, 0.0f,	//61
		-0.0f,  -0.65f, 0.0f,	//62

		//13
		-0.225f,  -0.19f, 0.0f,	//63
		-0.13f,  -0.22f, 0.0f,	//64
		-0.4f,  -0.42f, 0.0f,	//65
		-0.23f,  -0.55f, 0.0f,	//66

		//14
		-0.28f,  -0.1f, 0.0f,	//67
		-0.53f,  -0.27f, 0.0f,	//68
		-0.225f,  -0.19f, 0.0f,	//69
		-0.4f,  -0.42f, 0.0f,	//70

		//15
		-0.52f, 0.03f, 0.0f,	//71
		-0.28f, -0.1f, 0.0f,	//72
		-0.53f, -0.27f, 0.0f,	//73

		//16
		-0.45f,  0.175f, 0.0f,	//74
		-0.52f,  0.03f, 0.0f,	//75
		-0.2f,  0.03f, 0.0f,	//76
		-0.28f,  -0.1f, 0.0f,	//77
		-0.15f,  -0.13f, 0.0f,	//78

		//17
		-0.0f,  0.33f, 0.0f,	//79
		-0.0f,  0.115f, 0.0f,	//80
		-0.45f,  0.175f, 0.0f,	//81
		-0.2f,  0.03f, 0.0f,	//82

		//18
		-0.0f,  0.33f, 0.0f,	//83
		-0.26f,  0.33f, 0.0f,	//84
		-0.45f,  0.175f, 0.0f,	//85

		//19
		-0.45f,  0.285f, 0.0f,	//86
		-0.5f,  0.275f, 0.0f,	//87
		-0.45f,  0.175f, 0.0f,	//88
		-0.52f,  0.03f, 0.0f,	//89

		//20
		-0.48f,  0.66f, 0.0f,	//90
		-0.43f,  0.5f, 0.0f,	//91
		-0.5f,  0.275f, 0.0f,	//92
		-0.45f,  0.285f, 0.0f,	//93

		//21
		-0.48f,  0.66f, 0.0f,	//94
		-0.43f,  0.5f, 0.0f,	//95
		-0.13f,  0.33f, 0.0f,	//96
		-0.26f,  0.33f, 0.0f,	//97
			////////////////////////////////////////////////////
	};

	unsigned int indices[] =
	{
		0, 1, 4, 2, 3
	};

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);



	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

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
		//glDrawElements(GL_POINTS, 5, GL_UNSIGNED_INT, 0);
		//Indicar la informacion a usar y como dibujarla, 3 parametros
		//1)Forma de dibujo (Directiva de punto, GL_POINTS, LINE Lineas, LINE_STRIP linea continua
		//GN_LINE_LOOP Linea unida, GL_TRIANGLES triangulos, _TRIANGLE_STRIP Crea triangulos de 3 en 3 quitando un vertice
		//GN_TRIANGLE_FAN Similar a strip pero utiliza el primer vertice como pivote.
		//2)elemento inicial de datos ingresados
		 //3) Cuantos elementos quiero dibujar 
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
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
		glDrawArrays(GL_TRIANGLE_STRIP, 94, 4);

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