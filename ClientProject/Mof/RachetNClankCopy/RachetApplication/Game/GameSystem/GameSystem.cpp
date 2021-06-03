#include "GameSystem.h"

std::shared_ptr<my::ResourceMgr> my::GameSystem::GetResource(void) const {
    if (auto ptr = _resource.lock()) {
        return ptr;
    } // if
    return nullptr;
}

std::shared_ptr<my::UICanvas> my::GameSystem::GetUICanvas(void) const {
    if (auto ptr = _ui_canvas.lock()) {
        return ptr;
    } // if
    return nullptr;
}

my::GameSystem::GameSystem() :
    _subject(),
    _resource(),
    _ui_canvas(){
}

my::GameSystem::~GameSystem() {
}

void my::GameSystem::OnNotify(bool flag) {
    _subject.Notify(shared_from_this());
}

void my::GameSystem::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::GameSystem::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

my::Observable<const std::shared_ptr<my::GameSystem>&>* my::GameSystem::GetSubject(void) {
    return &this->_subject;
}

bool my::GameSystem::Update(float delta_time) {
    return false;
}
