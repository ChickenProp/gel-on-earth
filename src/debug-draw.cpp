#include "debug-draw.h"
#include "vertex.h"

void DebugDraw::drawLine(const btVector3 &from, const btVector3 &to,
                         const btVector3 &color)
{

	VertexC line[2] = {
		VertexC( (ph::vec3f) from, color.x(), color.y(), color.z() ),
		VertexC( (ph::vec3f) to, color.x(), color.y(), color.z() )
	};

	line[0].draw(GL_LINES, 2);
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

