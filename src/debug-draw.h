#ifndef GOE_DEBUG_DRAW_H
#define GOE_DEBUG_DRAW_H

#include "includes.h"

class DebugDraw : public btIDebugDraw {
public:
	int mode;

	void drawLine(const btVector3 &from, const btVector3 &to,
	              const btVector3 &color);

	void setDebugMode(int);
	int getDebugMode() const;

	/* These are pure virtual, but I haven't really implemented them. */
	void drawContactPoint(const btVector3&, const btVector3&, btScalar,
	                      int, const btVector3&);
	void reportErrorWarning(const char*);
	void draw3dText(const btVector3&, const char*);
};

#endif
