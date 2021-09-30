#ifndef RATCHET_COMPONENT_PLAYER_INVINCIBLE_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_INVINCIBLE_COMPONENT_H


#include "UpdateComponent.h"

#include "Base/Core/Timer.h"


namespace ratchet::component {
class InvincibleComponent : public ratchet::component::UpdateComponent {
    using super = ratchet::component::UpdateComponent;
private:
    //! 時間
    base::core::Timer _invincible;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    InvincibleComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    InvincibleComponent(const InvincibleComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~InvincibleComponent();
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// 有効化
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Activate(void) override;
};
}
#endif // !RATCHET_COMPONENT_PLAYER_INVINCIBLE_COMPONENT_H