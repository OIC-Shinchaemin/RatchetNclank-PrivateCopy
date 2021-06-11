#ifndef RATCHET_BUILDER_FACTORY_H
#define RATCHET_BUILDER_FACTORY_H


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
#include "Builder/Actor/ActorBuilder.h"
#include "Builder/Actor/TerrainBuilder.h"
#include "Builder/Actor/OmniWrenchBuilder.h"


namespace ratchet {
class BuilderFactory {
private:
    //! 保持しているBulder
    std::map<std::string, std::shared_ptr<ratchet::factory::builder::IBuilder>> _builders;
    //! コンポーネント
    ratchet::ComponentFactory* _component_factory;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;


    void SetActorBuilderParam(std::shared_ptr<ratchet::factory::builder::actor::ActorBuilder> builder, const rapidjson::Document& document) const {
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
    }
    void SetTerrainBuilderParam(std::shared_ptr<ratchet::factory::builder::actor::TerrainBuilder> builder) const {
        builder->SetResourceManager(_resource);
    }
    void SetOmniWrenchBuilderParam(std::shared_ptr<ratchet::factory::builder::actor::OmniWrenchBuilder> builder) const {
    }

    template <typename Builder>
    std::shared_ptr<Builder> CreateBuilder(const char* path = nullptr) const {
        auto ptr = ut::MakeSharedWithRelease<Builder>();
        return ptr;
    }
    template <>
    std::shared_ptr<ratchet::factory::builder::actor::ActorBuilder> CreateBuilder<ratchet::factory::builder::actor::ActorBuilder>(const char* path) const {
        auto ptr = ut::MakeSharedWithRelease<ratchet::factory::builder::actor::ActorBuilder>();
        rapidjson::Document document;
        if (!ut::ParseJsonDocument(path, document)) {
            return nullptr;
        } // if
        this->SetActorBuilderParam(ptr, document);
        return ptr;
    }
    template <>
    std::shared_ptr<ratchet::factory::builder::actor::OmniWrenchBuilder> CreateBuilder<ratchet::factory::builder::actor::OmniWrenchBuilder>(const char* path) const {
        auto ptr = ut::MakeSharedWithRelease<ratchet::factory::builder::actor::OmniWrenchBuilder>();
        rapidjson::Document document;
        if (!ut::ParseJsonDocument(path, document)) {
            return nullptr;
        } // if
        this->SetActorBuilderParam(ptr, document);
        this->SetOmniWrenchBuilderParam(ptr);
        return ptr;
    }
    template <>
    std::shared_ptr<ratchet::factory::builder::actor::TerrainBuilder> CreateBuilder<ratchet::factory::builder::actor::TerrainBuilder>(const char* path) const {
        auto ptr = ut::MakeSharedWithRelease<ratchet::factory::builder::actor::TerrainBuilder>();
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
    /// コンストラクタ
    /// </summary>
    /// <param name="component_factory"></param>
    BuilderFactory(ratchet::ComponentFactory* component_factory);
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BuilderFactory();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    void Release(void);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::factory::builder::IBuilder> Create(const char* path) const;
};
}
#endif // !RATCHET_ACTOR_FACTORY_H