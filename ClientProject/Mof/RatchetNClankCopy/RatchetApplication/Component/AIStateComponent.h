#ifndef RATCHET_COMPONENT_AI_STATE_COMPONENT_H
#define RATCHET_COMPONENT_AI_STATE_COMPONENT_H


#include "UpdateComponent.h"

#include "Base/Core/StateMachine.h"
#include "Base/Core/Timer.h"


namespace ratchet::component {
class AIStateComponent : public ratchet::component::UpdateComponent {
    using super = ratchet::component::UpdateComponent;
private:
    //! 状態
    base::core::StateMachine _state_machine;
    //! タイマー
    base::core::Timer _thinking_timer;
    //! 作成パス
    std::vector<std::string> _behaviour_path;

    template<class State>
    void RegisterState(base::core::StateMachine& out, const std::string& behaviour) {
        auto shared_this = super::GetOwner();
        auto ptr = std::make_shared<State>();
        ptr->SetActor(shared_this);
        ptr->GenerateBehaviourExecutor(behaviour);
        out.RegisterState(ptr);
    }
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    AIStateComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    AIStateComponent(const AIStateComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~AIStateComponent();
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
#ifdef _DEBUG
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void) override;
#endif // _DEBUG
};
}
#endif // !RATCHET_COMPONENT_AI_STATE_COMPONENT_H