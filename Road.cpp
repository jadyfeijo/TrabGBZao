#include "Road.h"

void Road::Draw()
{
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(-tamX_Road/2 + x, 0 + y, 0 +z);
	glVertex3f(-tamX_Road / 2 + x, 0 + y, 10 + z);
	glVertex3f(tamX_Road / 2 + x, 0 + y, 10 + z);
	glVertex3f(tamX_Road / 2 + x, 0 + y, 0 + z);
	glEnd();

	glLineWidth(5);

	glBegin(GL_LINES);
	glColor3f(1, 1, 0);
	glVertex3f(tamX_Road / 2 + x, 0 + y, 0 + z);
	glVertex3f(-tamX_Road / 2 + x, 0 + y, 0 + z);
	glVertex3f(tamX_Road / 2 + x, 0 + y, 10 + z);
	glVertex3f(-tamX_Road / 2 + x, 0 + y, 10 + z);
	glEnd();
}
