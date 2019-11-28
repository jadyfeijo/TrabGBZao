//*****************************************************************************
// Projeto OpenGL utilizando GLFW 
//
// Desenho básico baseado no livro "OpenGL - Uma Abordagem Prática e Objetiva"
//
// Disponibilizado por Vini Cassol - 15/08/2019
// Novembro - 2019 - Visualização 3D
//******************************************************************************

#include <iostream>
#include "Render.h" //é a Render que está incluindo a glfw!
using namespace std;

//Algumas globais para interface e simulação (IDEAL: criar uma classe gerenciadora)
float xMin = -20.0, xMax = 20.0, yMin = -20.0, yMax = 20.0; 

float posx = 15.0;
float posy = 70.0;
float posz = -70.0;
float alvox = 0.0;
float alvoy = 0.0;
float alvoz = 0.0;
float ang = 25;
int proj = 1;

float posXAtual = 0;
float posZAtual = 0;

void ajustaCamera2D(int width, int height)
{
	//Ativa a matriz de projeção --> conceitos mais tarde!!
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width < height) //altura menor que largura
	{
		float aspecto = (float)height / width; //proporcao altura/largura 
		gluOrtho2D(xMin, xMax, yMin * aspecto, yMax * aspecto); //corrige a proporção na largura
	}
	else {
		float aspecto = (float)width / height; //proporcao largura/altura
		gluOrtho2D(xMin * aspecto, xMax * aspecto, yMin, xMax); //corrige a proporção na altura

	}
}

void Visualizacao() {

	//Tipo de camera
	if (proj == 0)
		glOrtho(-30, 30, -30, 30, 1, 100);
	else if (proj == 1)
		gluPerspective(75, 1, 1, 10000);

	//Posição da camera
	gluLookAt(posx, posy, posz+30, alvox, alvoy, alvoz, 0, 1, 0);
}

void DesenhaCena() {

	//Comandos para habilitar a transparencia em areas sobrepostas
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Visualizacao();

	glRotatef(ang, 0, -1, 0);
//referencias vetores
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-10, 0, 0);
	glVertex3f(10, 0, 0);
	glVertex3f(9, 0, -2);
	glVertex3f(9, 0, 2);

	glColor3f(0, 1, 0);
	glVertex3f(0, -10, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(-2, 9, 0);
	glVertex3f(2, 9, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -10);
	glVertex3f(0, 0, 10);
	glVertex3f(-2, 0, 9);
	glVertex3f(2, 0, 9);
	glEnd();


	//piramide Quéops
	glBegin(GL_QUADS);
	glColor3f(0,0,0);
	glVertex3i(-5+posXAtual, -5, -5+posZAtual);
	glVertex3i(5 + posXAtual, -5, -5+posZAtual);
	glVertex3i(5 + posXAtual, -5, 5 + posZAtual);
	glVertex3i(-5 + posXAtual, -5, 5 + posZAtual);
	glEnd();

	glBegin(GL_TRIANGLES);
	// face voltada para eixo z positivo
	glColor4f(1.0f, 0.0f, 0.0f, 0.5);
	glVertex3i(5, -5, -5);
	glVertex3i(5, -5, 5);
	glVertex3i(0, 7, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
		
	glColor4f(0.0f, 1.0f, 0.0f, 0.5);
	glVertex3i(-5, -5, 5);
	glVertex3i(5, -5, 5);
	glVertex3i(0, 7, 0);
	glEnd();

	glBegin(GL_TRIANGLES);

	glColor4f(0.0f, 0.0f, 1.0f, 0.5);
	glVertex3i(-5, -5, -5);
	glVertex3i(-5, -5, 5);
	glVertex3i(0, 7, 0);
	glEnd();

	glBegin(GL_TRIANGLES);

	glColor4f(0.0f, 1.0f, 1.0f, 0.5);
	glVertex3i(-5, -5, -5);
	glVertex3i(5, -5, -5);
	glVertex3i(0, 7, 0);
	glEnd();

//faixas rodovia
	glBegin(GL_QUADS);
	for(int i=0)
	glColor3f(0.4, 0.4, 0.4);
	glVertex3i
	//piramide Quéfren

	//glBegin(GL_QUADS);
	//glColor3f(0, 0, 0);
	//glVertex3i(-20, -5, -20);
	//glVertex3i(-10, -5, -20);
	//glVertex3i(-10, -5, -10);
	//glVertex3i(-20, -5, -10);
	//glEnd();

	//glBegin(GL_TRIANGLES);

	//glColor4f(1.0f, 1.0f, 0.0f, 0.5);
	//glVertex3i(-10, -5, -10);
	//glVertex3i(-10, -5, -20);
	//glVertex3i(-15, 7, -15);
	//glEnd();

	//glBegin(GL_TRIANGLES);

	//glColor4f(1.0f, 0.0f, 1.0f, 0.5);
	//glVertex3i(-10, -5, -10);
	//glVertex3i(-20, -5, -10);
	//glVertex3i(-15, 7, -15);
	//glEnd();

	//glBegin(GL_TRIANGLES);

	//glColor4f(1.0f, 0.0f, 0.5f, 0.5);
	//glVertex3i(-20, -5, -10);
	//glVertex3i(-20, -5, -20);
	//glVertex3i(-15, 7, -15);
	//glEnd();

	//glBegin(GL_TRIANGLES);

	//glColor4f(0.0f, 0.5f, 1.0f, 0.5);
	//glVertex3i(-10, -5, -20);
	//glVertex3i(-20, -5, -20);
	//glVertex3i(-15, 7, -15);
	//glEnd();



	//piramide Miquerinos

	//glBegin(GL_QUADS);
	//glColor3f(0, 0, 0);
	//glVertex3i(7, -5, 7);
	//glVertex3i(12, -5, 7);
	//glVertex3i(12, -5, 12);
	//glVertex3i(7, -5, 12);
	//glEnd();

	//glBegin(GL_TRIANGLES);

	//glColor4f(0.5f, 1.0f, 0.0f, 0.5);
	//glVertex3i(12, -5, 7);
	//glVertex3i(12, -5, 12);
	//glVertex3i(9.5, 2.5, 9.5);
	//glEnd();

	//glBegin(GL_TRIANGLES);

	//glColor4f(0.0f, 1.0f, 0.5f, 0.5);
	//glVertex3i(7, -5, 12);
	//glVertex3i(12, -5, 12);
	//glVertex3i(9.5, 2.5, 9.5);
	//glEnd();

	//glBegin(GL_TRIANGLES);

	//glColor4f(1.0f, 0.5f, 0.0f, 0.5);
	//glVertex3i(7, -5, 7);
	//glVertex3i(7, -5, 12);
	//glVertex3i(9.5, 2.5, 9.5);
	//glEnd();

	//glBegin(GL_TRIANGLES);

	//glColor4f(0.5f, 1.0f, 0.5f, 0.5);
	//glVertex3i(7, -5, 7);
	//glVertex3i(12, -5, 7);
	//glVertex3i(9.5, 2.5, 9.5);
	//glEnd();

	cout << ang << endl;
}

//Callback de erro - PADRÃO DA GLFW - não precisa mexer
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

//Callback de teclado - PADRÃO DA GLFW - alterar conforme desejar (teclas de controle do programa)
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_LEFT)
		ang += 5;
	
	if (key == GLFW_KEY_RIGHT)
		ang -= 5;

	if (key == GLFW_KEY_O && action == GLFW_PRESS)
		proj = 0;

	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		proj = 1;
	if (key == GLFW_KEY_W)
		posZAtual += 1;
	if (key == GLFW_KEY_S)
		posZAtual -= 1;
	//if (key == GLFW_KEY_A)
	//	posXAtual += 1;
	//if (key == GLFW_KEY_D)
	//	posXAtual -= 1;
}

// Programa Principal 
int main()
{
	
	GLFWwindow* window; //Inicialização da janela da aplicação
	glfwSetErrorCallback(error_callback); //Setando a callback de erro - PADRÃO

	if (!glfwInit()) //Inicializando a lib
		exit(EXIT_FAILURE);

	//Criando a janela
	window = glfwCreateWindow(1280, 720, "PRIMEIRO DESENHO!!!", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Colocando a janela criada como sendo o contexto atual
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//Setando a callback de teclado
	glfwSetKeyCallback(window, key_callback);
	ajustaCamera2D(1280, 720);
	while (!glfwWindowShouldClose(window)) //loop da aplicação :)
	{
		float ratio;
		int width, height;

		//aqui recupera o tamanho atual da janela, para correção do aspect ratio mais tarde
		glfwGetFramebufferSize(window, &width, &height);
		//setando a viewport da OpenGL, para ocupar toda a janela da aplicação
		glViewport(0, 0, width, height);

		// Limpa a janela de visualização com a cor branca
		glClearColor(1, 1, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		//Setando a matriz de modelo, para mandar desenhar as primitivas
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		DesenhaCena();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	return 0;
}
