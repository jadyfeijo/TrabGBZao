#include "Objeto.h"

void Objeto::Draw()
{
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(0 + x, 0 + y, 0 + z);
	glVertex3f(0 + x, 0 + y, 3 + z);
	glVertex3f(tamX_Obstaculo + x, 0 + y, 3 + z);
	glVertex3f(tamX_Obstaculo + x, 0 + y, 0 + z);
	glEnd();
}