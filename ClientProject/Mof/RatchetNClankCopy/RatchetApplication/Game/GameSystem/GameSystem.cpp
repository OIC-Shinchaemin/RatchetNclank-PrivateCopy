#include "GameSystem.h"


std::shared_ptr<ratchet::ResourceMgr> ratchet::GameSystem::GetResource(void) const {
    if (auto ptr = _resource.lock()) {
        return ptr;
    } // if
    return nullptr;
}

std::shared_ptr<base::ui::UICanvas> ratchet::GameSystem::GetUICanvas(void) const {
    if (auto ptr = _ui_canvas.lock()) {
        return ptr;
    } // if
    return nullptr;
}

ratchet::GameSystem::GameSystem() :
    _subject(),
    _resource(),
    _ui_canvas(){
}

ratchet::GameSystem::~GameSystem() {
}

void ratchet::GameSystem::OnNotify(bool flag) {
    _subject.Notify(shared_from_this());
}

void ratchet::GameSystem::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::GameSystem::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

base::core::Observable<const std::shared_ptr<ratchet::GameSystem>&>* ratchet::GameSystem::GetSubject(void) {
    return &this->_subject;
}

bool ratchet::GameSystem::Update(float delta_time) {
    return false;
}
