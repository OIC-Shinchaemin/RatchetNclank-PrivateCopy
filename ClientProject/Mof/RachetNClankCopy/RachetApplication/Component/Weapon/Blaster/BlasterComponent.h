#ifndef MY_BLASTER_COMPONENT_H
#define MY_BLASTER_COMPONENT_H


#include "../../../Component/UpdateComponent.h"


namespace my {
class BlasterComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    BlasterComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    BlasterComponent(const BlasterComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BlasterComponent();
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
#endif // !MY_PLAYER_COMPONENT_H