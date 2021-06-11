#include "ComponentCreator.h"


rachet::ComponentCreator::ComponentCreator() :
    _origin() {
}

rachet::ComponentCreator::~ComponentCreator() {
    this->Release();
}

std::string rachet::ComponentCreator::GetComponentType(void) {
    return this->_origin->GetType();
}

std::shared_ptr<rachet::Component> rachet::ComponentCreator::Create(const rapidjson::Value& param) const{
    auto ret = _origin->Clone();
    ret->SetParam(param);
    return ret;
}

void rachet::ComponentCreator::Release(void) {
    if (_origin) {
        // 複製専用オブジェクトはReleaseを呼ぶ必要はない
        _origin.reset();
    } // if
}