#ifndef MY_ENEMY_STATE_COMPONENT_H
#define MY_ENEMY_STATE_COMPONENT_H


#include "../ActionStateComponent.h"
/*
#include "Base/Core/StateMachine.h"
#include "Base/Core/Timer.h"
#include "../../State/ActionState.h"
*/

namespace my {
class EnemyStateComponent : public my::ActionStateComponent {
    using super = my::ActionStateComponent;
/*
private:
    //! 状態
    my::StateMachine _state_machine;
    /// <summary>
    /// 登録
    /// </summary>
    /// <typeparam name="State"></typeparam>
    /// <param name="out"></param>
    template<class State>
    void RegisterState(my::StateMachine& out) {
        auto shared_this = super::GetOwner();
        auto ptr = std::make_shared<State>();
        ptr->SetActor(shared_this);
        out.RegisterState(ptr);
    }
    /// <summary>
    /// 登録
    /// </summary>
    /// <typeparam name="State"></typeparam>
    /// <param name="out"></param>
    void RegisterState(my::StateMachine& out, std::shared_ptr<my::ActionComponent> com) {
        auto shared_this = super::GetOwner();
        auto ptr = std::make_shared<state::ActionState>();
        ptr->SetActionComponent(com);
        out.RegisterState(ptr);
    }
*/
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    EnemyStateComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    EnemyStateComponent(const EnemyStateComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyStateComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    //virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="state"></param>
    /// <returns></returns>
    //bool IsEqual(std::string_view state) const;
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
    //virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Release(void) override;
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
    //void ChangeState(const std::string& name);
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    bool CanTransition(const std::string& next);
#ifdef _DEBUG
    virtual bool DebugRender(void) override;
#endif // _DEBUG
};
}
#endif // !MY_ENEMY_STATE_COMPONENT_H