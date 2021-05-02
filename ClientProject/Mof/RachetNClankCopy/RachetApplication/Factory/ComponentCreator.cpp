#include "ComponentCreator.h"


my::ComponentCreator::ComponentCreator() :
    _origin() {
}

my::ComponentCreator::~ComponentCreator() {
    this->Release();
}

std::string my::ComponentCreator::GetComponentType(void) {
    return this->_origin->GetType();
}

std::shared_ptr<my::Component> my::ComponentCreator::Create(const rapidjson::Value& param) const{
    auto ret = _origin->Clone();
    ret->SetParam(param);
    return ret;
}

void my::ComponentCreator::Release(void) {
    if (_origin) {
        // ������p�I�u�W�F�N�g��Release���ĂԕK�v�͂Ȃ�
        _origin.reset();
    } // if
}