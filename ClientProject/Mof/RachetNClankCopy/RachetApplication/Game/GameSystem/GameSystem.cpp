#include "GameSystem.h"


std::shared_ptr<rachet::ResourceMgr> rachet::GameSystem::GetResource(void) const {
    if (auto ptr = _resource.lock()) {
        return ptr;
    } // if
    return nullptr;
}

std::shared_ptr<base::ui::UICanvas> rachet::GameSystem::GetUICanvas(void) const {
    if (auto ptr = _ui_canvas.lock()) {
        return ptr;
    } // if
    return nullptr;
}

rachet::GameSystem::GameSystem() :
    _subject(),
    _resource(),
    _ui_canvas(){
}

rachet::GameSystem::~GameSystem() {
}

void rachet::GameSystem::OnNotify(bool flag) {
    _subject.Notify(shared_from_this());
}

void rachet::GameSystem::SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void rachet::GameSystem::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

base::core::Observable<const std::shared_ptr<rachet::GameSystem>&>* rachet::GameSystem::GetSubject(void) {
    return &this->_subject;
}

bool rachet::GameSystem::Update(float delta_time) {
    return false;
}
