#include "CollisionObject.h"


my::CollisionObject::CollisionObject() :
    _func_map() {
}

my::CollisionObject::~CollisionObject() {
}

void my::CollisionObject::AddCollisionFunc(const std::string& type, CollisionFunc lambda) {
}

void my::CollisionObject::ExcuteFunction(const std::string& key, const my::CollisionInfo& info) {
}