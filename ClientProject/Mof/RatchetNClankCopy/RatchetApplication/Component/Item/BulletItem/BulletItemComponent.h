#ifndef RATCHET_COMPONENT_ITEM_BULLET_ITEM_BulletItem_COMPONENT_H
#define RATCHET_COMPONENT_ITEM_BULLET_ITEM_BulletItem_COMPONENT_H


#include "../../UpdateComponent.h"

#include "../../../Actor/Item/BulletItem.h"


namespace ratchet {
namespace component {
namespace item {
namespace bulletitem {
class BulletItemComponent : public ratchet::component::UpdateComponent {
    using super = ratchet::component::UpdateComponent;
private:
    //! アクターパラメータ
    ratchet::actor::item::BulletItem::Param _param;
    //! 移動先
    std::weak_ptr<ratchet::actor::Actor> _player;
    //! 状態
    std::weak_ptr<class BulletItemActionStateComponent> _state_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    BulletItemComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    BulletItemComponent(const BulletItemComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BulletItemComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    void SetActorParam(const ratchet::actor::item::BulletItem::Param& param);
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
    const ratchet::actor::item::BulletItem::Param& GetActorParam(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::actor::Actor> GetPlayer(void) const;
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
};
}
}
}
}
#endif // !RATCHET_COMPONENT_ITEM_BULLET_ITEM_BulletItem_COMPONENT_H