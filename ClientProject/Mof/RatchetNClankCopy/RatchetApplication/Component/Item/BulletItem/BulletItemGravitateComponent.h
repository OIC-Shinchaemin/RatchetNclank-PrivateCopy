#ifndef RATCHET_COMPONENT_ITEM_BULLET_ITEM_BulletItem_GRAVITATE_COMPONENT_H
#define RATCHET_COMPONENT_ITEM_BULLET_ITEM_BulletItem_GRAVITATE_COMPONENT_H


#include "BulletItemActionComponent.h"

#include <memory>


namespace ratchet {
namespace component {
namespace item {
namespace bulletitem {
class BulletItemGravitateComponent : public ratchet::component::item::bulletitem::BulletItemActionComponent {
    using super = ratchet::component::item::bulletitem::BulletItemActionComponent;
private:
    //! 型
    std::weak_ptr<class BulletItemComponent> _type_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    BulletItemGravitateComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    BulletItemGravitateComponent(const BulletItemGravitateComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BulletItemGravitateComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string_view GetStateType(void) const override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool End(void) override;
};
}
}
}
}
#endif // !RATCHET_COMPONENT_ITEM_BULLET_ITEM_BulletItem_GRAVITATE_COMPONENT_H