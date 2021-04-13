#include "BuilderFactory.h"

#include "../Component/Component.h"
#include "ActorBuilder.h"
/*
std::shared_ptr<my::IBuilder> my::BuilderFactory::CreateBuilder(const char* path) {
    rapidjson::Document document;
    if (!ut::ParseJsonDocument(path, document)) {
        return nullptr;
    } // if
    // create

    auto actor_param = my::Actor::Param();
    auto builder = ut::MakeSharedWithRelease<my::IBuilder>();

    if (document.HasMember("proto_type")) {
        auto& proto_type = document["proto_type"];
        _ASSERT_EXPR(proto_type["source"].IsString(), L"指定された型でありません");

        auto source_path = std::string(proto_type["source"].GetString());
        if (!this->Exist(source_path)) {
            auto builder = this->CreateBuilder(source_path.c_str());
            this->AddBuilder(source_path, builder);
        } // if
        auto source = this->GetBuilder(source_path);
        source->Construct(builder);

        const auto& difference = proto_type["difference"];
        _ASSERT_EXPR(difference.IsArray(), L"指定された型でありません");
        for (int i = 0; i < difference.Size(); i++) {
            _ASSERT_EXPR(difference[i].HasMember("type"), L"タイプがありません");
            _ASSERT_EXPR(difference[i]["type"].IsString(), L"タイプが指定された型でありません");
            _ASSERT_EXPR(difference[i].HasMember("paramater"), L"パラメータがありません");
            _ASSERT_EXPR(difference[i]["paramater"].IsObject(), L"パラメータが指定された型でありません");

            auto& param = difference[i]["paramater"];
            // 値の設定
            std::string type = difference[i]["type"].GetString();
            if (auto com = builder->GetComponent(type); com) {
                com->SetParam(param);
            } // if
        } // for
    } // if

    if (document.HasMember("param")) {
        const auto& param = document["param"];
        if (param.HasMember("name")) {
            _ASSERT_EXPR(param["name"].IsString(), L"指定された型でありません");
            actor_param.name = param["name"].GetString();
        } // if
        if (param.HasMember("tag")) {
            _ASSERT_EXPR(param["tag"].IsString(), L"指定された型でありません");
            actor_param.tag = param["tag"].GetString();
        } // if
        builder->SetActorParam(actor_param);
    } // if

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
            auto& com = _component_factory.CreateComponent(type.c_str(), param);
            builder->AddComponent(com);
        } // for
    } // if
    return builder;
}
*/

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
/*
bool my::BuilderFactory::Exist(const std::string& type) {
    auto it = _builders.find(type);
    if (it == _builders.end()) {
        return false;
    } // if
    return true;
}
*/