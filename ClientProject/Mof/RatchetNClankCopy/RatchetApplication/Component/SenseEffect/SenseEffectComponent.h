#ifndef RATCHET_COMPONENT_EFFECT_SENSE_EFFECT_COMPONENT_H
#define RATCHET_COMPONENT_EFFECT_SENSE_EFFECT_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>

#include "../../Actor/Effect/SenseEffect.h"
#include "../BillboardComponent.h"
#include "Base/Core/Timer.h"


namespace ratchet::component::effect {
class SenseEffectComponent : public ::ratchet::component::UpdateComponent{
    using super = ::ratchet::component::UpdateComponent;
private:
    //! 描画オフセット
    Mof::CVector3 _billboard_render_offset;
    //! ビルボード
    std::weak_ptr<ratchet::component::BillboardComponent> _billboard;
    //! 時間
    base::core::Timer _timer;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    SenseEffectComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    SenseEffectComponent(const SenseEffectComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SenseEffectComponent();
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
#ifdef _DEBUG
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void) override;
#endif // _DEBUG
    void TimerStart(void);
};
}
#endif // !RATCHET_COMPONENT_EFFECT_SENSE_EFFECT_COMPONENT_H