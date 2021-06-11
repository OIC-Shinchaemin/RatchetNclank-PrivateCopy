#ifndef RATCHET_MOTION_STATE_COMPONENT_H
#define RATCHET_MOTION_STATE_COMPONENT_H


#include "UpdateComponent.h"

#include "Base/Core/StateMachine.h"
#include "../State/MotionState.h"


namespace ratchet {
class MotionStateComponent : public ratchet::UpdateComponent {
    using super = ratchet::UpdateComponent;
private:
    //! 状態
    base::core::StateMachine _state_machine;
    //! 
    std::weak_ptr<class MotionComponent> _motion_com;
    void RegisterState(const state::MotionState::Param& param) {
        auto shared_this = super::GetOwner();
        auto ptr = std::make_shared<state::MotionState>();
        ptr->SetActor(shared_this);
        ptr->SetParam(param);
        _state_machine.RegisterState(ptr);
    }
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    MotionStateComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    MotionStateComponent(const MotionStateComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~MotionStateComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
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
    /// <param name="delta_time"></param>
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
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    void ChangeState(const std::string& name);
};
}
#endif // !RATCHET_MOTION_STATE_COMPONENT_H