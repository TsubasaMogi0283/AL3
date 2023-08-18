#include "Collider.h"



void Collider::SetCollosionAttribute(uint32_t collisionAttribute) {
	collisionAttribute_ = collisionAttribute;
}

void Collider::SetCollisionMask(uint32_t collisionMask) { 
	collisionMask_ = collisionMask; 
}

