#ifndef RATCHET_FACTORY_FACTORY_MANAGER_H
#define RATCHET_FACTORY_FACTORY_MANAGER_H


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


namespace ratchet {
namespace factory {
class FactoryManager {
private:
    //! �R���|�[�l���g
    ratchet::factory::ComponentFactory _component;
    //! �r���_�[
    ratchet::factory::BuilderFactory _builder;
    //! �A�N�^�[
    ratchet::factory::ActorFactory _actor;
    //! �t�@�N�g���[
    ratchet::factory::BehaviourFactory _behaviour_node;
    //! �t�@�N�g���[
    ratchet::factory::BehaviourExecutorFactory _behaviour_executor;
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! �Q�[��
    std::weak_ptr<ratchet::GameManager> _game;
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    FactoryManager();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~FactoryManager();
public:
    /// <summary>
    /// �V���O���g��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static ratchet::factory::FactoryManager& Singleton(void);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<ratchet::GameManager> ptr);
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::Component> CreateComponent(const char* name, const rapidjson::Value& param) const;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::factory::builder::IBuilder> CreateBuilder(const char* path) const;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="path"></param>
    /// <param name="param"></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::Actor> CreateActor(const char* path, ratchet::Actor::Param* param);
    template<typename Derived>
    std::shared_ptr<Derived> CreateActor(const char* path, ratchet::Actor::Param* param) {
        return _actor.Create<Derived>(path, param);
    }
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="type"></param>
    /// <param name="builder_key"></param>
    /// <param name="param"></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::Mechanical> CreateMechanicalWeapon(const char* type, const std::string& builder_key, ratchet::Actor::Param* param);
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    behaviour::NodeExecutorPtr CreateBehaviourExecutor(const char* key);
};
}
}
#endif // !RATCHET_FACTORY_FACTORY_MANAGER_H