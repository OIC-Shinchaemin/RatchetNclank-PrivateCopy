#ifndef RATCHET_COMPONENT_ITEM_BULLET_ITEM_BulletItem_ACTION_STATE_COMPONENT_H
#define RATCHET_COMPONENT_ITEM_BULLET_ITEM_BulletItem_ACTION_STATE_COMPONENT_H


#include "../../ActionStateComponent.h"

#include "../../../State/BulletItemActionStateDefine.h"


namespace ratchet {
namespace component {
namespace item {
namespace bulletitem {
class BulletItemActionStateComponent : public ratchet::component::ActionStateComponent {
    using super = ratchet::component::ActionStateComponent;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    BulletItemActionStateComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    BulletItemActionStateComponent(const BulletItemActionStateComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BulletItemActionStateComponent();
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
}
#endif // !RATCHET_COMPONENT_ITEM_BULLET_ITEM_BulletItem_ACTION_STATE_COMPONENT_H