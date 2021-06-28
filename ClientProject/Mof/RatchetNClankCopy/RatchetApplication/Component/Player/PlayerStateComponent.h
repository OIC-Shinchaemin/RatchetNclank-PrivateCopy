#ifndef RATCHET_COMPONENT_PLAYER_PLAYER_STATE_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_PLAYER_STATE_COMPONENT_H


#include "../ActionStateComponent.h"

#include "../../State/PlayerActionStateDefine.h"


namespace ratchet {
namespace component {
namespace player {
class PlayerStateComponent : public ratchet::component::ActionStateComponent {
    using super = ratchet::component::ActionStateComponent;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerStateComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerStateComponent(const PlayerStateComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerStateComponent();
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
    bool CanTransition(std::string_view next) const;
#ifdef _DEBUG
    virtual bool DebugRender(void) override;
#endif // _DEBUG
};
}
}
}
#endif // !RATCHET_COMPONENT_PLAYER_PLAYER_STATE_COMPONENT_H