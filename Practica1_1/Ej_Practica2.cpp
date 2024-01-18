/*---------------------------------------------------------*/
/* ----------------   Práctica 2 --------------------------*/
/*-----------------    2023-2   ---------------------------*/
/*------------- (Nombre del alumno: DEL VALLE ARAGON ALEXIS RAFAEL ) ---------------*/
#include <glew.h>
#include <glfw3.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

GLFWmonitor *monitors;
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
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{
	float vertices[] = 
	{
		// Posicion de vertices		//  Color
		-0.35f,  -0.8f, 0.0f,		0.0f, 1.0f, 0.0f,		//0	
		-0.2f,  -0.8f, 0.0f,		0.0f, 1.0f, 0.0f,		//1
		-0.2f,  -0.025f, 0.0f,		0.0f, 1.0f, 0.0f,		//2
		0.05f,  -0.025f, 0.0f,		1.0f, 1.0f, 0.0f,		//3
		0.05f,  0.2f, 0.0f,			1.0f, 1.0f, 0.0f,		//4
		-0.2f,  0.2f, 0.0f,			1.0f, 1.0f, 0.0f,		//5
		-0.2f,  0.45f, 0.0f,		1.0f, 0.0f, 0.0f,		//6
		0.1f,  0.45f, 0.0f,			1.0f, 0.0f, 0.0f,		//7
		0.1f,  0.7f, 0.0f,			1.0f, 0.0f, 0.0f,		//8
		-0.35f,  0.7f, 0.0f,		1.0f, 0.0f, 0.0f,		//9

		-0.35f,  -0.6f, 0.0f,		1.0f, 0.0f, 1.0f,		//10
		-0.2f,  -0.6f, 0.0f,		1.0f, 0.56f, 0.59f,		//11
		-0.2f,  0.2f, 0.0f,			0.45f, 0.36f, 0.74f,	//12
		-0.2f,  0.4f, 0.0f,			0.099f, 0.88f, 0.77f,	//13
		-0.2f,  0.6f, 0.0f,			0.13f, 0.95f, 0.12f,	//14
		-0.35f,  0.7f, 0.0f,		0.45f, 1.0f, 1.0f,		//15

		-0.2f,  -0.025f, 0.0f,		1.0f, 1.0f, 0.0f,		//16 - 2
		
		-0.35f,  -0.8f, 0.0f,		1.0f, 1.0f, 0.0f,		//17 -0	
		-0.2f,  0.45f, 0.0f,		1.0f, 1.0f, 0.0f,		//18 -6
		-0.35f,  0.7f, 0.0f,		1.0f, 1.0f, 0.0f,		//19 -9

	};

	//Arreglo de indices 
	unsigned int indices[] =
	{
		0,1,2,	//valor  de tres elementos 0,1,2
		6,7,8,

		6,8,9,

		16,3,4,
		3,4,5,

		16,4,5,
		16,17,18,
		17,16,19,
		19,18,16

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
		glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0); //Para indices (tIPO DE FIGURA,CUANTOS VERTICES SE USARAN, ENTEROS SIN SIGNO, PRIMER VERTICE)
		//glDrawArrays(GL_TRIANGLE_FAN, 6, 4); //Indicar la informacion a usar y como dibujarla, 3 parametros
		//glDrawArrays(GL_TRIANGLE_FAN, 2, 4);  //1)Forma de dibujo (Directiva de punto, GL_POINTS, LINE Lineas, LINE_STRIP linea continua), 2)elemento inicial de datos ingresados
		//glDrawArrays(GL_TRIANGLE_FAN, 10, 6);  //3) Cuantos elementos quiero dibujar (GN_LINE_LOOP Linea unida, _TRIANGLE triangulos, _TRIANGLE_STRIP Crea triangulos de 3 en 3 quitando un vertice)
		
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
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}