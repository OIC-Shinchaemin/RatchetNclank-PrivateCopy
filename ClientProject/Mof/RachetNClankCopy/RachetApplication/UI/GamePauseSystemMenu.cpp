#include "GamePauseSystemMenu.h"

my::GamePauseSystemMenu::GamePauseSystemMenu(const char* name) :
super(name){
}

void my::GamePauseSystemMenu::OnNotify(const my::GamePauseSystem::Info& info) {
}

void my::GamePauseSystemMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
}

void my::GamePauseSystemMenu::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
}

bool my::GamePauseSystemMenu::Initialize(void) {
    return false;
}

bool my::GamePauseSystemMenu::Update(float delta_time) {
    return false;
}

bool my::GamePauseSystemMenu::Render(void) {
    return false;
}
