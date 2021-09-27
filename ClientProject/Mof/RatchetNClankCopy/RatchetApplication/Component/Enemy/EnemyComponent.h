#ifndef RATCHET_COMPONENT_ENEMY_ENEMY_COMPONENT_H
#define RATCHET_COMPONENT_ENEMY_ENEMY_COMPONENT_H


#include "../CharacterComponent.h"

#include <optional>
#include <memory>

#include "Base/Core/Timer.h"

#include "../VelocityComponent.h"
#include "../../Actor/Character/Enemy.h"


namespace ratchet::component::enemy {
class EnemyComponent : public ::ratchet::component::CharacterComponent {
    using super = ::ratchet::component::CharacterComponent;
private:
    //! �x�~��Ԑ؂�ւ�
    base::core::Timer _velocity_timer;
    //! �W�I
    std::weak_ptr<::ratchet::actor::Actor> _target;
    //! ���x
    std::weak_ptr<::ratchet::component::VelocityComponent> _velocity_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    EnemyComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    EnemyComponent(const EnemyComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetTarget(const std::shared_ptr<::ratchet::actor::Actor>& ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    std::shared_ptr<ratchet::actor::character::Enemy> GetOwnerCastd(void) const;
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
    std::optional<Mof::CVector3> GetTargetPosition(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetHomeDistance(void) const;
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
    /// <summary>
    /// �G�t�F�N�g����
    /// </summary>
    /// <param name=""></param>
    void DamageEffectEmit(std::shared_ptr<ratchet::actor::Actor> actor);
    /// <summary>
    /// �G�t�F�N�g����
    /// </summary>
    /// <param name=""></param>
    void StarEffectEmit(std::shared_ptr<ratchet::actor::Actor> actor);
};
}
#endif // !RATCHET_COMPONENT_ENEMY_ENEMY_COMPONENT_H