#ifndef RATCHET_COMPONENT_KING_KING_COMPONENT_H
#define RATCHET_COMPONENT_KING_KING_COMPONENT_H


#include "../CharacterComponent.h"

#include <memory>

#include "../../Actor/Character/King.h"


namespace ratchet::component::king {
class KingComponent : public ::ratchet::component::CharacterComponent {
    using super = ::ratchet::component::CharacterComponent;
private:
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    KingComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    KingComponent(const KingComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~KingComponent();
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
    virtual std::shared_ptr<::ratchet::component::Component> Clone(void) override;
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
#endif // !RATCHET_COMPONENT_KING_KING_COMPONENT_H