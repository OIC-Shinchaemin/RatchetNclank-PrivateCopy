#include "GameSystem.h"


std::shared_ptr<ratchet::ResourceMgr> ratchet::game::gamesystem::GameSystem::GetResource(void) const {
    if (auto ptr = _resource.lock()) {
        return ptr;
    } // if
    return nullptr;
}

std::shared_ptr<base::ui::UICanvas> ratchet::game::gamesystem::GameSystem::GetUICanvas(void) const {
    if (auto ptr = _ui_canvas.lock()) {
        return ptr;
    } // if
    return nullptr;
}

ratchet::game::gamesystem::GameSystem::GameSystem() :
    _subject(),
    _resource(),
    _ui_canvas(){
}

ratchet::game::gamesystem::GameSystem::~GameSystem() {
}

void ratchet::game::gamesystem::GameSystem::OnNotify(bool flag) {
    _subject.Notify(shared_from_this());
}

void ratchet::game::gamesystem::GameSystem::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::game::gamesystem::GameSystem::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

base::core::Observable<const std::shared_ptr<ratchet::game::gamesystem::GameSystem>&>* ratchet::game::gamesystem::GameSystem::GetSubject(void) {
    return &this->_subject;
}

bool ratchet::game::gamesystem::GameSystem::Update(float delta_time) {
    return false;
}
