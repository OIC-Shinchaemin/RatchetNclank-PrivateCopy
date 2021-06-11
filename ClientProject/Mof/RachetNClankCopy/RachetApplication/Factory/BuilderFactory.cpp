#include "BuilderFactory.h"

/*
#include "../Component/Component.h"
#include "Builder/ActorBuilder.h"
#include "Builder/TerrainBuilder.h"
#include "Builder/OmniWrenchBuilder.h"
*/


rachet::BuilderFactory::BuilderFactory(rachet::ComponentFactory* component_factory) :
    _builders(),
    _component_factory(component_factory),
    _resource() {
}

rachet::BuilderFactory::~BuilderFactory() {
    this->Release();
}

void rachet::BuilderFactory::SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void rachet::BuilderFactory::Release(void) {
    _component_factory = nullptr;
}

std::shared_ptr<rachet::IBuilder> rachet::BuilderFactory::Create(const char* path) const {
    // actor builder のみ

    // builderフォルダのファイル構成をきれいにする
    // パスで作成するCreateBuilderのtemplate引数を変える
    // 2回もioが入って無駄
    
    // 作成
    rapidjson::Document document;
    if (!ut::ParseJsonDocument(path, document)) {
        return nullptr;
    } // if

    std::shared_ptr<rachet::ActorBuilder>  builder;
    if (document.HasMember("type")) {
        std::string type = document["type"].GetString();
        if (type == "Terrain") {
            return this->CreateBuilder<rachet::TerrainBuilder>(path);
        } // if
        else if (type == "OmniWrench") {
            return this->CreateBuilder<rachet::OmniWrenchBuilder>(path);
        } // else if
    } // if
    else {
        return this->CreateBuilder<rachet::ActorBuilder>(path);
    } // else
    return builder;
}