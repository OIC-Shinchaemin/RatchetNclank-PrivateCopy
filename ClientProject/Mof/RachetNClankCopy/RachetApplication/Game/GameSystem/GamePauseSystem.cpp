#include "GamePauseSystem.h"

my::GamePauseSystem::GamePauseSystem() {
}

my::GamePauseSystem::~GamePauseSystem() {
}

void my::GamePauseSystem::OnNotify(bool flag) {
}

my::Observable<const my::GamePauseSystem::Info&>* my::GamePauseSystem::GetInfoSubject(void) {
    return nullptr;
}

bool my::GamePauseSystem::Initialize(void) {
    return false;
}

bool my::GamePauseSystem::Input(void) {
    return false;
}

bool my::GamePauseSystem::Update(float delta_time) {
    return false;
}

bool my::GamePauseSystem::Release(void) {
    return false;
}
