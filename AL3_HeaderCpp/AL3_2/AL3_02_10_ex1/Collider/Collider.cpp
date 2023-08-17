#include "Collider.h"


//衝突時に呼ばれる関数
void Collider::OnCollision() {

}

void Collider::SetCollosionAttribute(uint32_t collisionAttribute) {
	collisionAttribute_ = collisionAttribute;
}

void Collider::SetCollisionMask(uint32_t collisionMask) { 
	collisionMask_ = collisionMask; 
}

