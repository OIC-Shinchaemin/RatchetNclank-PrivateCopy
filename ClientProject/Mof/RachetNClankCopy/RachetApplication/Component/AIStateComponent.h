#ifndef MY_AI_STATE_COMPONENT_H
#define MY_AI_STATE_COMPONENT_H


#include "UpdateComponent.h"

#include "My/Core/StateMachine.h"
#include "My/Core/Timer.h"


namespace my {
class AIStateComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! ���
    my::StateMachine _state_machine;
    //! �^�C�}�[
    my::Timer _thinking_timer;
    //! �쐬�p�X
    std::vector<std::string> _behaviour_path;

    template<class State>
    void RegisterState(my::StateMachine& out, const std::string& behaviour) {
        auto shared_this = super::GetOwner();
        auto ptr = std::make_shared<State>();
        ptr->SetActor(shared_this);
        ptr->GenerateBehaviourExecutor(behaviour);
        out.RegisterState(ptr);
    }
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    AIStateComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    AIStateComponent(const AIStateComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~AIStateComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
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
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
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
    void ChangeState(const std::string& name);
#ifdef _DEBUG
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void) override;
#endif // _DEBUG
};
}
#endif // !MY_AI_STATE_COMPONENT_H