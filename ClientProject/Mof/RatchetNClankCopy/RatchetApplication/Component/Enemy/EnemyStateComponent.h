#ifndef RATCHET_COMPONENT_ENEMY_ENEMY_STATE_COMPONENT_H
#define RATCHET_COMPONENT_ENEMY_ENEMY_STATE_COMPONENT_H


#include "../ActionStateComponent.h"


namespace ratchet {
namespace component {
namespace enemy {
class EnemyStateComponent : public ratchet::component::ActionStateComponent {
    using super = ratchet::component::ActionStateComponent;
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
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
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
}
}
#endif // !RATCHET_COMPONENT_ENEMY_ENEMY_STATE_COMPONENT_H