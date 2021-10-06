#ifndef RATCHET_COMPONENT_BULLET_BLASTER_BULLET_COMPONENT_H
#define RATCHET_COMPONENT_BULLET_BLASTER_BULLET_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>


namespace ratchet::component::bullet {
class BlasterBulletComponent : public ::ratchet::component::UpdateComponent {
    using super = ::ratchet::component::UpdateComponent;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    BlasterBulletComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    BlasterBulletComponent(const BlasterBulletComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BlasterBulletComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
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
    virtual std::shared_ptr<::ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_COMPONENT_BULLET_BLASTER_BULLET_COMPONENT_H