#include "ActorFactory.h"

#include "../Component/Component.h"


my::ActorFactory::ActorFactory(my::BuilderFactory* builder_factory) :
    _builder_factory(builder_factory),
    _builders() {    
}

my::ActorFactory::~ActorFactory() {
    this->Release();
}

std::shared_ptr<my::IBuilder> my::ActorFactory::GetBuilder(const std::string& key) {
    return this->_builders[key];
}

void my::ActorFactory::AddBuilder(const std::string& key, std::shared_ptr<my::IBuilder> builder) {
    this->_builders[key] = builder;
}

bool my::ActorFactory::Exist(const std::string& type) const {
    auto it = _builders.find(type);
    if (it == _builders.end()) {
        return false;
    } // if
    return true;
}

void my::ActorFactory::Release(void) {
    if (!_builders.empty()) {
        _builders.clear();
    } // if
}