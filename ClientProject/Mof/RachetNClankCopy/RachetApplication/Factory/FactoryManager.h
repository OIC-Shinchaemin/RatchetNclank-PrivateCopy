#ifndef MY_FACTORY_MANAGER_H
#define MY_FACTORY_MANAGER_H


#include "../GameDefine.h"
#include "../FunctionPointerContainer.h"
#include "Factory.h"
#include "My/Core/State.h"
#include "../State/AIState.h"
#include "../State/EnemyMotionState.h"
#include "ComponentFactory.h"
#include "BuilderFactory.h"
#include "BehaviourFactory.h"
#include "BehaviourExecutorFactory.h"


namespace my {
class FactoryManager {
private:
    //! �R���|�[�l���g
    my::ComponentFactory _component;
    //! �R���|�[�l���g
    my::BuilderFactory _builder;
    //! �t�@�N�g���[
    my::BehaviourFactory _behaviour_node;
    //! �t�@�N�g���[
    my::BehaviourExecutorFactory<class Enemy> _behaviour_executor;
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
    static my::FactoryManager& Singleton(void);
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    std::shared_ptr<my::Component> CreateComponent(const char* name, const rapidjson::Value& param) const;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    std::shared_ptr<my::IBuilder> CreateBuilder(const char* path) const;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    behaviour::NodeExecutorPtr<std::shared_ptr<class Enemy> > CreateBehaviourExecutor(const char* key);
};
}
#endif // !MY_FACTORY_MANAGER_H