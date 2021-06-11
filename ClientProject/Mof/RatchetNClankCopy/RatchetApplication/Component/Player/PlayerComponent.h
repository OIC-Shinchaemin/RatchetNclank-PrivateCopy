#ifndef RATCHET_PLAYER_COMPONENT_H
#define RATCHET_PLAYER_COMPONENT_H


#include "../CharacterComponent.h"

#include <memory>

#include "Base/Core/Observable.h"


namespace ratchet {
class PlayerComponent : public ratchet::CharacterComponent {
    using super = ratchet::CharacterComponent;
private:
    //! �W�I
    std::weak_ptr<ratchet::actor::Actor> _target;
    //! �J�[�\���ʒu
    base::core::Observable<std::optional<Mof::CVector3>> _observable;
    //! ���
    std::weak_ptr<class PlayerStateComponent> _state_com;
    //! �n�_
    std::string _next_terrain;
    //! �A�N�V�����t���O
    //bool _action_enable;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerComponent(const PlayerComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetTarget(const std::shared_ptr<ratchet::actor::Actor>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetNextTerrain(const std::string& terrain);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::weak_ptr<ratchet::actor::Actor> GetTarget(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetNextTerrain(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //bool IsActionEnable(void);
    /// <summary>
    /// �L����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //bool EnableAction(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //bool DisableAction(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_PLAYER_COMPONENT_H