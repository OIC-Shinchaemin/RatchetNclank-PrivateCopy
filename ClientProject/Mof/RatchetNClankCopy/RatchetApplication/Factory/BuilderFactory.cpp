#include "BuilderFactory.h"

/*
#include "../Component/Component.h"
#include "Builder/ActorBuilder.h"
#include "Builder/TerrainBuilder.h"
#include "Builder/OmniWrenchBuilder.h"
*/


ratchet::BuilderFactory::BuilderFactory(ratchet::ComponentFactory* component_factory) :
    _builders(),
    _component_factory(component_factory),
    _resource() {
}

ratchet::BuilderFactory::~BuilderFactory() {
    this->Release();
}

void ratchet::BuilderFactory::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::BuilderFactory::Release(void) {
    _component_factory = nullptr;
}

std::shared_ptr<ratchet::factory::builder::IBuilder> ratchet::BuilderFactory::Create(const char* path) const {
    // actor builder のみ

    // builderフォルダのファイル構成をきれいにする
    // パスで作成するCreateBuilderのtemplate引数を変える
    // 2回もioが入って無駄
    
    // 作成
    rapidjson::Document document;
    if (!ut::ParseJsonDocument(path, document)) {
        return nullptr;
    } // if

    std::shared_ptr<ratchet::factory::builder::actor::ActorBuilder>  builder;
    if (document.HasMember("type")) {
        std::string type = document["type"].GetString();
        if (type == "Terrain") {
            return this->CreateBuilder<ratchet::factory::builder::actor::TerrainBuilder>(path);
        } // if
        else if (type == "OmniWrench") {
            return this->CreateBuilder<ratchet::factory::builder::actor::OmniWrenchBuilder>(path);
        } // else if
    } // if
    else {
        return this->CreateBuilder<ratchet::factory::builder::actor::ActorBuilder>(path);
    } // else
    return builder;
}