#ifndef RATCHET_COMPONENT_BULLET_BOMB_GLOVE_BULLET_COMPONENT_H
#define RATCHET_COMPONENT_BULLET_BOMB_GLOVE_BULLET_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>

#include "../Collision/CollisionComponent.h"


namespace ratchet::component::bullet {
class BombGloveBulletComponent : public ratchet::component::UpdateComponent {
    using super = ratchet::component::UpdateComponent;
private:
    /// <summary>
    /// �Փˏ���
    /// </summary>
    /// <param name="in"></param>
    /// <returns></returns>
    bool CollisionEnemy(const component::collision::CollisionInfo& in);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    BombGloveBulletComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    BombGloveBulletComponent(const BombGloveBulletComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BombGloveBulletComponent();
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
#endif // !RATCHET_COMPONENT_BULLET_BOMB_GLOVE_BULLET_COMPONENT_H