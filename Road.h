#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include "Objeto.h"


#define MAX_ENIMY 20
const float tamX_Road = 70;


class Road
{
public:

	float x;
	float y;
	float z;
	int numObstaculos;
	float intervalo;
	Objeto obstaculos[MAX_ENIMY];

	bool active=true;

	void Draw();
};

