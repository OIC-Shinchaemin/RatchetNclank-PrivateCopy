#include "BuilderFactory.h"

#include "../Component/Component.h"
#include "ActorBuilder.h"

my::BuilderFactory::BuilderFactory(my::ComponentFactory* component_factory) :
    _component_factory(component_factory) {
}

my::BuilderFactory::~BuilderFactory() {
    this->Release();
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

    auto builder = std::make_shared<my::ActorBuilder>();
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
            (std::dynamic_pointer_cast<my::ActorBuilder>)(builder)->AddComponent(com);
        } // for
    } // if

    return builder;
}