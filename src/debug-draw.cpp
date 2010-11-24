#include "debug-draw.h"

void DebugDraw::drawLine(const btVector3 &from, const btVector3 &to,
                         const btVector3 &color)
{
	glColor3f(color.x(), color.y(), color.z());

	glBegin(GL_LINES);
	glVertex3f(from.x(), from.z(), from.y());
	glVertex3f(to.x(), to.z(), to.y());
	glEnd();
}

void DebugDraw::setDebugMode(int m) {
	mode = m;
}
int DebugDraw::getDebugMode() const {
	return mode;
}

void DebugDraw::drawContactPoint(const btVector3&, const btVector3&, btScalar,
                                 int, const btVector3&)
{
	printf("drawContactPoint()");
}
void DebugDraw::reportErrorWarning(const char*) {
	printf("reportErrorWarning()");
}
void DebugDraw::draw3dText(const btVector3&, const char*) {
	printf("draw3dText()");
}

