#include "ComponentCreator.h"


ratchet::ComponentCreator::ComponentCreator() :
    _origin() {
}

ratchet::ComponentCreator::~ComponentCreator() {
    this->Release();
}

std::string ratchet::ComponentCreator::GetComponentType(void) {
    return this->_origin->GetType();
}

std::shared_ptr<ratchet::Component> ratchet::ComponentCreator::Create(const rapidjson::Value& param) const{
    auto ret = _origin->Clone();
    ret->SetParam(param);
    return ret;
}

void ratchet::ComponentCreator::Release(void) {
    if (_origin) {
        // ������p�I�u�W�F�N�g��Release���ĂԕK�v�͂Ȃ�
        _origin.reset();
    } // if
}