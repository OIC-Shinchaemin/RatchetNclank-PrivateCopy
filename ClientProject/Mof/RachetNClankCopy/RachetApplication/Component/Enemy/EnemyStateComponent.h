#ifndef MY_ENEMY_STATE_COMPONENT_H
#define MY_ENEMY_STATE_COMPONENT_H


#include "../ActionStateComponent.h"
/*
#include "Base/Core/StateMachine.h"
#include "Base/Core/Timer.h"
#include "../../State/ActionState.h"
*/

namespace my {
class EnemyStateComponent : public my::ActionStateComponent {
    using super = my::ActionStateComponent;
/*
private:
    //! ���
    my::StateMachine _state_machine;
    /// <summary>
    /// �o�^
    /// </summary>
    /// <typeparam name="State"></typeparam>
    /// <param name="out"></param>
    template<class State>
    void RegisterState(my::StateMachine& out) {
        auto shared_this = super::GetOwner();
        auto ptr = std::make_shared<State>();
        ptr->SetActor(shared_this);
        out.RegisterState(ptr);
    }
    /// <summary>
    /// �o�^
    /// </summary>
    /// <typeparam name="State"></typeparam>
    /// <param name="out"></param>
    void RegisterState(my::StateMachine& out, std::shared_ptr<my::ActionComponent> com) {
        auto shared_this = super::GetOwner();
        auto ptr = std::make_shared<state::ActionState>();
        ptr->SetActionComponent(com);
        out.RegisterState(ptr);
    }
*/
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    EnemyStateComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    EnemyStateComponent(const EnemyStateComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyStateComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    //virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="state"></param>
    /// <returns></returns>
    //bool IsEqual(std::string_view state) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    //virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Release(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    //void ChangeState(const std::string& name);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    bool CanTransition(const std::string& next);
#ifdef _DEBUG
    virtual bool DebugRender(void) override;
#endif // _DEBUG
};
}
#endif // !MY_ENEMY_STATE_COMPONENT_H