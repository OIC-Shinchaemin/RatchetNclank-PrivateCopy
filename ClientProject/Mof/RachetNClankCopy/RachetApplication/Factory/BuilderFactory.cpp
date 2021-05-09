#include "BuilderFactory.h"

#include "../Component/Component.h"
#include "ActorBuilder.h"
#include "TerrainBuilder.h"


my::BuilderFactory::BuilderFactory(my::ComponentFactory* component_factory) :
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

    // 作成
    rapidjson::Document document;
    if (!ut::ParseJsonDocument(path, document)) {
        return nullptr;
    } // if

    std::shared_ptr<my::ActorBuilder>  builder;
    if (!document.HasMember("type")) {
        builder = std::make_shared<my::ActorBuilder>();
    } // if
    else {
        std::string type = document["type"].GetString();
        if (type == "Terrain") {
            auto temp = std::make_shared<my::TerrainBuilder>();
            temp->SetResourceManager(_resource);
            builder = temp;
        } // if
    } // else


    if (document.HasMember("components")) {
        const auto& components = document["components"];
        _ASSERT_EXPR(components.IsArray(), L"指定された型でありません");
        for (int i = 0; i < components.Size(); i++) {
            _ASSERT_EXPR(components[i].HasMember("type"), L"タイプがありません");
            _ASSERT_EXPR(components[i]["type"].IsString(), L"タイプが指定された型でありません");
            _ASSERT_EXPR(components[i].HasMember("paramater"), L"パラメータがありません");
            _ASSERT_EXPR(components[i]["paramater"].IsObject(), L"パラメータが指定された型でありません");

            auto& param = components[i]["paramater"];

            // 値の設定
            std::string type = components[i]["type"].GetString();

            auto com = _component_factory->Create(type.c_str(), param);
            builder->AddComponent(com);
        } // for
    } // if

    return builder;
}