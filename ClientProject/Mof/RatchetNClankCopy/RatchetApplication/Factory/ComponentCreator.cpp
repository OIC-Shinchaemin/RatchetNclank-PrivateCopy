#include "ComponentCreator.h"


ratchet::factory::ComponentCreator::ComponentCreator() :
    _origin() {
}

ratchet::factory::ComponentCreator::~ComponentCreator() {
    this->Release();
}

std::string ratchet::factory::ComponentCreator::GetComponentType(void) {
    return this->_origin->GetType();
}

std::shared_ptr<ratchet::component::Component> ratchet::factory::ComponentCreator::Create(const rapidjson::Value& param) const{
    auto ret = _origin->Clone();
    ret->SetParam(param);
    return ret;
}

void ratchet::factory::ComponentCreator::Release(void) {
    if (_origin) {
        // 複製専用オブジェクトはReleaseを呼ぶ必要はない
        _origin.reset();
    } // if
}