#ifndef GOE_BULLET_H
#define GOE_BULLET_H

#include "entity.h"

class Bullet : public Entity {
public:
	typedef Entity super;

	Bullet(ph::vec3f pos, ph::vec3f vel);
};

#endif
