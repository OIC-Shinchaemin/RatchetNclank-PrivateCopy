#ifndef RATCHET_COMPONENT_ITEM_NANOTECH_ITEM_NanotechItem_GRAVITATE_COMPONENT_H
#define RATCHET_COMPONENT_ITEM_NANOTECH_ITEM_NanotechItem_GRAVITATE_COMPONENT_H


#include "NanotechItemActionComponent.h"

#include <memory>


namespace ratchet { namespace component { namespace item { namespace nanotechitem {
class NanotechItemGravitateComponent : public ratchet::component::item::nanotechitem::NanotechItemActionComponent {
    using super = ratchet::component::item::nanotechitem::NanotechItemActionComponent;
private:
    //! 型
    std::weak_ptr<class NanotechItemComponent> _type_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    NanotechItemGravitateComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    NanotechItemGravitateComponent(const NanotechItemGravitateComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~NanotechItemGravitateComponent();
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
};}}}
}
#endif // !RATCHET_COMPONENT_ITEM_NANOTECH_ITEM_NanotechItem_GRAVITATE_COMPONENT_H