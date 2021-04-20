#ifndef MY_BLASTER_BULLET_COMPONENT_H
#define MY_BLASTER_BULLET_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>


namespace my {
class BlasterBulletComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_BLASTER_BULLET_COMPONENT_H