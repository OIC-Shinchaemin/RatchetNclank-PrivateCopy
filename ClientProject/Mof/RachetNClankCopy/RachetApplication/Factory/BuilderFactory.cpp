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
    // actor builder �̂�

    // �쐬
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
        _ASSERT_EXPR(components.IsArray(), L"�w�肳�ꂽ�^�ł���܂���");
        for (int i = 0; i < components.Size(); i++) {
            _ASSERT_EXPR(components[i].HasMember("type"), L"�^�C�v������܂���");
            _ASSERT_EXPR(components[i]["type"].IsString(), L"�^�C�v���w�肳�ꂽ�^�ł���܂���");
            _ASSERT_EXPR(components[i].HasMember("paramater"), L"�p�����[�^������܂���");
            _ASSERT_EXPR(components[i]["paramater"].IsObject(), L"�p�����[�^���w�肳�ꂽ�^�ł���܂���");

            auto& param = components[i]["paramater"];

            // �l�̐ݒ�
            std::string type = components[i]["type"].GetString();

            auto com = _component_factory->Create(type.c_str(), param);
            builder->AddComponent(com);
        } // for
    } // if

    return builder;
}