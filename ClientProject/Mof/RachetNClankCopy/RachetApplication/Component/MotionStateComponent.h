#ifndef MY_MOTION_STATE_COMPONENT_H
#define MY_MOTION_STATE_COMPONENT_H


#include "UpdateComponent.h"

#include "My/Core/StateMachine.h"


namespace my {
class MotionStateComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! 状態
    my::StateMachine _state_machine;
    template<class State>
    void RegisterMotionState(my::StateMachine& out) {
        auto shared_this = super::GetOwner();
        auto ptr = std::make_shared<State>();
        ptr->SetActor(shared_this);
        out.RegisterState(ptr);
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    void ChangeState(const std::string& name);
};
}
#endif // !MY_MOTION_STATE_COMPONENT_H