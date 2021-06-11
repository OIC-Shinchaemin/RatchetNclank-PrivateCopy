#ifndef MY_BUILDER_FACTORY_H
#define MY_BUILDER_FACTORY_H


#include <memory>
#include <string>
#include <map>

#include "Base/Core/Define.h"
#include "Builder/IBuilder.h"
#include "ComponentFactory.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "Factory.h"

#include "../Component/Component.h"
#include "Builder/ActorBuilder.h"
#include "Builder/TerrainBuilder.h"
#include "Builder/OmniWrenchBuilder.h"


namespace my {
class BuilderFactory {
private:
    //! �ێ����Ă���Bulder
    std::map<std::string, std::shared_ptr<my::IBuilder>> _builders;
    //! �R���|�[�l���g
    my::ComponentFactory* _component_factory;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;


    void SetActorBuilderParam(std::shared_ptr<my::ActorBuilder> builder, const rapidjson::Document& document) const {
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
    }
    void SetTerrainBuilderParam(std::shared_ptr<my::TerrainBuilder> builder) const {
        builder->SetResourceManager(_resource);
    }
    void SetOmniWrenchBuilderParam(std::shared_ptr<my::OmniWrenchBuilder> builder) const {
    }

    template <typename Builder>
    std::shared_ptr<Builder> CreateBuilder(const char* path = nullptr) const {
        auto ptr = ut::MakeSharedWithRelease<Builder>();
        return ptr;
    }
    template <>
    std::shared_ptr<my::ActorBuilder> CreateBuilder<my::ActorBuilder>(const char* path) const {
        auto ptr = ut::MakeSharedWithRelease<my::ActorBuilder>();
        rapidjson::Document document;
        if (!ut::ParseJsonDocument(path, document)) {
            return nullptr;
        } // if
        this->SetActorBuilderParam(ptr, document);
        return ptr;
    }
    template <>
    std::shared_ptr<my::OmniWrenchBuilder> CreateBuilder<my::OmniWrenchBuilder>(const char* path) const {
        auto ptr = ut::MakeSharedWithRelease<my::OmniWrenchBuilder>();
        rapidjson::Document document;
        if (!ut::ParseJsonDocument(path, document)) {
            return nullptr;
        } // if
        this->SetActorBuilderParam(ptr, document);
        this->SetOmniWrenchBuilderParam(ptr);
        return ptr;
    }
    template <>
    std::shared_ptr<my::TerrainBuilder> CreateBuilder<my::TerrainBuilder>(const char* path) const {
        auto ptr = ut::MakeSharedWithRelease<my::TerrainBuilder>();
        rapidjson::Document document;
        if (!ut::ParseJsonDocument(path, document)) {
            return nullptr;
        } // if
        this->SetActorBuilderParam(ptr, document);
        this->SetTerrainBuilderParam(ptr);
        return ptr;
    }


public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="component_factory"></param>
    BuilderFactory(my::ComponentFactory* component_factory);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~BuilderFactory();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    void Release(void);
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    std::shared_ptr<my::IBuilder> Create(const char* path) const;
};
}
#endif // !MY_ACTOR_FACTORY_H