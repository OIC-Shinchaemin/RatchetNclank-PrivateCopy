#ifndef RATCHET_COMPONENT_PLAYER_PLAYER_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_PLAYER_COMPONENT_H


#include "../CharacterComponent.h"

#include <memory>

#include "../../Actor/Actor.h"
#include "../../Actor/Character/King.h"
#include "Base/Core/Observable.h"


namespace ratchet::component { 
class TransformComponent; 
class VelocityComponent; 
class CameraComponent; 
}
namespace ratchet::component::collision {
class PlayerCollisionComponent;
}
namespace ratchet::component::player {
class PlayerComponent : public ::ratchet::component::CharacterComponent {
    using super = ::ratchet::component::CharacterComponent;
private:
    //! �W�I
    std::weak_ptr<::ratchet::actor::Actor> _target;
    //! �J�[�\���ʒu
    base::core::Observable<std::optional<Mof::CVector3>> _observable;
    //! ���
    std::weak_ptr<class PlayerStateComponent> _state_com;
    //! �g�����X�t�H�[��
    std::weak_ptr<ratchet::component::TransformComponent> _transform_com;
    //! ���x
    std::weak_ptr<ratchet::component::VelocityComponent> _velocity_com;
    //! �J����
    std::weak_ptr<ratchet::component::CameraComponent> _camera_com;
    //! �J����
    std::weak_ptr<ratchet::component::collision::PlayerCollisionComponent> _coll_volume_com;
    //! �n�_
    std::string _next_terrain;
    //! �ڐG���[�h �L���ł���Ε���{�^�����A�N�V�����{�^���ɂȂ�
    bool _contact_mode;
    //! �b������
    std::weak_ptr<ratchet::actor::character::King> _talk_target;
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
    void SetTarget(const std::shared_ptr<::ratchet::actor::Actor>& ptr);
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
    std::weak_ptr<::ratchet::actor::Actor> GetTarget(void) const;
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
    bool IsContactMode(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool HasTalkTarget(void) const;
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
    virtual std::shared_ptr<::ratchet::component::Component> Clone(void) override;
#ifdef _DEBUG
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void) override;
#endif // _DEBUG
    /// <summary>
    /// ��b
    /// </summary>
    /// <param name=""></param>
    void TalkToTarget(void);
};
}
#endif // !RATCHET_COMPONENT_PLAYER_PLAYER_COMPONENT_H