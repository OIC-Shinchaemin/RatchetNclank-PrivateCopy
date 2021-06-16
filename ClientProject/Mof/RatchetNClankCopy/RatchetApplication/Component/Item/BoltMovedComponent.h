#ifndef RATCHET_COMPONENT_ITEM_BOLT_MOVED_COMPONENT_H
#define RATCHET_COMPONENT_ITEM_BOLT_MOVED_COMPONENT_H


#include "BoltActionComponent.h"

#include <memory>


namespace ratchet {
namespace component {
namespace item {
class BoltMovedComponent : public ratchet::component::item::BoltActionComponent {
    using super = ratchet::component::item::BoltActionComponent;
private:
    //! ���x
    Mof::CVector3 _speed;
    //! �p�x
    Mof::CVector3 _angle;
    //! ����
    float _decrase;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    BoltMovedComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    BoltMovedComponent(const BoltMovedComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BoltMovedComponent();
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
    virtual std::string_view GetStateType(void) const override;
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
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void) override;
    /// <summary>
    /// �I��
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool End(void) override;
};
}
}
}
#endif // !RATCHET_COMPONENT_ITEM_BOLT_MOVED_COMPONENT_H