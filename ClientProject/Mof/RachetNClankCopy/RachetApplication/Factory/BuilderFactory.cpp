#include "BuilderFactory.h"

/*
#include "../Component/Component.h"
#include "Builder/ActorBuilder.h"
#include "Builder/TerrainBuilder.h"
#include "Builder/OmniWrenchBuilder.h"
*/


my::BuilderFactory::BuilderFactory(my::ComponentFactory* component_factory) :
    _builders(),
    _component_factory(component_factory),
    _resource() {
}

my::BuilderFactory::~BuilderFactory() {
    this->Release();
}

void my::BuilderFactory::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::BuilderFactory::Release(void) {
    _component_factory = nullptr;
}

std::shared_ptr<my::IBuilder> my::BuilderFactory::Create(const char* path) const {
    // actor builder のみ

    // builderフォルダのファイル構成をきれいにする
    // パスで作成するCreateBuilderのtemplate引数を変える
    // 2回もioが入って無駄
    
    // 作成
    rapidjson::Document document;
    if (!ut::ParseJsonDocument(path, document)) {
        return nullptr;
    } // if

    std::shared_ptr<my::ActorBuilder>  builder;
    if (document.HasMember("type")) {
        std::string type = document["type"].GetString();
        if (type == "Terrain") {
            return this->CreateBuilder<my::TerrainBuilder>(path);
        } // if
        else if (type == "OmniWrench") {
            return this->CreateBuilder<my::OmniWrenchBuilder>(path);
        } // else if
    } // if
    else {
        return this->CreateBuilder<my::ActorBuilder>(path);
    } // else
    return builder;
}