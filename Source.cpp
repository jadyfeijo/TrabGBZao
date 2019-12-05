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
#include "Road.h"
#include <ctime>

#define MAX_ROAD 9
using namespace std;


//Algumas globais para interface e simulação (IDEAL: criar uma classe gerenciadora)
float xMin = -20.0, xMax = 20.0, yMin = -20.0, yMax = 20.0; 

float posx = 15.0;
float posy = 70.0;
float posz = -70.0;
float alvox = 0.0;
float alvoy = 0.0;
float alvoz = 0.0;
float ang = 205;
int proj = 1;
float posXAtual = 0;
float posZAtual = 0;
int instRoad = 0;

float timer=0;

Road roads[MAX_ROAD];
Objeto player;

Road inicializaRoad(Road road)
{
	

		road.numObstaculos = rand()%(MAX_ENIMY-6)+6;

		road.intervalo =(tamX_Road*2 - road.numObstaculos * tamX_Obstaculo) / (float)road.numObstaculos +5;
		road.z = 10 * instRoad;

		for (int j = 0; j < road.numObstaculos; j++)
		{
			road.obstaculos[j].x = (-tamX_Road / 2) +road.intervalo*j;
			road.obstaculos[j].z = road.z+3;
		}
		instRoad++;
	

	return road;
}

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
	gluLookAt(posx, posy, posz+3, alvox, alvoy, alvoz, 0, 1, 0);
}

void DesenhaCena() {

	//Comandos para habilitar a transparencia em areas sobrepostas
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Visualizacao();

	glRotatef(ang, 0, -1, 0);
//referencias vetores



	for (int i = 0; i < MAX_ROAD; i++) {
		if (player.z > roads[i].z) {
			roads[i] = inicializaRoad(roads[i]);
		}
		roads[i].Draw();

		for (int j=0; j <= roads[i].numObstaculos; j++) {
			if (player.y >= roads[i].z && (player.x >= roads[i].obstaculos[j].x - 0.5 && player.x <= roads[i].obstaculos[j].x + 0.5))
			{
				printf("LOOOOOSE");
			}


			if (roads[i].obstaculos[j].x <= tamX_Road/2) {
				roads[i].obstaculos[j].x += timer * 2;
			}
			else {
				roads[i].obstaculos[j].x = -tamX_Road / 2;
			}
			roads[i].obstaculos[j].Draw();
		}
	}

	
	player.Draw();
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
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		player.z += 10;
		//posZAtual += 1;
	/*if (key == GLFW_KEY_S && action == GLFW_PRESS)
		player.z -= 10;
	if (key == GLFW_KEY_A)
		posXAtual += 1;
	if (key == GLFW_KEY_D)
		posXAtual -= 1;*/
}

// Programa Principal 
int main()
{
	srand(time(NULL));
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

	for (int i = 0; i < MAX_ROAD; i++)
	{
		roads[i] = inicializaRoad(roads[i]);

	}

	float time = (float)glfwGetTime();
	float tprev = 0;

	player.x = 0;
	player.y = 0;
	player.z = 0;

	while (!glfwWindowShouldClose(window)) //loop da aplicação :)
	{
		float ratio;
		int width, height;

		tprev = time;
		time = (float)glfwGetTime();

		timer = time - tprev;

		//printf("time=%f\n", timer);

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
