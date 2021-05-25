#include "Enemy.h"


my::Enemy::Enemy() :
    super() {
    super::SetTag("Enemy");
}

my::Enemy::~Enemy() {
}

void my::Enemy::End(void) {
    super::End();
    Observable::Notify("EnemyDead", shared_from_this());
}