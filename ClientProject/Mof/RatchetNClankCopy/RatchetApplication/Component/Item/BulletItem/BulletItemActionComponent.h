#ifndef RATCHET_COMPONENT_ITEM_BULLET_ITEM_BulletItem_ACTION_COMPONENT_H
#define RATCHET_COMPONENT_ITEM_BULLET_ITEM_BulletItem_ACTION_COMPONENT_H


#include "../../ActionComponent.h"

#include <memory>

#include "../../VelocityComponent.h"
#include "BulletItemActionStateComponent.h"
#include "../../../State/BulletItemActionStateDefine.h"


namespace ratchet {
namespace component {
namespace item {
namespace bulletitem {
    class BulletItemActionComponent : public ratchet::component::ActionComponent {
    using super = ratchet::component::ActionComponent;
    private:
        //! ���x
        std::weak_ptr<ratchet::component::VelocityComponent> _velocity_com;
        //! ���
        std::weak_ptr<ratchet::component::item::bulletitem::BulletItemActionStateComponent> _state_com;
    protected:
        /// <summary>
        /// �Q�b�^�[
        /// </summary>
        /// <param name=""></param>
        /// <returns></returns>
        std::shared_ptr<ratchet::component::VelocityComponent> GetVelocityComponent(void) const;
        /// <summary>
        /// �ύX
        /// </summary>
        /// <param name="name"></param>
        bool ChangeActionState(const std::string& name);
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="priority"></param>
        BulletItemActionComponent(int priority);
        /// <summary>
        /// �R�s�[�R���X�g���N�^
        /// </summary>
        /// <param name="obj"></param>
        BulletItemActionComponent(const BulletItemActionComponent& obj);
        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        virtual ~BulletItemActionComponent();
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
        /// ���
        /// </summary>
        /// <param name=""></param>
        /// <returns></returns>
        virtual bool Release(void) override;
};
}
}
}
}
#endif // !RATCHET_COMPONENT_ITEM_BULLET_ITEM_BulletItem_ACTION_COMPONENT_H