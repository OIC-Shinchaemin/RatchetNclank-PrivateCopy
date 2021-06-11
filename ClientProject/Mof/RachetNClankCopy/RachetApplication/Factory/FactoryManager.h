#ifndef RACHET_FACTORY_MANAGER_H
#define RACHET_FACTORY_MANAGER_H


#include "../GameDefine.h"
#include "Base/Core/FunctionPointerContainer.h"
#include "Factory.h"
#include "ComponentFactory.h"
#include "BuilderFactory.h"
#include "ActorFactory.h"
#include "BehaviourFactory.h"
#include "BehaviourExecutorFactory.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Game/GameManager.h"


namespace rachet {
class FactoryManager {
private:
    //! コンポーネント
    rachet::ComponentFactory _component;
    //! ビルダー
    rachet::BuilderFactory _builder;
    //! アクター
    rachet::ActorFactory _actor;
    //! ファクトリー
    rachet::BehaviourFactory _behaviour_node;
    //! ファクトリー
    rachet::BehaviourExecutorFactory _behaviour_executor;
    //! リソース
    std::weak_ptr<rachet::ResourceMgr> _resource;
    //! ゲーム
    std::weak_ptr<rachet::GameManager> _game;
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FactoryManager();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~FactoryManager();
public:
    /// <summary>
    /// シングルトン
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static rachet::FactoryManager& Singleton(void);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<rachet::GameManager> ptr);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    std::shared_ptr<rachet::Component> CreateComponent(const char* name, const rapidjson::Value& param) const;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    std::shared_ptr<rachet::IBuilder> CreateBuilder(const char* path) const;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="path"></param>
    /// <param name="param"></param>
    /// <returns></returns>
    std::shared_ptr<rachet::Actor> CreateActor(const char* path, rachet::Actor::Param* param);
    template<typename Derived>
    std::shared_ptr<Derived> CreateActor(const char* path, rachet::Actor::Param* param) {
        return _actor.Create<Derived>(path, param);
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="type"></param>
    /// <param name="builder_key"></param>
    /// <param name="param"></param>
    /// <returns></returns>
    std::shared_ptr<rachet::Mechanical> CreateMechanicalWeapon(const char* type, const std::string& builder_key, rachet::Actor::Param* param);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    behaviour::NodeExecutorPtr CreateBehaviourExecutor(const char* key);
};
}
#endif // !RACHET_FACTORY_MANAGER_H